#include "Scene.h"
#include "Game.h"
#include "Camera.h"
#include "GameObject.h"
namespace Library
{
	Scene::Scene(Game& game, Camera& camera):
		mGame(game),mCamera(camera),
		mAmbientColor(1, 1, 1, 0.3),
		mMainDirectionalLight(nullptr)
	{
	}

	Scene::~Scene()
	{
		for (GameObject*& go : mGameObjects)
		{
			DeleteObject(go);
		}
		for (Light*& light : mLights)
		{
			DeleteObject(light);
		}
		DeleteObject(mMainDirectionalLight);
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
			go->Destory();
		}
	}

	Game& Scene::GetGame()
	{
		return mGame;
	}
	XMCOLOR& Scene::GetAmbientColor()
	{
		return mAmbientColor;
	}
}
