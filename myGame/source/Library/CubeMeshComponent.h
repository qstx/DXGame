#pragma once
#include "DrawableGameComponent.h"

using namespace Library;

namespace Library
{
	class Effect;
	class DirectionalLight;
	class RenderStateHelper;
}

namespace Rendering
{
	class DefaultMaterial;

	class CubeMeshComponent : public DrawableGameComponent
	{
		RTTI_DECLARATIONS(CubeMeshComponent, DrawableGameComponent)

	public:
		CubeMeshComponent(Game& game, const std::wstring shaderFilePath, const std::wstring texFilePath);
		virtual ~CubeMeshComponent();

		virtual void Initialize() override;
		virtual void Update(const GameTime& gameTime) override;
		virtual void Draw(const GameTime& gameTime) override;


	private:
		CubeMeshComponent();
		CubeMeshComponent(const CubeMeshComponent& rhs);
		CubeMeshComponent& operator=(const CubeMeshComponent& rhs);

		const std::wstring mShaderFilePath;
		const std::wstring mTexFilePath;

		Effect* mEffect;
		DefaultMaterial* mMaterial;
		ID3D11ShaderResourceView* mTextureShaderResourceView;
		ID3D11Buffer* mVertexBuffer;
		ID3D11Buffer* mIndexBuffer;
		UINT mIndexCount;

		XMFLOAT4X4 mWorldMatrix;

		RenderStateHelper* mRenderStateHelper;
	};
}
