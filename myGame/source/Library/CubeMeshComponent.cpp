#include "CubeMeshComponent.h"
#include "Game.h"
#include "GameException.h"
#include "MatrixHelper.h"
#include "Camera.h"
#include "Utility.h"
#include "D3DCompiler.h"
#include "WICTextureLoader.h" 
#include "Effect.h"

namespace Library
{
    RTTI_DEFINITIONS(CubeMeshComponent)

    CubeMeshComponent::CubeMeshComponent(Game& game, Camera& camera):
        DrawableGameComponent(game, camera),
        //mEffect(nullptr), mTechnique(nullptr), mPass(nullptr),
        mWvpVariable(nullptr),
        mTextureShaderResourceView(nullptr), mColorTextureVariable(nullptr),
        mInputLayout(nullptr), mWorldMatrix(MatrixHelper::Identity), mVertexBuffer(nullptr), mIndexBuffer(nullptr),
        aEffect(nullptr),
        aMaterial(nullptr)
    {
    }

    CubeMeshComponent::~CubeMeshComponent()
    {
        ReleaseObject(mWvpVariable);
        //ReleaseObject(mPass);
        ReleaseObject(mTextureShaderResourceView);
        ReleaseObject(mColorTextureVariable);
        //ReleaseObject(mTechnique);
        //ReleaseObject(mEffect);
        DeleteObject(aEffect);
        ReleaseObject(mInputLayout);
        ReleaseObject(mVertexBuffer);
        ReleaseObject(mIndexBuffer);
    }

