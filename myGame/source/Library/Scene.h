#pragma once
#include <string>
#include <vector>
#include "Common.h"

namespace Library
{
    class Game;
    class GameTime;
    class Camera;
    class GameObject;
    class Light;
    class DirectionalLight;
    class Scene
    {
    public:
        Scene(Camera& camera);
        virtual ~Scene();

        virtual void Initialize();
        virtual void Update(const GameTime& gameTime);
        virtual void Draw(const GameTime& gameTime);
        virtual void Shutdown();

        const XMVECTOR& GetAmbientColor();
    protected:
        Scene(const Scene& rhs) = delete;
        Scene& operator=(const Scene& rhs) = delete;

        Camera& mCamera;
        std::vector<GameObject*> mGameObjects;
    public:
        XMFLOAT4 mAmbientColor;
        std::vector<Light*> mLights;
        std::vector<DirectionalLight*> mDirectionalLights;
    };
}