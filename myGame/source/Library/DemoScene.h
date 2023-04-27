#pragma once
#include "Scene.h"
#include "DefaultSkybox.h"
using namespace Rendering;
namespace Rendering
{
	class DefaultSkybox;
}
namespace Library
{
	class DemoScene :public Scene
	{
	public:
		DemoScene(Camera& camera);
		~DemoScene();

		virtual void Initialize() override;
		virtual void Update(const GameTime& gameTime) override;
		virtual void Draw(const GameTime& gameTime) override;
		virtual void Shutdown() override;
	protected:
		DemoScene(const Scene& rhs);
		DemoScene& operator=(const Scene& rhs);
		DefaultSkybox* mSkybox;
	};
}