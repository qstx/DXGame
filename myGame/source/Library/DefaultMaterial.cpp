#include "DefaultMaterial.h"
#include "GameException.h"
#include "Mesh.h"

namespace Rendering
{
    RTTI_DEFINITIONS(DefaultMaterial)

    DefaultMaterial::DefaultMaterial():
        Material("main11"),
        MATERIAL_VARIABLE_INITIALIZATION(WorldViewProjection), MATERIAL_VARIABLE_INITIALIZATION(World),
        MATERIAL_VARIABLE_INITIALIZATION(CamPos),
        MATERIAL_VARIABLE_INITIALIZATION(AmbientColor), MATERIAL_VARIABLE_INITIALIZATION(LightColor),
        MATERIAL_VARIABLE_INITIALIZATION(LightDirection), MATERIAL_VARIABLE_INITIALIZATION(ColorTexture)
    {
    }

    MATERIAL_VARIABLE_DEFINITION(DefaultMaterial, WorldViewProjection)
    MATERIAL_VARIABLE_DEFINITION(DefaultMaterial, World)
    MATERIAL_VARIABLE_DEFINITION(DefaultMaterial, CamPos)
    MATERIAL_VARIABLE_DEFINITION(DefaultMaterial, AmbientColor)
    MATERIAL_VARIABLE_DEFINITION(DefaultMaterial, LightColor)
    MATERIAL_VARIABLE_DEFINITION(DefaultMaterial, LightDirection)
    MATERIAL_VARIABLE_DEFINITION(DefaultMaterial, ColorTexture)

    void DefaultMaterial::Initialize(Effect* effect)
    {
        Material::Initialize(effect);

        MATERIAL_VARIABLE_RETRIEVE(WorldViewProjection)
        MATERIAL_VARIABLE_RETRIEVE(World)
        MATERIAL_VARIABLE_RETRIEVE(CamPos)
        MATERIAL_VARIABLE_RETRIEVE(AmbientColor)
        MATERIAL_VARIABLE_RETRIEVE(LightColor)
        MATERIAL_VARIABLE_RETRIEVE(LightDirection)
        MATERIAL_VARIABLE_RETRIEVE(ColorTexture)

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

        std::vector<_DefaultMaterialVertex> vertices;
        vertices.reserve(sourceVertices.size());
        for (UINT i = 0; i < sourceVertices.size(); i++)
        {
            XMFLOAT3 position = sourceVertices.at(i);
            XMFLOAT3 uv = textureCoordinates->at(i);
            XMFLOAT3 normal = normals.at(i);
            vertices.push_back(_DefaultMaterialVertex(XMFLOAT4(position.x, position.y, position.z, 1.0f), XMFLOAT2(uv.x, uv.y), normal));
        }

        CreateVertexBuffer(device, &vertices[0], vertices.size(), vertexBuffer);
    }

    void DefaultMaterial::CreateVertexBuffer(ID3D11Device* device, _DefaultMaterialVertex* vertices, UINT vertexCount, ID3D11Buffer** vertexBuffer) const
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
        return sizeof(_DefaultMaterialVertex);
    }
}