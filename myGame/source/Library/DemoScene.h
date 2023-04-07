#pragma once
#include "Scene.h"

namespace Library
{
	class DemoScene :public Scene
	{
	public:
		DemoScene(Game& game, Camera& camera);
		~DemoScene();

		virtual void Initialize() override;
		virtual void Update(const GameTime& gameTime) override;
		virtual void Shutdown() override;
	protected:
		DemoScene(const Scene& rhs);
		DemoScene& operator=(const Scene& rhs);
	};
}