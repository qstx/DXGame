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

	class MeshComponent : public DrawableGameComponent
	{
		RTTI_DECLARATIONS(MeshComponent, DrawableGameComponent)

	public:
		MeshComponent(const std::string modelFilePath, const std::wstring shaderFilePath, const std::wstring texFilePath);
		virtual ~MeshComponent();

		virtual void Initialize() override;
		virtual void Update(const GameTime& gameTime) override;
		virtual void Draw(const GameTime& gameTime) override;

		//add to support multiple model in the scene
		void SetPosition(const float rotateX, const float rotateY, const float rotateZ, const float scaleFactor, const float translateX, const float translateY, const float translateZ);

	private:
		MeshComponent();
		MeshComponent(const MeshComponent& rhs);
		MeshComponent& operator=(const MeshComponent& rhs);

		const std::string mModelFilePath;
		const std::wstring mShaderFilePath;
		const std::wstring mTexFilePath;

		Effect* mEffect;
		DefaultMaterial* mMaterial;
		ID3D11ShaderResourceView* mTextureShaderResourceView;
		std::vector<ID3D11Buffer*> mVertexBuffers;
		std::vector<ID3D11Buffer*> mIndexBuffers;
		std::vector <UINT> mIndexCounts;

		XMFLOAT4X4 mWorldMatrix;

		RenderStateHelper* mRenderStateHelper;
	};
}
