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
#include "ProxyModel.h"
#include "RenderStateHelper.h"
#include "Scene.h"
#include <sstream>

namespace Rendering
{
	RTTI_DEFINITIONS(MeshComponent)

		MeshComponent::MeshComponent(Game& game, const std::string modelFilePath, const std::wstring shaderFilePath, const std::wstring texFilePath)
		: DrawableGameComponent(game, *(game.GetCamera())), mEffect(nullptr), mMaterial(nullptr), mTextureShaderResourceView(nullptr),
		mVertexBuffer(nullptr), mIndexBuffer(nullptr), mIndexCount(0),
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
		ReleaseObject(mVertexBuffer);
		ReleaseObject(mIndexBuffer);
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

		std::unique_ptr<Model> model(new Model(*mGame, mModelFilePath, false));

		// Initialize the material
		mEffect = new Effect(*mGame);
		mEffect->LoadCompiledEffect(mShaderFilePath);
		mMaterial = new DefaultMaterial();
		mMaterial->Initialize(mEffect);

		Mesh* mesh = model->Meshes().at(0);
		mMaterial->CreateVertexBuffer(mGame->Direct3DDevice(), *mesh, &mVertexBuffer);
		mesh->CreateIndexBuffer(&mIndexBuffer);
		mIndexCount = mesh->Indices().size();

		HRESULT hr = DirectX::CreateWICTextureFromFile(mGame->Direct3DDevice(), mGame->Direct3DDeviceContext(), mTexFilePath.c_str(), nullptr, &mTextureShaderResourceView);
		if (FAILED(hr))
		{
			throw GameException("CreateWICTextureFromFile() failed.", hr);
		}

		mRenderStateHelper = new RenderStateHelper(*mGame);
	}

	void MeshComponent::Update(const GameTime& gameTime)
	{

	}

	void MeshComponent::Draw(const GameTime& gameTime)
	{
		ID3D11DeviceContext* direct3DDeviceContext = mGame->Direct3DDeviceContext();
		direct3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		Pass* pass = mMaterial->CurrentTechnique()->Passes().at(0);
		ID3D11InputLayout* inputLayout = mMaterial->InputLayouts().at(pass);
		direct3DDeviceContext->IASetInputLayout(inputLayout);

		UINT stride = mMaterial->VertexSize();
		UINT offset = 0;
		direct3DDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
		direct3DDeviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		XMMATRIX worldMatrix = XMLoadFloat4x4(&mWorldMatrix);
		XMMATRIX wvp = worldMatrix * mCamera->ViewMatrix() * mCamera->ProjectionMatrix();
		XMVECTOR ambientColor = XMLoadColor(&(mGame->GetScene()->GetAmbientColor()));

		mMaterial->WorldViewProjection() << wvp;
		mMaterial->World() << worldMatrix;
		mMaterial->CamPos() << mCamera->PositionVector();
		mMaterial->AmbientColor() << ambientColor;
		if (mGame->GetScene()->mMainDirectionalLight)
		{
			mMaterial->LightColor() << mGame->GetScene()->mMainDirectionalLight->ColorVector();
			mMaterial->LightDirection() << mGame->GetScene()->mMainDirectionalLight->DirectionVector();
		}
		mMaterial->ColorTexture() << mTextureShaderResourceView;

		pass->Apply(0, direct3DDeviceContext);

		mRenderStateHelper->SaveAll();
		direct3DDeviceContext->DrawIndexed(mIndexCount, 0, 0);
		mRenderStateHelper->RestoreAll();
	}
}