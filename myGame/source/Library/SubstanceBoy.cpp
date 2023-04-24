#include "SubstanceBoy.h"
#include "RenderStateHelper.h"
#include "RasterizerStates.h"
#include "PBRMeshComponent.h"
#include "Game.h"

namespace Rendering
{
	RTTI_DEFINITIONS(SubstanceBoy)

		SubstanceBoy::SubstanceBoy() :mRenderStateHelper(new RenderStateHelper())
	{
		mGameComponents.push_back(new PBRMeshComponent("Content\\Models\\substance_boy\\head.obj", L"Content\\Effects\\PBREffect.cso", L"Content\\Models\\substance_boy\\textures\\01_Head_Base_Color.png", L"Content\\Models\\substance_boy\\textures\\01_Head_Normal_DirectX.png", L"Content\\Models\\substance_boy\\textures\\01_Head_MetallicRoughness.png"));
		mGameComponents.push_back(new PBRMeshComponent("Content\\Models\\substance_boy\\body.obj", L"Content\\Effects\\PBREffect.cso", L"Content\\Models\\substance_boy\\textures\\02_Body_Base_Color.png", L"Content\\Models\\substance_boy\\textures\\02_Body_Normal_DirectX.png", L"Content\\Models\\substance_boy\\textures\\02_Body_MetallicRoughness.png"));
		mGameComponents.push_back(new PBRMeshComponent("Content\\Models\\substance_boy\\base.obj", L"Content\\Effects\\PBREffect.cso", L"Content\\Models\\substance_boy\\textures\\03_Base_Base_Color.png", L"Content\\Models\\substance_boy\\textures\\03_Base_Normal_DirectX.png", L"Content\\Models\\substance_boy\\textures\\03_Base_MetallicRoughness.png"));
		mGameComponents[0]->As<PBRMeshComponent>()->SetPosition(0.0f, 0.0f, 0.0f, 10.0f, 0.1f, 1.0f, 0.0f);
		mGameComponents[1]->As<PBRMeshComponent>()->SetPosition(0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 0.42f, 0.0f);
		mGameComponents[2]->As<PBRMeshComponent>()->SetPosition(0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f);
	}
	SubstanceBoy::~SubstanceBoy()
	{
		DeleteObject(mRenderStateHelper);
	}
	void SubstanceBoy::Draw(const GameTime& gamTime)
	{
		mRenderStateHelper->SaveAll();
		Game::GetInstance()->Direct3DDeviceContext()->RSSetState(RasterizerStates::DisabledCulling);
		GameObject::Draw(gamTime);
		mRenderStateHelper->RestoreAll();
	}
}