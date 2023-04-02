#include "RenderingGame.h"
#include "GameException.h"
#include "FirstPersonCamera.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "TriangleDemo.h"
#include "ModelFromFile.h"
#include "FpsComponent.h"
#include "RenderStateHelper.h"
#include "ObjectDiffuseLight.h"
#include "DefaultObject.h"
#include "SamplerStates.h"
#include "RasterizerStates.h"
#include "DemoScene.h"
#include "DemoGameObject.h"

namespace Rendering
{
	const XMFLOAT4 RenderingGame::BackgroundColor = { 0.5f, 0.5f, 0.5f, 1.0f };

    RenderingGame::RenderingGame(HINSTANCE instance, const std::wstring& windowClass, const std::wstring& windowTitle, int showCommand)
        :  Game(instance, windowClass, windowTitle, showCommand),
        mDirectInput(nullptr),
        mKeyboard(nullptr),
        mMouse(nullptr),
        mFpsComponent(nullptr),
        mRenderStateHelper(nullptr),
        mScene(nullptr)
    {
        mDepthStencilBufferEnabled = true;
        mMultiSamplingEnabled = true;
    }

    RenderingGame::~RenderingGame()
    {
    }

    void RenderingGame::Initialize()
    {
        mCamera = new FirstPersonCamera(*this);
        mComponents.push_back(mCamera);
        mServices.AddService(Camera::TypeIdClass(), mCamera);

        if (FAILED(DirectInput8Create(mInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&mDirectInput, nullptr)))
        {
            throw GameException("DirectInput8Create() failed");
        }
        mKeyboard = new Keyboard(*this, mDirectInput);
        mComponents.push_back(mKeyboard);
        mServices.AddService(Keyboard::TypeIdClass(), mKeyboard);

        mMouse = new Mouse(*this, mDirectInput);
        mComponents.push_back(mMouse);
        mServices.AddService(Mouse::TypeIdClass(), mMouse);

        mFpsComponent = new FpsComponent(*this);
        mFpsComponent->Initialize();
        mRenderStateHelper = new RenderStateHelper(*this);
        RasterizerStates::Initialize(mDirect3DDevice);
        SamplerStates::Initialize(mDirect3DDevice);

        Game::Initialize();
		mCamera->SetPosition(0.0f, 0.0f, 15.0f);

        mScene = new DemoScene(*this, *mCamera);
        mScene->Initialize();
    }

    void RenderingGame::Shutdown()
    {
        mScene->Shutdown();
        DeleteObject(mScene);

        RasterizerStates::Release();
        SamplerStates::Release();
        Game::Shutdown();

		DeleteObject(mFpsComponent);
		DeleteObject(mRenderStateHelper);
        DeleteObject(mCamera);
        DeleteObject(mKeyboard);
        DeleteObject(mMouse);
        ReleaseObject(mDirectInput);
    }

    void RenderingGame::Update(const GameTime &gameTime)
    {
        if (mKeyboard->WasKeyPressedThisFrame(DIK_ESCAPE))
            Exit();
        mScene->Update(gameTime);
        mFpsComponent->Update(gameTime);
        Game::Update(gameTime);
    }

    void RenderingGame::Draw(const GameTime &gameTime)
    {
        mDirect3DDeviceContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&BackgroundColor));
        mDirect3DDeviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

        mScene->Draw(gameTime);
        mRenderStateHelper->SaveAll();
        mFpsComponent->Draw(gameTime);
        mRenderStateHelper->RestoreAll();

        Game::Draw(gameTime);
       
        HRESULT hr = mSwapChain->Present(0, 0);
        if (FAILED(hr))
        {
            throw GameException("IDXGISwapChain::Present() failed.", hr);
        }
    }
}