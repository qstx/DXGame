#pragma once
#include <vector>
#include "DrawableGameComponent.h"
namespace Library
{
	class Mesh;
	class MeshComponent :public DrawableGameComponent
	{
	public:
		std::vector<Mesh> mMeshes;
		// Í¨¹ý DrawableGameComponent ¼Ì³Ð
		virtual void Draw(const GameTime& gameTime) override;
	};
}