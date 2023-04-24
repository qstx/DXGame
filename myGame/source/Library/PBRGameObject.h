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
	class PBRGameObject :public GameObject
	{
		RTTI_DECLARATIONS(PBRGameObject, GameObject)

	public:
		PBRGameObject();
		virtual ~PBRGameObject();
		virtual void Draw(const GameTime& gamTime) override;

	protected:
		PBRGameObject(const PBRGameObject& rhs) = delete;
		PBRGameObject& operator=(const PBRGameObject& rhs) = delete;
	private:
		RenderStateHelper* mRenderStateHelper;
	};
}