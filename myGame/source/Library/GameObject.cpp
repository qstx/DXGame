#include "GameObject.h"
#include "Game.h"
#include "GameTime.h"
#include "GameComponent.h"
#include "DrawableGameComponent.h"
#include "DefaultObject.h"

namespace Library
{
	RTTI_DEFINITIONS(GameObject)

	GameObject::GameObject(Game& game,Camera& camera):
		mGame(game), mCamera(&camera)
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

	void GameObject::Destory()
	{
		for (GameComponent*& comp : mGameComponents)
		{
			DeleteObject(comp);
		}
	}

	Game& GameObject::GetGame()
	{
		return mGame;
	}
}