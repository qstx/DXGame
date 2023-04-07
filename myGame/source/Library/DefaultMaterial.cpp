#include "DefaultMaterial.h"
#include "GameException.h"
#include "Mesh.h"

namespace Rendering
{
    RTTI_DEFINITIONS(DefaultMaterial)

    DefaultMaterial::DefaultMaterial():
        Material("main11"),
        MATERIAL_VARIABLE_INITIALIZATION(World),
        MATERIAL_VARIABLE_INITIALIZATION(ViewProjection),
        MATERIAL_VARIABLE_INITIALIZATION(CamPos),
        MATERIAL_VARIABLE_INITIALIZATION(AmbientColor),
        MATERIAL_VARIABLE_INITIALIZATION(DirectLights),
        MATERIAL_VARIABLE_INITIALIZATION(PointLights),
        MATERIAL_VARIABLE_INITIALIZATION(SpotLights),
        MATERIAL_VARIABLE_INITIALIZATION(NumDirLight),
        MATERIAL_VARIABLE_INITIALIZATION(NumPointLight),
        MATERIAL_VARIABLE_INITIALIZATION(NumSpotLight),
        MATERIAL_VARIABLE_INITIALIZATION(ColorTexture),
        MATERIAL_VARIABLE_INITIALIZATION(P)
    {
    }

	MATERIAL_VARIABLE_DEFINITION(DefaultMaterial, World);
	MATERIAL_VARIABLE_DEFINITION(DefaultMaterial, ViewProjection);
	MATERIAL_VARIABLE_DEFINITION(DefaultMaterial, CamPos);
	MATERIAL_VARIABLE_DEFINITION(DefaultMaterial, AmbientColor);
	MATERIAL_VARIABLE_DEFINITION(DefaultMaterial, DirectLights);
	MATERIAL_VARIABLE_DEFINITION(DefaultMaterial, PointLights);
	MATERIAL_VARIABLE_DEFINITION(DefaultMaterial, SpotLights);
	MATERIAL_VARIABLE_DEFINITION(DefaultMaterial, NumDirLight);
	MATERIAL_VARIABLE_DEFINITION(DefaultMaterial, NumPointLight);
	MATERIAL_VARIABLE_DEFINITION(DefaultMaterial, NumSpotLight);
	MATERIAL_VARIABLE_DEFINITION(DefaultMaterial, ColorTexture);
	MATERIAL_VARIABLE_DEFINITION(DefaultMaterial, P);

    void DefaultMaterial::Initialize(Effect* effect)
    {
        Material::Initialize(effect);

        MATERIAL_VARIABLE_RETRIEVE(World);
        MATERIAL_VARIABLE_RETRIEVE(ViewProjection);
        MATERIAL_VARIABLE_RETRIEVE(CamPos);
        MATERIAL_VARIABLE_RETRIEVE(AmbientColor);
        MATERIAL_VARIABLE_RETRIEVE(DirectLights);
        MATERIAL_VARIABLE_RETRIEVE(PointLights);
        MATERIAL_VARIABLE_RETRIEVE(SpotLights);
        MATERIAL_VARIABLE_RETRIEVE(NumDirLight);
        MATERIAL_VARIABLE_RETRIEVE(NumPointLight);
        MATERIAL_VARIABLE_RETRIEVE(NumSpotLight);
        MATERIAL_VARIABLE_RETRIEVE(ColorTexture);
        MATERIAL_VARIABLE_RETRIEVE(P);

        D3D11_INPUT_ELEMENT_DESC inputElementDescriptions[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
        };

        CreateInputLayout("main11", "p0", inputElementDescriptions, ARRAYSIZE(inputElementDescriptions));
    }

    void DefaultMaterial::CreateVertexBuffer(ID3D11Device* device, const Mesh& mesh, ID3D11Buffer** vertexBuffer) const
    {
        const std::vector<XMFLOAT3>& sourceVertices = mesh.Vertices();
        std::vector<XMFLOAT3>* textureCoordinates = mesh.TextureCoordinates().at(0);
        assert(textureCoordinates->size() == sourceVertices.size());
        const std::vector<XMFLOAT3>& normals = mesh.Normals();
        assert(textureCoordinates->size() == sourceVertices.size());

        std::vector<DefaultMaterialVertex> vertices;
        vertices.reserve(sourceVertices.size());
        for (UINT i = 0; i < sourceVertices.size(); i++)
        {
            XMFLOAT3 position = sourceVertices.at(i);
            XMFLOAT3 uv = textureCoordinates->at(i);
            XMFLOAT3 normal = normals.at(i);
            vertices.push_back(DefaultMaterialVertex(XMFLOAT4(position.x, position.y, position.z, 1.0f), XMFLOAT2(uv.x, uv.y), normal));
        }

        CreateVertexBuffer(device, &vertices[0], vertices.size(), vertexBuffer);
    }

    void DefaultMaterial::CreateVertexBuffer(ID3D11Device* device, DefaultMaterialVertex* vertices, UINT vertexCount, ID3D11Buffer** vertexBuffer) const
    {
        D3D11_BUFFER_DESC vertexBufferDesc;
        ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
        vertexBufferDesc.ByteWidth = VertexSize() * vertexCount;
        vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
        vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA vertexSubResourceData;
        ZeroMemory(&vertexSubResourceData, sizeof(vertexSubResourceData));
        vertexSubResourceData.pSysMem = vertices;
        if (FAILED(device->CreateBuffer(&vertexBufferDesc, &vertexSubResourceData, vertexBuffer)))
        {
            throw GameException("ID3D11Device::CreateBuffer() failed.");
        }
    }

    UINT DefaultMaterial::VertexSize() const
    {
        return sizeof(DefaultMaterialVertex);
    }
}