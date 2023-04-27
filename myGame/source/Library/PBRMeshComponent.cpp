#include "PBRMeshComponent.h"
#include "MatrixHelper.h"
#include "Utility.h"
#include "Model.h"
#include "Game.h"
#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include "Effect.h"
#include "PBRMaterial.h"
#include "GameException.h"
#include "RenderStateHelper.h"
#include "DirectionalLight.h"
#include <WICTextureLoader.h>

namespace Rendering
{
	RTTI_DEFINITIONS(PBRMeshComponent)

		PBRMeshComponent::PBRMeshComponent(const std::string modelFilePath, const std::wstring shaderFilePath, const std::wstring albedoTexFilePath, const std::wstring normalTexFilePath, const std::wstring metallicRoughnessTexFilePath)
		: mEffect(nullptr), mMaterial(nullptr), mAlbedoTextureShaderResourceView(nullptr),
		mWorldMatrix(MatrixHelper::Identity),
		mRenderStateHelper(nullptr),
		mModelFilePath(modelFilePath), mShaderFilePath(shaderFilePath), 
		mAlbedoTexFilePath(albedoTexFilePath),mNormalTexFilePath(normalTexFilePath),mMetallicRoughnessTexFilePath(metallicRoughnessTexFilePath)
	{
	}

	PBRMeshComponent::~PBRMeshComponent()
	{
		DeleteObject(mRenderStateHelper);
		ReleaseObject(mAlbedoTextureShaderResourceView);
		ReleaseObject(mNormalTextureShaderResourceView);
		ReleaseObject(mMetallicRoughnessTextureShaderResourceView);
		DeleteObject(mMaterial);
		DeleteObject(mEffect);
		for (int i = 0; i < mVertexBuffers.size(); ++i)
		{
			ReleaseObject(mVertexBuffers[i]);
			ReleaseObject(mIndexBuffers[i]);
		}
	}

	void PBRMeshComponent::SetPosition(const float rotateX, const float rotateY, const float rotateZ, const float scaleFactor, const float translateX, const float translateY, const float translateZ)
	{
		XMMATRIX worldMatrix = XMLoadFloat4x4(&mWorldMatrix);
		XMMATRIX RotationZ = XMMatrixRotationZ(rotateZ);
		XMMATRIX RotationX = XMMatrixRotationX(rotateX);
		XMMATRIX RotationY = XMMatrixRotationY(rotateY);
		XMMATRIX Scale = XMMatrixScaling(scaleFactor, scaleFactor, scaleFactor);
		XMMATRIX Translation = XMMatrixTranslation(translateX, translateY, translateZ);
		worldMatrix = RotationZ * RotationX * RotationY * Scale * Translation;

		XMStoreFloat4x4(&mWorldMatrix, worldMatrix);
	}

	void PBRMeshComponent::Initialize()
	{
		SetCurrentDirectory(Utility::ExecutableDirectory().c_str());
		std::unique_ptr<Model> model(new Model(mModelFilePath, false));

		// Initialize the material
		mEffect = new Effect();
		mEffect->LoadCompiledEffect(mShaderFilePath);
		mMaterial = new PBRMaterial();
		mMaterial->Initialize(mEffect);

		mVertexBuffers.resize(model->Meshes().size());
		mIndexBuffers.resize(model->Meshes().size());
		mIndexCounts.resize(model->Meshes().size());
		for (int i = 0; i < model->Meshes().size(); ++i)
		{
			Mesh* mesh = model->Meshes().at(i);
			mMaterial->CreateVertexBuffer(Game::GetInstance()->Direct3DDevice(), *mesh, &mVertexBuffers[i]);
			mesh->CreateIndexBuffer(&mIndexBuffers[i]);
			mIndexCounts[i] = mesh->Indices().size();
		}

		HRESULT hr = DirectX::CreateWICTextureFromFile(Game::GetInstance()->Direct3DDevice(), Game::GetInstance()->Direct3DDeviceContext(), mAlbedoTexFilePath.c_str(), nullptr, &mAlbedoTextureShaderResourceView);
		if (FAILED(hr))
		{
			throw GameException("CreateWICTextureFromFile() failed.", hr);
		}
		if (mNormalTexFilePath.size())
		{
			hr = DirectX::CreateWICTextureFromFile(Game::GetInstance()->Direct3DDevice(), Game::GetInstance()->Direct3DDeviceContext(), mNormalTexFilePath.c_str(), nullptr, &mNormalTextureShaderResourceView);
			if (FAILED(hr))
			{
				throw GameException("CreateWICTextureFromFile() failed.", hr);
			}
		}
		if (mMetallicRoughnessTexFilePath.size())
		{
			hr = DirectX::CreateWICTextureFromFile(Game::GetInstance()->Direct3DDevice(), Game::GetInstance()->Direct3DDeviceContext(), mMetallicRoughnessTexFilePath.c_str(), nullptr, &mMetallicRoughnessTextureShaderResourceView);
			if (FAILED(hr))
			{
				throw GameException("CreateWICTextureFromFile() failed.", hr);
			}
		}
		mRenderStateHelper = new RenderStateHelper();
	}

