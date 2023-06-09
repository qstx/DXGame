#pragma once


#include "Game.h"

using namespace Library;

namespace Library
{
	class FirstPersonCamera;
	class RenderStateHelper;
	class Keyboard;
	class Mouse;
	class FpsComponent;
	class Scene;
	class GameObject;
}

namespace Rendering
{
	class TriangleDemo;
	class ModelFromFile;
	class ObjectDiffuseLight;
	class DefaultObject;

	class RenderingGame : public Game
	{
	public:
		RenderingGame(HINSTANCE instance, const std::wstring& windowClass, const std::wstring& windowTitle, int showCommand);
		~RenderingGame();

		virtual void Initialize() override;
		virtual void Update(const GameTime& gameTime) override;
		virtual void Draw(const GameTime& gameTime) override;
		virtual Camera* GetCamera() override;
		virtual Scene* GetScene() override;

	protected:
		RenderingGame() {};
		virtual void Shutdown() override;

	private:
		static const XMFLOAT4 BackgroundColor;
		FirstPersonCamera* mCamera;
		LPDIRECTINPUT8 mDirectInput;
		Keyboard* mKeyboard;
		Mouse* mMouse;

		FpsComponent* mFpsComponent;
		RenderStateHelper* mRenderStateHelper;
		Scene* mScene;
	};
}