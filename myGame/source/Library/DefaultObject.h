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

	class DefaultObject : public DrawableGameComponent
	{
		RTTI_DECLARATIONS(DefaultObject, DrawableGameComponent)

	public:
		DefaultObject(Game& game);
		virtual ~DefaultObject();

		virtual void Initialize() override;
		virtual void Update(const GameTime& gameTime) override;
		virtual void Draw(const GameTime& gameTime) override;

		//add to support multiple model in the scene
		void SetPosition(const float rotateX, const float rotateY, const float rotateZ, const float scaleFactor, const float translateX, const float translateY, const float translateZ);

	private:
		DefaultObject();
		DefaultObject(const DefaultObject& rhs);
		DefaultObject& operator=(const DefaultObject& rhs);

		void UpdateAmbientLight(const GameTime& gameTime);
		void UpdateDirectionalLight(const GameTime& gameTime);

		Effect* mEffect;
		DefaultMaterial* mMaterial;
		ID3D11ShaderResourceView* mTextureShaderResourceView;
		ID3D11Buffer* mVertexBuffer;
		ID3D11Buffer* mIndexBuffer;
		UINT mIndexCount;

		XMCOLOR mAmbientColor;
		DirectionalLight* mDirectionalLight;
		XMFLOAT4X4 mWorldMatrix;

		RenderStateHelper* mRenderStateHelper;
	};
}
