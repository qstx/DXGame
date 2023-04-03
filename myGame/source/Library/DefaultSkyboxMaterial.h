#pragma once
#pragma once
#include "Common.h"
#include "Material.h"

using namespace Library;

namespace Rendering
{
    typedef struct _DefaultSkyboxMaterialVertex
    {
        XMFLOAT4 Position;
        XMFLOAT2 TextureCoordinates;

        _DefaultSkyboxMaterialVertex() {}

        _DefaultSkyboxMaterialVertex(XMFLOAT4 position, XMFLOAT2 textureCoordinates, XMFLOAT3 normal)
            : Position(position), TextureCoordinates(textureCoordinates)
        {
        }
    } DiffuseLightingMaterialVertex;

    class DefaultSkyboxMaterial : public Material
    {
        RTTI_DECLARATIONS(DefaultSkyboxMaterial, Material)

        MATERIAL_VARIABLE_DECLARATION(SkyboxTexture0)
        MATERIAL_VARIABLE_DECLARATION(SkyboxTexture1)
        MATERIAL_VARIABLE_DECLARATION(SkyboxTexture2)
        MATERIAL_VARIABLE_DECLARATION(SkyboxTexture3)
        MATERIAL_VARIABLE_DECLARATION(SkyboxTexture4)
        MATERIAL_VARIABLE_DECLARATION(SkyboxTexture5)

    public:
        DefaultSkyboxMaterial();

        virtual void Initialize(Effect* effect) override;
        virtual void CreateVertexBuffer(ID3D11Device* device, const Mesh& mesh, ID3D11Buffer** vertexBuffer) const override;
        void CreateVertexBuffer(ID3D11Device* device, DiffuseLightingMaterialVertex* vertices, UINT vertexCount, ID3D11Buffer** vertexBuffer) const;
        virtual UINT VertexSize() const override;
    };
}

