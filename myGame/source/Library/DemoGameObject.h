#pragma once
#include <vector>
#include "GameObject.h"
#include "Common.h"
using namespace Library;

namespace Library
{
	class Camera;
	class Game;
}

namespace Rendering
{
	class DemoGameObject:public GameObject
	{
		RTTI_DECLARATIONS(DemoGameObject,GameObject)

	public:
		DemoGameObject(Game& game, Camera& camera);
		virtual ~DemoGameObject();

	protected:
		DemoGameObject(const DemoGameObject& rhs);
		DemoGameObject& operator=(const DemoGameObject& rhs);
	};
}