    void CubeMeshComponent::Initialize()
    {
        SetCurrentDirectory(Utility::ExecutableDirectory().c_str());
        //Effect::CompileEffectFromFile(mGame->Direct3DDevice(), &mEffect, L"Content\\Effects\\TextureMapping.fx");
        aEffect = new Effect(*mGame);
        aEffect->CompileFromFile(L"Content\\Effects\\TextureMapping.fx");
        aTechnique = aEffect->TechniquesByName().find("main11")->second;
        aPass = aTechnique->PassesByName().find("p0")->second;
        ID3DX11EffectVariable* variable = aEffect->VariablesByName().find("WorldViewProjection")->second->GetVariable();
        mWvpVariable = variable->AsMatrix();
        if (mWvpVariable->IsValid() == false)
        {
            throw GameException("Invalid effect variable cast.");
        }
        variable = aEffect->VariablesByName().find("ColorTexture")->second->GetVariable();
        mColorTextureVariable = variable->AsShaderResource();
        if (mColorTextureVariable->IsValid() == false)
        {
            throw GameException("Invalid effect variable cast.");
        }
        D3D11_INPUT_ELEMENT_DESC inputElementDescriptions[] =
        {
          { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
          { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
        };
        aPass->CreateInputLayout(inputElementDescriptions, ARRAYSIZE(inputElementDescriptions), &mInputLayout);

        // Compile the shader
//        UINT shaderFlags = 0;
//
//#if defined( DEBUG ) || defined( _DEBUG )
//        shaderFlags |= D3DCOMPILE_DEBUG;
//        shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
//#endif
//
//        ID3D10Blob* compiledShader = nullptr;
//        ID3D10Blob* errorMessages = nullptr;
//
//        //1. load the effect file (vertex and pixel shader)
//        HRESULT hr = D3DCompileFromFile(L"Content\\Effects\\TextureMapping.fx", nullptr, nullptr, nullptr, "fx_5_0", shaderFlags, 0, &compiledShader, &errorMessages);
//        if (FAILED(hr))
//        {
//            const char* errorMessage = (errorMessages != nullptr ? (char*)errorMessages->GetBufferPointer() : "D3DX11CompileFromFile() failed");
//            GameException ex(errorMessage, hr);
//            ReleaseObject(errorMessages);
//            throw ex;
//        }
//        // Create an effect object from the compiled shader
//        hr = D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), 0, mGame->Direct3DDevice(), &mEffect);
//        if (FAILED(hr))
//        {
//            throw GameException("D3DX11CreateEffectFromMemory() failed.", hr);
//        }
//
//        ReleaseObject(compiledShader);
//
//        // Look up the technique, pass, and WVP variable from the effect
//        mTechnique = mEffect->GetTechniqueByName("main11");
//        if (mTechnique == nullptr)
//        {
//            throw GameException("ID3DX11Effect::GetTechniqueByName() could not find the specified technique.", hr);
//        }
//
//        mPass = mTechnique->GetPassByName("p0");
//        if (mPass == nullptr)
//        {
//            throw GameException("ID3DX11EffectTechnique::GetPassByName() could not find the specified pass.", hr);
//        }
//        
//        ID3DX11EffectVariable* variable = mEffect->GetVariableByName("WorldViewProjection");
//        if (variable == nullptr)
//        {
//            throw GameException("ID3DX11Effect::GetVariableByName() could not find the specified variable.", hr);
//        }
//        mWvpVariable = variable->AsMatrix();
//        if (mWvpVariable->IsValid() == false)
//        {
//            throw GameException("Invalid effect variable cast.");
//        }
//
//        variable = mEffect->GetVariableByName("ColorTexture");
//        if (variable == nullptr)
//        {
//            throw GameException("ID3DX11Effect::GetVariableByName() could not find the specified variable.", hr);
//        }
//        mColorTextureVariable = variable->AsShaderResource();
//        if (mColorTextureVariable->IsValid() == false)
//        {
//            throw GameException("Invalid effect variable cast.");
//        }
//
//        // Create the input layout
//        D3DX11_PASS_DESC passDesc;
//        mPass->GetDesc(&passDesc);
//
//        //2. create the vetex layout
//        D3D11_INPUT_ELEMENT_DESC inputElementDescriptions[] =
//        {
//          { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//          { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
//        };
//        if (FAILED(hr = mGame->Direct3DDevice()->CreateInputLayout(inputElementDescriptions, ARRAYSIZE(inputElementDescriptions), passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &mInputLayout)))
//        {
//            throw GameException("ID3D11Device::CreateInputLayout() failed.", hr);
//        }

        // 3. Create the vertex buffer
        TextureMappingVertex vertices[] =
        {
TextureMappingVertex(XMFLOAT4(-5.0f, 0.0f, 5.0f, 1.0f), XMFLOAT2(0.0f, 1.0f)),
TextureMappingVertex(XMFLOAT4(+5.0f, 0.0f, 5.0f, 1.0f), XMFLOAT2(1.0f, 1.0f)),
TextureMappingVertex(XMFLOAT4(+5.0f, 0.0f, -5.0f, 1.0f), XMFLOAT2(1.0f, 0.0f)),
TextureMappingVertex(XMFLOAT4(-5.0f, 0.0f, -5.0f, 1.0f), XMFLOAT2(0.0f, 0.0f)),
        };
        D3D11_BUFFER_DESC vertexBufferDesc;
        ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
        vertexBufferDesc.ByteWidth = sizeof(TextureMappingVertex) * ARRAYSIZE(vertices);
        vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
        vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        D3D11_SUBRESOURCE_DATA vertexSubResourceData;
        ZeroMemory(&vertexSubResourceData, sizeof(vertexSubResourceData));
        vertexSubResourceData.pSysMem = vertices;
        if (FAILED(mGame->Direct3DDevice()->CreateBuffer(&vertexBufferDesc, &vertexSubResourceData, &mVertexBuffer)))
        {
            throw GameException("ID3D11Device::CreateBuffer() failed.");
        }

        //Use Indexbuffer
        UINT indices[] =
        {
            //using texture
            1, 0, 3,
            1, 3, 2,

        };
        D3D11_BUFFER_DESC indexBufferDesc;
        ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
        indexBufferDesc.ByteWidth = sizeof(UINT) * ARRAYSIZE(indices);
        indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
        indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        D3D11_SUBRESOURCE_DATA indexSubResourceData;
        ZeroMemory(&indexSubResourceData, sizeof(indexSubResourceData));
        indexSubResourceData.pSysMem = indices;
        if (FAILED(mGame->Direct3DDevice()->CreateBuffer(&indexBufferDesc, &indexSubResourceData, &mIndexBuffer)))
        {
            throw GameException("ID3D11Device::CreateBuffer() failed.");
        }

        std::wstring textureName = L"Content\\Textures\\grass.jpg";
        HRESULT hr;
        if (FAILED(hr = DirectX::CreateWICTextureFromFile(mGame->Direct3DDevice(), mGame->Direct3DDeviceContext(), textureName.c_str(), nullptr, &mTextureShaderResourceView)))
        {
            throw GameException("CreateWICTextureFromFile() failed.", hr);
        }
    }

    void CubeMeshComponent::Update(const GameTime& gameTime)
    {
        
    }

    void CubeMeshComponent::Draw(const GameTime& gameTime)
    {
        //4. draw function
        ID3D11DeviceContext* direct3DDeviceContext = mGame->Direct3DDeviceContext();
        direct3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        direct3DDeviceContext->IASetInputLayout(mInputLayout);

        UINT stride = sizeof(TextureMappingVertex);
        UINT offset = 0;
        direct3DDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
        direct3DDeviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
        mColorTextureVariable->SetResource(mTextureShaderResourceView);
        XMMATRIX worldMatrix = XMLoadFloat4x4(&mWorldMatrix);
        XMMATRIX wvp = worldMatrix * mCamera->ViewMatrix() * mCamera->ProjectionMatrix();
        mWvpVariable->SetMatrix(reinterpret_cast<const float*>(&wvp));
        aPass->Apply(0, direct3DDeviceContext);
        //direct3DDeviceContext->Draw(3, 0);
        direct3DDeviceContext->DrawIndexed(6, 0, 0);
    }
}