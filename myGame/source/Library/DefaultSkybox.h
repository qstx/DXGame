#pragma once
#include <vector>
#include "GameObject.h"
#include "Common.h"
using namespace Library;

namespace Library
{
	class Camera;
	class Game;
	class Effect;
	class RenderStateHelper;
}

namespace Rendering
{
	class DefaultSkyboxMaterial;
	class DefaultSkybox :public GameObject
	{
		RTTI_DECLARATIONS(DefaultSkybox, GameObject)

	public:
		DefaultSkybox();
		virtual ~DefaultSkybox();
		virtual void Initialize() override;
		virtual void Update(const GameTime& gameTime) override;
		virtual void Draw(const GameTime& gameTime) override;
		virtual void Destory() override;

	protected:
		DefaultSkybox(const DefaultSkybox& rhs);
		DefaultSkybox& operator=(const DefaultSkybox& rhs);
	private:
		Effect* mEffect;
		DefaultSkyboxMaterial* mMaterial;
		RenderStateHelper* mRenderStateHelper;
	};
}