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
        Scene(Game& game, Camera& camera);
        virtual ~Scene();

        virtual void Initialize();
        virtual void Update(const GameTime& gameTime);
        virtual void Draw(const GameTime& gameTime);
        virtual void Shutdown();

        Game& GetGame();
        XMCOLOR& GetAmbientColor();
    protected:
        Scene(const Scene& rhs);
        Scene& operator=(const Scene& rhs);

        Game& mGame;
        Camera& mCamera;
        std::vector<GameObject*> mGameObjects;
    public:
        XMCOLOR mAmbientColor;
        //DirectionalLight* mMainDirectionalLight;
        std::vector<Light*> mLights;
        std::vector<DirectionalLight*> mDirectionalLights;
    };
}