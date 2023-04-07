#include "DemoGameObject.h"
#include "MeshComponent.h"

namespace Rendering
{
	RTTI_DEFINITIONS(DemoGameObject)

	DemoGameObject::DemoGameObject(Game& game):GameObject(game)
	{
		mGameComponents.push_back(new MeshComponent(game, "Content\\Models\\bench.3ds", L"Content\\Effects\\DefaultLighting.cso", L"Content\\Textures\\bench.jpg"));
		mGameComponents[0]->As<MeshComponent>()->SetPosition(-1.57f, 0.0f, 0.0f, 0.01f, 0.0f, 0.0f, 0.0f);
		mGameComponents.push_back(new MeshComponent(game, "Content\\Models\\Marry.obj", L"Content\\Effects\\DefaultLighting.cso", L"Content\\Textures\\MC003_Kozakura_Mari.png"));
	}
	DemoGameObject::~DemoGameObject()
	{

	}
}