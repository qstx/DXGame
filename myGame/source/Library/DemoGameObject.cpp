#include "DemoGameObject.h"
#include "MeshComponent.h"
#include "RenderStateHelper.h"
#include "RasterizerStates.h"
#include "DepthStencilStates.h"
#include "Game.h"

namespace Rendering
{
	RTTI_DEFINITIONS(DemoGameObject)

	DemoGameObject::DemoGameObject(Game& game):GameObject(game),mRenderStateHelper(new RenderStateHelper(game))
	{
		mGameComponents.push_back(new MeshComponent(game, "Content\\Models\\bench.3ds", L"Content\\Effects\\DefaultLighting.cso", L"Content\\Textures\\bench.jpg"));
		mGameComponents[0]->As<MeshComponent>()->SetPosition(-1.57f, 0.0f, 0.0f, 0.01f, 0.0f, 1.0f, 0.0f);
		mGameComponents.push_back(new MeshComponent(game, "Content\\Models\\Marry.obj", L"Content\\Effects\\DefaultLighting.cso", L"Content\\Textures\\MC003_Kozakura_Mari.png"));
	}
	DemoGameObject::~DemoGameObject()
	{
		DeleteObject(mRenderStateHelper);
	}
	void DemoGameObject::Draw(const GameTime& gamTime)
	{
		mRenderStateHelper->SaveAll();
		mGame.Direct3DDeviceContext()->RSSetState(RasterizerStates::DisabledCulling);
		GameObject::Draw(gamTime);
		mRenderStateHelper->RestoreAll();
	}
}