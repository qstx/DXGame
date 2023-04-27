#include "CubeMeshComponent.h"
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
#include <DDSTextureLoader.h>
#include "ProxyModel.h"
#include "RasterizerStates.h"
#include "DepthStencilStates.h"
#include "RenderStateHelper.h"
#include "Scene.h"
#include <sstream>
#include <d3d11.h>

namespace Rendering
{
	RTTI_DEFINITIONS(CubeMeshComponent)

		CubeMeshComponent::CubeMeshComponent(const std::wstring shaderFilePath, const std::wstring texFilePath)
		: mEffect(nullptr), mMaterial(nullptr), mTextureShaderResourceView(nullptr),
		mWorldMatrix(MatrixHelper::Identity),
		mRenderStateHelper(nullptr),
		mShaderFilePath(shaderFilePath), mTexFilePath(texFilePath),
		mVertexBuffer(nullptr), mIndexBuffer(nullptr), mIndexCount(0)
	{

	}

	CubeMeshComponent::~CubeMeshComponent()
	{
		DeleteObject(mRenderStateHelper);
		ReleaseObject(mTextureShaderResourceView);
		DeleteObject(mMaterial);
		DeleteObject(mEffect);
		ReleaseObject(mVertexBuffer);
		ReleaseObject(mIndexBuffer);
	}

