#include "GameObject.h"
#include "Game.h"
#include "GameTime.h"
#include "GameComponent.h"
#include "DrawableGameComponent.h"
#include "DefaultObject.h"

namespace Library
{
	RTTI_DEFINITIONS(GameObject)

	GameObject::GameObject()
	{

	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Initialize()
	{
		for (GameComponent*& comp : mGameComponents)
		{
			comp->Initialize();
		}
	}

	void GameObject::Update(const GameTime& gameTime)
	{
		for (GameComponent*& comp : mGameComponents)
		{
			comp->Update(gameTime);
		}
	}

	void GameObject::Draw(const GameTime& gameTime)
	{
		DrawableGameComponent* dComp = nullptr;
		for (GameComponent*& comp : mGameComponents)
		{
			dComp = (*comp).As<DrawableGameComponent>();
			if (dComp)
				dComp->Draw(gameTime);
		}
	}

	void GameObject::DrawPass(const GameTime& gameTime, std::string passName)
	{
		DrawableGameComponent* dComp = nullptr;
		for (GameComponent*& comp : mGameComponents)
		{
			dComp = (*comp).As<DrawableGameComponent>();
			if (dComp)
				dComp->DrawPass(gameTime,passName);
		}
	}

	void GameObject::Destory()
	{
		for (GameComponent*& comp : mGameComponents)
		{
			DeleteObject(comp);
		}
	}
}