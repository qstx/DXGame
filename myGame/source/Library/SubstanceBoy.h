#pragma once
#include "Common.h"
#include "GameObject.h"

using namespace Library;
namespace Library
{
	class RenderStateHelper;
}
namespace Rendering
{
	class SubstanceBoy :public GameObject
	{
		RTTI_DECLARATIONS(SubstanceBoy, GameObject)

	public:
		SubstanceBoy();
		virtual ~SubstanceBoy();
		virtual void Draw(const GameTime& gamTime) override;

	protected:
		SubstanceBoy(const SubstanceBoy& rhs) = delete;
		SubstanceBoy& operator=(const SubstanceBoy& rhs) = delete;
	private:
		RenderStateHelper* mRenderStateHelper;
	};
}