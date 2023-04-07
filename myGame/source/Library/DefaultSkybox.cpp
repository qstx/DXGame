#include "DefaultSkybox.h"
#include "CubeMeshComponent.h"
namespace Rendering
{
	RTTI_DEFINITIONS(DefaultSkybox)

	DefaultSkybox::DefaultSkybox(Game& game) :GameObject(game)
	{
		mGameComponents.push_back(new CubeMeshComponent(game, L"Content\\Effects\\DefaultLighting.cso", L"Content\\Textures\\bench.jpg"));
	}
	DefaultSkybox::~DefaultSkybox()
	{

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
		GameObject::Draw(gameTime);
	}
	void DefaultSkybox::Destory()
	{
		GameObject::Destory();
	}
}