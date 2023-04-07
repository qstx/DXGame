#include "DemoScene.h"
#include "GameTime.h"
#include "DemoGameObject.h"
#include "DirectionalLight.h"
#include "TriangleDemo.h"
#include "MatrixHelper.h"
#include "DefaultSkybox.h"

Library::DemoScene::DemoScene(Game& game, Camera& camera):
	Scene(game,camera)
{
	mGameObjects.push_back(new Rendering::DemoGameObject(game));
	mGameObjects.push_back(new Rendering::DefaultSkybox(game));
	//mLights.push_back(new DirectionalLight(game));
	//mMainDirectionalLight = new DirectionalLight(game);
	//mMainDirectionalLight->SetColor(1, 0, 0, 0.5);
	DirectionalLight* dl = new DirectionalLight(game);
	mDirectionalLights.push_back(dl);
	dl = new DirectionalLight(game);
	dl->SetColor(0, 0, 1, 0.2);
	mDirectionalLights.push_back(dl);
}

Library::DemoScene::~DemoScene()
{
}

void Library::DemoScene::Initialize()
{
	Scene::Initialize();
	for (DirectionalLight*& dl : mDirectionalLights)
		dl->Initialize();
}

void Library::DemoScene::Update(const GameTime& gameTime)
{
	Scene::Update(gameTime);
	static float rotateY=0;
	rotateY = gameTime.ElapsedGameTime()*0.78f;
	XMMATRIX RotationZ = XMMatrixRotationY(rotateY);
	mDirectionalLights[0]->ApplyRotation(RotationZ);
	for (DirectionalLight*& dl : mDirectionalLights)
		dl->Update(gameTime);
}

void Library::DemoScene::Shutdown()
{
	for (DirectionalLight*& dl : mDirectionalLights)
		DeleteObject(dl);
	Scene::Shutdown();
}
