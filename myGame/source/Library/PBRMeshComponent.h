#pragma once
#include "Common.h"
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
	class PBRMaterial;
	class PBRMeshComponent : public DrawableGameComponent
	{
		RTTI_DECLARATIONS(PBRMeshComponent, DrawableGameComponent)

	public:
		PBRMeshComponent(const std::string modelFilePath, const std::wstring shaderFilePath, const std::wstring albedoTexFilePath, const std::wstring normalTexFilePath = L"", const std::wstring metallicRoughnessTexFilePath = L"");
		virtual ~PBRMeshComponent();

		virtual void Initialize() override;
		virtual void Update(const GameTime& gameTime) override;
		virtual void Draw(const GameTime& gameTime) override;

		//add to support multiple model in the scene
		void SetPosition(const float rotateX, const float rotateY, const float rotateZ, const float scaleFactor, const float translateX, const float translateY, const float translateZ);

	private:
		PBRMeshComponent() = delete;
		PBRMeshComponent(const PBRMeshComponent& rhs) = delete;
		PBRMeshComponent& operator=(const PBRMeshComponent& rhs) = delete;

		const std::string mModelFilePath;
		const std::wstring mShaderFilePath;
		const std::wstring mAlbedoTexFilePath;
		const std::wstring mNormalTexFilePath;
		const std::wstring mMetallicRoughnessTexFilePath;

		Effect* mEffect;
		PBRMaterial* mMaterial;
		ID3D11ShaderResourceView* mAlbedoTextureShaderResourceView;
		ID3D11ShaderResourceView* mNormalTextureShaderResourceView;
		ID3D11ShaderResourceView* mMetallicRoughnessTextureShaderResourceView;
		std::vector<ID3D11Buffer*> mVertexBuffers;
		std::vector<ID3D11Buffer*> mIndexBuffers;
		std::vector <UINT> mIndexCounts;

		XMFLOAT4X4 mWorldMatrix;

		RenderStateHelper* mRenderStateHelper;
	};
}