	void CubeMeshComponent::Initialize()
	{
		SetCurrentDirectory(Utility::ExecutableDirectory().c_str());
		std::unique_ptr<Model> model(new Model("Content/Models/bench.3ds", false));

		// Initialize the material
		mEffect = new Effect();
		mEffect->LoadCompiledEffect(mShaderFilePath);
		mMaterial = new DefaultMaterial();
		mMaterial->Initialize(mEffect);

		DefaultMaterialVertex vertices[] =
		{
			//上
DefaultMaterialVertex(XMFLOAT4(-0.5f, 0.5f, 0.5f, 1.0f), XMFLOAT2(0.0f, 1.0f),XMFLOAT3(0,1,0)),
DefaultMaterialVertex(XMFLOAT4(+0.5f, 0.5f, 0.5f, 1.0f), XMFLOAT2(1.0f, 1.0f),XMFLOAT3(0,1,0)),
DefaultMaterialVertex(XMFLOAT4(+0.5f, 0.5f, -0.5f, 1.0f), XMFLOAT2(1.0f, 0.0f),XMFLOAT3(0,1,0)),
DefaultMaterialVertex(XMFLOAT4(-0.5f, 0.5f, -0.5f, 1.0f), XMFLOAT2(0.0f, 0.0f),XMFLOAT3(0,1,0)),
			//下
DefaultMaterialVertex(XMFLOAT4(-0.5f, -0.5f, 0.5f, 1.0f), XMFLOAT2(0.0f, 1.0f),XMFLOAT3(0,-1,0)),
DefaultMaterialVertex(XMFLOAT4(+0.5f, -0.5f, 0.5f, 1.0f), XMFLOAT2(1.0f, 1.0f),XMFLOAT3(0,-1,0)),
DefaultMaterialVertex(XMFLOAT4(+0.5f, -0.5f, -0.5f, 1.0f), XMFLOAT2(1.0f, 0.0f),XMFLOAT3(0,-1,0)),
DefaultMaterialVertex(XMFLOAT4(-0.5f, -0.5f, -0.5f, 1.0f), XMFLOAT2(0.0f, 0.0f),XMFLOAT3(0,-1,0)),
			//右
DefaultMaterialVertex(XMFLOAT4(0.5f, -0.5f, 0.5f, 1.0f), XMFLOAT2(0.0f, 1.0f),XMFLOAT3(1,0,0)),
DefaultMaterialVertex(XMFLOAT4(0.5f, +0.5f, 0.5f, 1.0f), XMFLOAT2(1.0f, 1.0f),XMFLOAT3(1,0,0)),
DefaultMaterialVertex(XMFLOAT4(0.5f, +0.5f, -0.5f, 1.0f), XMFLOAT2(1.0f, 0.0f),XMFLOAT3(1,0,0)),
DefaultMaterialVertex(XMFLOAT4(0.5f, -0.5f, -0.5f, 1.0f), XMFLOAT2(0.0f, 0.0f),XMFLOAT3(1,0,0)),
			//左
DefaultMaterialVertex(XMFLOAT4(-0.5f,-0.5f, 0.5f, 1.0f), XMFLOAT2(0.0f, 1.0f),XMFLOAT3(-1,0,0)),
DefaultMaterialVertex(XMFLOAT4(-0.5f,+0.5f, 0.5f, 1.0f), XMFLOAT2(1.0f, 1.0f),XMFLOAT3(-1,0,0)),
DefaultMaterialVertex(XMFLOAT4(-0.5f,+0.5f, -0.5f, 1.0f), XMFLOAT2(1.0f, 0.0f),XMFLOAT3(-1,0,0)),
DefaultMaterialVertex(XMFLOAT4(-0.5f,-0.5f, -0.5f, 1.0f), XMFLOAT2(0.0f, 0.0f),XMFLOAT3(-1,0,0)),
		//前
DefaultMaterialVertex(XMFLOAT4(-0.5f, 0.5f, 0.5f, 1.0f), XMFLOAT2(0.0f, 1.0f),XMFLOAT3(0,0,1)),
DefaultMaterialVertex(XMFLOAT4(+0.5f, 0.5f, 0.5f, 1.0f), XMFLOAT2(1.0f, 1.0f),XMFLOAT3(0,0,1)),
DefaultMaterialVertex(XMFLOAT4(+0.5f, -0.5f,0.5f,  1.0f), XMFLOAT2(1.0f, 0.0f),XMFLOAT3(0,0,1)),
DefaultMaterialVertex(XMFLOAT4(-0.5f, -0.5f,0.5f,  1.0f), XMFLOAT2(0.0f, 0.0f),XMFLOAT3(0,0,1)),
		//后
DefaultMaterialVertex(XMFLOAT4(-0.5f, 0.5f, -0.5f,1.0f), XMFLOAT2(0.0f, 1.0f),XMFLOAT3(0,0,-1)),
DefaultMaterialVertex(XMFLOAT4(+0.5f, 0.5f, -0.5f,1.0f), XMFLOAT2(1.0f, 1.0f),XMFLOAT3(0,0,-1)),
DefaultMaterialVertex(XMFLOAT4(+0.5f, -0.5f,-0.5f, 1.0f), XMFLOAT2(1.0f, 0.0f),XMFLOAT3(0,0,-1)),
DefaultMaterialVertex(XMFLOAT4(-0.5f, -0.5f,-0.5f, 1.0f), XMFLOAT2(0.0f, 0.0f),XMFLOAT3(0,0,-1)),
		};
		D3D11_BUFFER_DESC vertexBufferDesc;
		ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
		vertexBufferDesc.ByteWidth = sizeof(DefaultMaterialVertex) * ARRAYSIZE(vertices);
		vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		D3D11_SUBRESOURCE_DATA vertexSubResourceData;
		ZeroMemory(&vertexSubResourceData, sizeof(vertexSubResourceData));
		vertexSubResourceData.pSysMem = vertices;
		if (FAILED(Game::GetInstance()->Direct3DDevice()->CreateBuffer(&vertexBufferDesc, &vertexSubResourceData, &mVertexBuffer)))
		{
			throw GameException("ID3D11Device::CreateBuffer() failed.");
		}

		//Use Indexbuffer
		UINT indices[] =
		{
			//using texture
			1, 0, 3,
			1, 3, 2,
			4, 5, 7,
			7, 5, 6,
			8, 9, 11,
			11,9, 10,
			13,12,15,
			13,15,14,
			16,17,18,
			16,18,19,
			21,20,22,
			22,20,23,
		};
		D3D11_BUFFER_DESC indexBufferDesc;
		ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
		indexBufferDesc.ByteWidth = sizeof(UINT) * ARRAYSIZE(indices);
		indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		D3D11_SUBRESOURCE_DATA indexSubResourceData;
		ZeroMemory(&indexSubResourceData, sizeof(indexSubResourceData));
		indexSubResourceData.pSysMem = indices;
		if (FAILED(Game::GetInstance()->Direct3DDevice()->CreateBuffer(&indexBufferDesc, &indexSubResourceData, &mIndexBuffer)))
		{
			throw GameException("ID3D11Device::CreateBuffer() failed.");
		}
		mIndexCount = 36;
		HRESULT hr = DirectX::CreateDDSTextureFromFile(Game::GetInstance()->Direct3DDevice(), Game::GetInstance()->Direct3DDeviceContext(), mTexFilePath.c_str(), nullptr, &mTextureShaderResourceView);
		if (FAILED(hr))
		{
			throw GameException("CreateWICTextureFromFile() failed.", hr);
		}
		mRenderStateHelper = new RenderStateHelper();
	}

	void CubeMeshComponent::Update(const GameTime& gameTime)
	{

	}

	void CubeMeshComponent::Draw(const GameTime& gameTime)
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
		mMaterial->ColorTexture() << mTextureShaderResourceView;

		pass->Apply(0, direct3DDeviceContext);

		direct3DDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
		direct3DDeviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		direct3DDeviceContext->DrawIndexed(mIndexCount, 0, 0);
	}
}