#include "DemoScene.h"
#include "GameTime.h"
#include "DemoGameObject.h"
#include "PBRGameObject.h"
#include "SubstanceBoy.h"
#include "DirectionalLight.h"
#include "TriangleDemo.h"
#include "MatrixHelper.h"
#include "DefaultSkybox.h"

Library::DemoScene::DemoScene(Camera& camera):
	Scene(camera)
{
	mSkybox = new Rendering::DefaultSkybox();
	mAmbientColor = XMFLOAT4(1, 1, 1, 0.05);
	mGameObjects.push_back(new Rendering::SubstanceBoy());
	DirectionalLight* dl = new DirectionalLight();
	dl->SetColor(1, 1, 1, 10);
	mDirectionalLights.push_back(dl);
}

Library::DemoScene::~DemoScene()
{
}

void Library::DemoScene::Initialize()
{
	mSkybox->Initialize();
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

void Library::DemoScene::Draw(const GameTime& gameTime)
{
	for (GameObject*& go : mGameObjects)
	{
		go->DrawPass(gameTime,"p0");
	}
	mSkybox->Draw(gameTime);
}

void Library::DemoScene::Shutdown()
{
	for (DirectionalLight*& dl : mDirectionalLights)
		DeleteObject(dl);
	Scene::Shutdown();
	mSkybox->Destory();
	DeleteObject(mSkybox);
}
