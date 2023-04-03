#pragma once
#include "DrawableGameComponent.h"

namespace Library
{
    class Effect;
    class Technique;
    class Pass;
    class Variable;
    class Material;
	class CubeMeshComponent:public DrawableGameComponent
	{
        RTTI_DECLARATIONS(CubeMeshComponent, DrawableGameComponent)

    public:
        CubeMeshComponent(Game& game, Camera& camera);
        ~CubeMeshComponent();

        virtual void Initialize() override;
        virtual void Update(const GameTime& gameTime) override;
        virtual void Draw(const GameTime& gameTime) override;

    private:
        typedef struct _TextureMappingVertex
        {
            XMFLOAT4 Position;
            XMFLOAT2 TextureCoordinates;
            _TextureMappingVertex() {}
            _TextureMappingVertex(XMFLOAT4 position, XMFLOAT2 textureCoordinates)
                : Position(position), TextureCoordinates(textureCoordinates)
            {
            }
        } TextureMappingVertex;


        CubeMeshComponent();
        CubeMeshComponent(const CubeMeshComponent& rhs);
        CubeMeshComponent& operator=(const CubeMeshComponent& rhs);


        Effect *aEffect;
        Technique* aTechnique;
        Pass* aPass;
        Material* aMaterial;
        //ID3DX11Effect* mEffect;
        //ID3DX11EffectTechnique* mTechnique;
        //ID3DX11EffectPass* mPass;
        ID3DX11EffectMatrixVariable* mWvpVariable;

        ID3D11ShaderResourceView* mTextureShaderResourceView;
        ID3DX11EffectShaderResourceVariable* mColorTextureVariable;

        ID3D11InputLayout* mInputLayout;
        ID3D11Buffer* mVertexBuffer;
        ID3D11Buffer* mIndexBuffer;

        XMFLOAT4X4 mWorldMatrix;
	};
}