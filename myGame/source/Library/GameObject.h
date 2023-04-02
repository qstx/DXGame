#pragma once
#include "Common.h"

#include <string>
#include <vector>


namespace Rendering
{
    class DefaultObject;
}
using namespace Rendering;
namespace Library
{
    class Game;
    class GameTime;
    class Camera;
    class GameComponent;
    class GameObject:public RTTI
    {
        RTTI_DECLARATIONS(GameObject,RTTI)

    public:
        GameObject(Game& game, Camera& camera);
        virtual ~GameObject();

		virtual void Initialize();
		virtual void Update(const GameTime& gameTime);
		virtual void Draw(const GameTime& gameTime);
		virtual void Destory();

        Game& GetGame();

    protected:
        GameObject(const GameObject& rhs);
        GameObject& operator=(const GameObject& rhs);

        Game& mGame;
        Camera* mCamera;
        std::vector<GameComponent*> mGameComponents;
    };
}