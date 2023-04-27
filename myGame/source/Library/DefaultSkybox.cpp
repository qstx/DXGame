#include "DefaultSkybox.h"
#include "CubeMeshComponent.h"
#include "RenderStateHelper.h"
#include "DepthStencilStates.h"
#include "RasterizerStates.h"
#include "Game.h"

namespace Rendering
{
	RTTI_DEFINITIONS(DefaultSkybox)

	DefaultSkybox::DefaultSkybox() :mRenderStateHelper(new RenderStateHelper())
	{
		mGameComponents.push_back(new CubeMeshComponent(L"Content\\Effects\\DefaultSkybox.cso", L"Content\\Textures\\desertcube1024.dds"));
	}
	DefaultSkybox::~DefaultSkybox()
	{
		DeleteObject(mRenderStateHelper);
	}
	void DefaultSkybox::Initialize()
	{
		GameObject::Initialize();
	}
	void DefaultSkybox::Update(const GameTime& gameTime)
	{
		GameObject::Update(gameTime);
	}
	void DefaultSkybox::Draw(const GameTime& gameTime)
	{
		mRenderStateHelper->SaveAll();
		Game::GetInstance()->Direct3DDeviceContext()->OMSetDepthStencilState(DepthStencilStates::DepthLessEqual_NoWrite, 0);
		Game::GetInstance()->Direct3DDeviceContext()->RSSetState(RasterizerStates::FrontCulling);
		GameObject::Draw(gameTime);
		mRenderStateHelper->RestoreAll();
	}
	void DefaultSkybox::DrawPass(const GameTime& gameTime, std::string passName)
	{
		mRenderStateHelper->SaveAll();
		Game::GetInstance()->Direct3DDeviceContext()->OMSetDepthStencilState(DepthStencilStates::DepthLessEqual_NoWrite, 0);
		Game::GetInstance()->Direct3DDeviceContext()->RSSetState(RasterizerStates::FrontCulling);
		GameObject::DrawPass(gameTime,passName);
		mRenderStateHelper->RestoreAll();
	}
	void DefaultSkybox::Destory()
	{
		GameObject::Destory();
	}
}