#pragma once

#include "GameComponent.h"

namespace Library
{
    class Camera;

    class DrawableGameComponent : public GameComponent
    {
        RTTI_DECLARATIONS(DrawableGameComponent, GameComponent)

    public:
        DrawableGameComponent();
        virtual ~DrawableGameComponent();

        bool Visible() const;
        void SetVisible(bool visible);

        virtual void Draw(const GameTime& gameTime);
        virtual void DrawPass(const GameTime& gameTime, std::string passName);

    protected:
        bool mVisible;

    private:
        DrawableGameComponent(const DrawableGameComponent& rhs) = delete;
        DrawableGameComponent& operator=(const DrawableGameComponent& rhs) = delete;
    };
}