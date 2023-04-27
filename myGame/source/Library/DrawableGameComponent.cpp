#include "DrawableGameComponent.h"
#include "Game.h"

namespace Library
{
	RTTI_DEFINITIONS(DrawableGameComponent)

	DrawableGameComponent::DrawableGameComponent()
		: GameComponent(), mVisible(true)
	{
	}

	DrawableGameComponent::~DrawableGameComponent()
	{
	}

	bool DrawableGameComponent::Visible() const
	{
		return mVisible;
	}

	void DrawableGameComponent::SetVisible(bool visible)
	{
		mVisible = visible;
	}

	void DrawableGameComponent::Draw(const GameTime& gameTime)
	{
	}
	void DrawableGameComponent::DrawPass(const GameTime& gameTime, std::string pasaName)
	{
	}
}