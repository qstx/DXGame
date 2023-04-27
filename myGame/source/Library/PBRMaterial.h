#pragma once
#include "Common.h"
#include "Material.h"

using namespace Library;

namespace Rendering
{
    typedef struct _PBRMaterialVertex
    {
        XMFLOAT4 Position;
        XMFLOAT2 TextureCoordinates;
        XMFLOAT3 Normal;
        XMFLOAT3 Tangent;
        XMFLOAT3 Bitangent;

        _PBRMaterialVertex() {}

        _PBRMaterialVertex(XMFLOAT4 position, XMFLOAT2 textureCoordinates, XMFLOAT3 normal, XMFLOAT3 tangent, XMFLOAT3 bitangent)
            : Position(position), TextureCoordinates(textureCoordinates), Normal(normal),
            Tangent(tangent),Bitangent(bitangent)
        {
        }
    } PBRMaterialVertex;

    class PBRMaterial : public Material
    {
        RTTI_DECLARATIONS(PBRMaterial, Material)

            MATERIAL_VARIABLE_DECLARATION(World)
            MATERIAL_VARIABLE_DECLARATION(ViewProjection)
            MATERIAL_VARIABLE_DECLARATION(CamPos)
            MATERIAL_VARIABLE_DECLARATION(AmbientColor)
            MATERIAL_VARIABLE_DECLARATION(DirectLights)
            MATERIAL_VARIABLE_DECLARATION(PointLights)
            MATERIAL_VARIABLE_DECLARATION(SpotLights)
            MATERIAL_VARIABLE_DECLARATION(NumDirLight)
            MATERIAL_VARIABLE_DECLARATION(NumPointLight)
            MATERIAL_VARIABLE_DECLARATION(NumSpotLight)
            MATERIAL_VARIABLE_DECLARATION(AlbedoTexture)
            MATERIAL_VARIABLE_DECLARATION(NormalTexture)
            MATERIAL_VARIABLE_DECLARATION(MetallicRoughnessTexture)

    public:
        PBRMaterial();

        virtual void Initialize(Effect* effect) override;
        virtual void CreateVertexBuffer(ID3D11Device* device, const Mesh& mesh, ID3D11Buffer** vertexBuffer) const override;
        void CreateVertexBuffer(ID3D11Device* device, PBRMaterialVertex* vertices, UINT vertexCount, ID3D11Buffer** vertexBuffer) const;
        virtual UINT VertexSize() const override;
    };
}