#pragma once
#include <vector>
#include "GameObject.h"
#include "Common.h"
using namespace Library;

namespace Library
{
	class Camera;
	class Game;
	class RenderStateHelper;
}

namespace Rendering
{
	class DemoGameObject:public GameObject
	{
		RTTI_DECLARATIONS(DemoGameObject,GameObject)

	public:
		DemoGameObject(Game& game);
		virtual ~DemoGameObject();
		virtual void Draw(const GameTime& gamTime) override;

	protected:
		DemoGameObject(const DemoGameObject& rhs);
		DemoGameObject& operator=(const DemoGameObject& rhs);
	private:
		RenderStateHelper* mRenderStateHelper;
	};
}