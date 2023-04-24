#include "MeshComponent.h"
#include "DefaultMaterial.h"
#include "Game.h"
#include "GameException.h"
#include "VectorHelper.h"
#include "MatrixHelper.h"
#include "Camera.h"
#include "Model.h"
#include "Mesh.h"
#include "Utility.h"
#include "DirectionalLight.h"
#include <WICTextureLoader.h>
#include "RasterizerStates.h"
#include "RenderStateHelper.h"
#include "DepthStencilStates.h"
#include "Scene.h"
#include <sstream>

namespace Rendering
{
	RTTI_DEFINITIONS(MeshComponent)

		MeshComponent::MeshComponent(Game& game, const std::string modelFilePath, const std::wstring shaderFilePath, const std::wstring texFilePath)
		: DrawableGameComponent(*(game.GetCamera())), mEffect(nullptr), mMaterial(nullptr), mTextureShaderResourceView(nullptr),
		mWorldMatrix(MatrixHelper::Identity),
		mRenderStateHelper(nullptr),
		mModelFilePath(modelFilePath),mShaderFilePath(shaderFilePath),mTexFilePath(texFilePath)
	{
	}

	MeshComponent::~MeshComponent()
	{
		DeleteObject(mRenderStateHelper);
		ReleaseObject(mTextureShaderResourceView);
		DeleteObject(mMaterial);
		DeleteObject(mEffect);
		for (int i = 0; i < mVertexBuffers.size(); ++i)
		{
			ReleaseObject(mVertexBuffers[i]);
			ReleaseObject(mIndexBuffers[i]);
		}	
	}

	void MeshComponent::SetPosition(const float rotateX, const float rotateY, const float rotateZ, const float scaleFactor, const float translateX, const float translateY, const float translateZ)
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

	void MeshComponent::Initialize()
	{
		SetCurrentDirectory(Utility::ExecutableDirectory().c_str());
		std::unique_ptr<Model> model(new Model(*Game::GetInstance(), mModelFilePath, false));

		// Initialize the material
		mEffect = new Effect(*Game::GetInstance());
		mEffect->LoadCompiledEffect(mShaderFilePath);
		mMaterial = new DefaultMaterial();
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
		
		HRESULT hr = DirectX::CreateWICTextureFromFile(Game::GetInstance()->Direct3DDevice(), Game::GetInstance()->Direct3DDeviceContext(), mTexFilePath.c_str(), nullptr, &mTextureShaderResourceView);
		if (FAILED(hr))
		{
			throw GameException("CreateWICTextureFromFile() failed.", hr);
		}

		mRenderStateHelper = new RenderStateHelper(*Game::GetInstance());
	}

	void MeshComponent::Update(const GameTime& gameTime)
	{

	}

	void MeshComponent::Draw(const GameTime& gameTime)
	{
		ID3D11DeviceContext* direct3DDeviceContext = Game::GetInstance()->Direct3DDeviceContext();
		direct3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		Pass* pass = mMaterial->CurrentTechnique()->Passes().at(0);
		ID3D11InputLayout* inputLayout = mMaterial->InputLayouts().at(pass);
		direct3DDeviceContext->IASetInputLayout(inputLayout);

		UINT stride = mMaterial->VertexSize();
		UINT offset = 0;
		XMMATRIX worldMatrix = XMLoadFloat4x4(&mWorldMatrix);
		XMMATRIX vp = mCamera->ViewMatrix() * mCamera->ProjectionMatrix();
		XMVECTOR ambientColor = XMLoadColor(&(Game::GetInstance()->GetScene()->GetAmbientColor()));

		mMaterial->ViewProjection() << vp;
		mMaterial->World() << worldMatrix;
		mMaterial->CamPos() << mCamera->PositionVector();
		mMaterial->AmbientColor() << ambientColor;
		mMaterial->NumDirLight() << Game::GetInstance()->GetScene()->mDirectionalLights.size();
		for (int i = 0; i < Game::GetInstance()->GetScene()->mDirectionalLights.size(); ++i)
		{
			mMaterial->DirectLights().GetVariable()->GetElement(i)->SetRawValue(Game::GetInstance()->GetScene()->mDirectionalLights[i]->GetData(), 0, sizeof(DirectionalLightData));
		}
		mMaterial->ColorTexture() << mTextureShaderResourceView;

		pass->Apply(0, direct3DDeviceContext);
		for (int i = 0; i < mVertexBuffers.size(); ++i)
		{
			direct3DDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffers[i], &stride, &offset);
			direct3DDeviceContext->IASetIndexBuffer(mIndexBuffers[i], DXGI_FORMAT_R32_UINT, 0);
			//direct3DDeviceContext->OMSetDepthStencilState(Library::DepthStencilStates::DepthGreaterEqual, 0);
			direct3DDeviceContext->DrawIndexed(mIndexCounts[i], 0, 0);
		}
	}
}