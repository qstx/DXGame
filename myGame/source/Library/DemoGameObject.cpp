#include "DemoGameObject.h"
#include "DefaultObject.h"

namespace Rendering
{
	RTTI_DEFINITIONS(DemoGameObject)

	DemoGameObject::DemoGameObject(Game& game,Camera& camera):GameObject(game, camera)
	{
		mGameComponents.push_back(new DefaultObject(game, camera));
		mGameComponents[0]->As<DefaultObject>()->SetPosition(-1.57f, 0.0f, 0.0f, 0.01, 0.0f, 0.0f, 0.0f);
	}
	DemoGameObject::~DemoGameObject()
	{

	}
}