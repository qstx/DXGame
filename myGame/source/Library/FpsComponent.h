#pragma once

#include "DrawableGameComponent.h"

namespace DirectX
{
    inline namespace DX11
    {
        class SpriteBatch;
        class SpriteFont;
    }
}

namespace Library
{
    class FpsComponent : public DrawableGameComponent
    {
        RTTI_DECLARATIONS(FpsComponent, DrawableGameComponent)

    public:
        FpsComponent();
        ~FpsComponent();

        XMFLOAT2& TextPosition();
        int FrameRate() const;

        virtual void Initialize() override;
        virtual void Update(const GameTime& gameTime) override;
        virtual void Draw(const GameTime& gameTime) override;

    private:
        FpsComponent(const FpsComponent& rhs);
        FpsComponent& operator=(const FpsComponent& rhs);
        
        SpriteBatch* mSpriteBatch;
        SpriteFont* mSpriteFont;
        XMFLOAT2 mTextPosition;

        int mFrameCount;
        int mFrameRate;
        double mLastTotalElapsedTime;
    };
}