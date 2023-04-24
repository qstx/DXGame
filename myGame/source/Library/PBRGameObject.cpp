#include "PBRGameObject.h"
#include "RenderStateHelper.h"
#include "PBRMeshComponent.h"
#include "Game.h"
#include "RasterizerStates.h"

namespace Rendering
{
	RTTI_DEFINITIONS(PBRGameObject)

		PBRGameObject::PBRGameObject() :mRenderStateHelper(new RenderStateHelper())
	{
		mGameComponents.push_back(new PBRMeshComponent("Content\\Models\\bench.3ds", L"Content\\Effects\\PBREffect.cso", L"Content\\Textures\\bench.jpg"));
		mGameComponents[0]->As<PBRMeshComponent>()->SetPosition(-1.57f, 0.0f, 0.0f, 0.01f, 0.0f, 1.0f, 0.0f);
		mGameComponents.push_back(new PBRMeshComponent("Content\\Models\\Marry.obj", L"Content\\Effects\\PBREffect.cso", L"Content\\Textures\\MC003_Kozakura_Mari.png"));
	}
	PBRGameObject::~PBRGameObject()
	{
		DeleteObject(mRenderStateHelper);
	}
	void PBRGameObject::Draw(const GameTime& gamTime)
	{
		mRenderStateHelper->SaveAll();
		Game::GetInstance()->Direct3DDeviceContext()->RSSetState(RasterizerStates::DisabledCulling);
		GameObject::Draw(gamTime);
		mRenderStateHelper->RestoreAll();
	}
}