#include "Scene.h"
#include "Game.h"
#include "Camera.h"
#include "GameObject.h"
namespace Library
{
	Scene::Scene(Game& game, Camera& camera):
		mGame(game)
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{
		for (GameObject*& go : mGameObjects)
		{
			go->Initialize();
		}
	}

	void Scene::Update(const GameTime& gameTime)
	{
		for (GameObject*& go : mGameObjects)
		{
			go->Update(gameTime);
		}
	}

	void Scene::Draw(const GameTime& gameTime)
	{
		for (GameObject*& go : mGameObjects)
		{
			go->Draw(gameTime);
		}
	}

	void Scene::Shutdown()
	{
		for (GameObject*& go : mGameObjects)
		{
			go->Shutdown();
		}
	}

	Game& Scene::GetGame()
	{
		return mGame;
	}
}