	void PBRMeshComponent::Update(const GameTime& gameTime)
	{

	}

	void PBRMeshComponent::Draw(const GameTime& gameTime)
	{
		ID3D11DeviceContext* direct3DDeviceContext = Game::GetInstance()->Direct3DDeviceContext();
		direct3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		Pass* pass = mMaterial->CurrentTechnique()->Passes().at(0);
		ID3D11InputLayout* inputLayout = mMaterial->InputLayouts().at(pass);
		direct3DDeviceContext->IASetInputLayout(inputLayout);

		UINT stride = mMaterial->VertexSize();
		UINT offset = 0;
		XMMATRIX worldMatrix = XMLoadFloat4x4(&mWorldMatrix);
		XMMATRIX vp = Game::GetInstance()->GetCamera()->ViewMatrix() * Game::GetInstance()->GetCamera()->ProjectionMatrix();
		XMVECTOR ambientColor = Game::GetInstance()->GetScene()->GetAmbientColor();

		mMaterial->ViewProjection() << vp;
		mMaterial->World() << worldMatrix;
		mMaterial->CamPos() << Game::GetInstance()->GetCamera()->PositionVector();
		mMaterial->AmbientColor() << ambientColor;
		mMaterial->NumDirLight() << Game::GetInstance()->GetScene()->mDirectionalLights.size();
		for (int i = 0; i < Game::GetInstance()->GetScene()->mDirectionalLights.size(); ++i)
		{
			mMaterial->DirectLights().GetVariable()->GetElement(i)->SetRawValue(Game::GetInstance()->GetScene()->mDirectionalLights[i]->GetData(), 0, sizeof(DirectionalLightData));
		}
		mMaterial->AlbedoTexture() << mAlbedoTextureShaderResourceView;
		if (mNormalTextureShaderResourceView)
			mMaterial->NormalTexture() << mNormalTextureShaderResourceView;
		if (mMetallicRoughnessTextureShaderResourceView)
			mMaterial->MetallicRoughnessTexture() << mMetallicRoughnessTextureShaderResourceView;
		pass->Apply(0, direct3DDeviceContext);
		for (int i = 0; i < mVertexBuffers.size(); ++i)
		{
			direct3DDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffers[i], &stride, &offset);
			direct3DDeviceContext->IASetIndexBuffer(mIndexBuffers[i], DXGI_FORMAT_R32_UINT, 0);
			direct3DDeviceContext->DrawIndexed(mIndexCounts[i], 0, 0);
		}
	}
	void PBRMeshComponent::DrawPass(const GameTime& gameTime, std::string passName)
	{
		Pass* pass = mMaterial->CurrentTechnique()->GetPass(passName);
		if (!pass)
			return;
		ID3D11DeviceContext* direct3DDeviceContext = Game::GetInstance()->Direct3DDeviceContext();
		direct3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		ID3D11InputLayout* inputLayout = mMaterial->InputLayouts().at(pass);
		direct3DDeviceContext->IASetInputLayout(inputLayout);

		UINT stride = mMaterial->VertexSize();
		UINT offset = 0;
		XMMATRIX worldMatrix = XMLoadFloat4x4(&mWorldMatrix);
		XMMATRIX vp = Game::GetInstance()->GetCamera()->ViewMatrix() * Game::GetInstance()->GetCamera()->ProjectionMatrix();
		XMVECTOR ambientColor = Game::GetInstance()->GetScene()->GetAmbientColor();

		mMaterial->ViewProjection() << vp;
		mMaterial->World() << worldMatrix;
		mMaterial->CamPos() << Game::GetInstance()->GetCamera()->PositionVector();
		mMaterial->AmbientColor() << ambientColor;
		mMaterial->NumDirLight() << Game::GetInstance()->GetScene()->mDirectionalLights.size();
		for (int i = 0; i < Game::GetInstance()->GetScene()->mDirectionalLights.size(); ++i)
		{
			mMaterial->DirectLights().GetVariable()->GetElement(i)->SetRawValue(Game::GetInstance()->GetScene()->mDirectionalLights[i]->GetData(), 0, sizeof(DirectionalLightData));
		}
		mMaterial->AlbedoTexture() << mAlbedoTextureShaderResourceView;
		if (mNormalTextureShaderResourceView)
			mMaterial->NormalTexture() << mNormalTextureShaderResourceView;
		if (mMetallicRoughnessTextureShaderResourceView)
			mMaterial->MetallicRoughnessTexture() << mMetallicRoughnessTextureShaderResourceView;
		pass->Apply(0, direct3DDeviceContext);
		for (int i = 0; i < mVertexBuffers.size(); ++i)
		{
			direct3DDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffers[i], &stride, &offset);
			direct3DDeviceContext->IASetIndexBuffer(mIndexBuffers[i], DXGI_FORMAT_R32_UINT, 0);
			direct3DDeviceContext->DrawIndexed(mIndexCounts[i], 0, 0);
		}
	}
}