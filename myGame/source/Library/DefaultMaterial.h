#pragma once
#include "Common.h"
#include "Material.h"

using namespace Library;

namespace Rendering
{
    typedef struct _DefaultMaterialVertex
    {
        XMFLOAT4 Position;
        XMFLOAT2 TextureCoordinates;
        XMFLOAT3 Normal;

        _DefaultMaterialVertex() {}

        _DefaultMaterialVertex(XMFLOAT4 position, XMFLOAT2 textureCoordinates, XMFLOAT3 normal)
            : Position(position), TextureCoordinates(textureCoordinates), Normal(normal)
        {
        }
    } DiffuseLightingMaterialVertex;

    class DefaultMaterial : public Material
    {
        RTTI_DECLARATIONS(DefaultMaterial, Material)

            MATERIAL_VARIABLE_DECLARATION(WorldViewProjection)
            MATERIAL_VARIABLE_DECLARATION(World)
            MATERIAL_VARIABLE_DECLARATION(CamPos)
            MATERIAL_VARIABLE_DECLARATION(AmbientColor)
            MATERIAL_VARIABLE_DECLARATION(LightColor)
            MATERIAL_VARIABLE_DECLARATION(LightDirection)
            MATERIAL_VARIABLE_DECLARATION(ColorTexture)

    public:
        DefaultMaterial();

        virtual void Initialize(Effect* effect) override;
        virtual void CreateVertexBuffer(ID3D11Device* device, const Mesh& mesh, ID3D11Buffer** vertexBuffer) const override;
        void CreateVertexBuffer(ID3D11Device* device, DiffuseLightingMaterialVertex* vertices, UINT vertexCount, ID3D11Buffer** vertexBuffer) const;
        virtual UINT VertexSize() const override;
    };
}

