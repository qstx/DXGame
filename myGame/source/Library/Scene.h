#pragma once
#include <string>
#include <vector>

namespace Library
{
    class Game;
    class GameTime;
    class Camera;
    class GameObject;
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
    protected:
        Scene(const Scene& rhs);
        Scene& operator=(const Scene& rhs);

        Game& mGame;
        Camera& mCamera;
        std::vector<GameObject*> mGameObjects;
    };
}