#include "DemoScene.h"
#include "DemoGameObject.h"

Library::DemoScene::DemoScene(Game& game, Camera& camera):
	Scene(game,camera)
{
	mGameObjects.push_back(new Rendering::DemoGameObject(game, camera));
}

Library::DemoScene::~DemoScene()
{
}
