#pragma once
#include <vector>
#include "GameObject.h"
#include "Common.h"
using namespace Library;

namespace Library
{
	class RenderStateHelper;
}

namespace Rendering
{
	class DemoGameObject:public GameObject
	{
		RTTI_DECLARATIONS(DemoGameObject,GameObject)

	public:
		DemoGameObject();
		virtual ~DemoGameObject();
		virtual void Draw(const GameTime& gamTime) override;

	protected:
		DemoGameObject(const DemoGameObject& rhs) = delete;
		DemoGameObject& operator=(const DemoGameObject& rhs) = delete;
	private:
		RenderStateHelper* mRenderStateHelper;
	};
}