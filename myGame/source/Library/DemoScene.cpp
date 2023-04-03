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
	mLights.push_back(new DirectionalLight(game));
	mMainDirectionalLight = new DirectionalLight(game);
}

Library::DemoScene::~DemoScene()
{
}

void Library::DemoScene::Update(const GameTime& gameTime)
{
	static float rotateY=0;
	rotateY = gameTime.ElapsedGameTime()*3.14f;
	XMMATRIX RotationZ = XMMatrixRotationY(rotateY);
	mMainDirectionalLight->ApplyRotation(RotationZ);
}
