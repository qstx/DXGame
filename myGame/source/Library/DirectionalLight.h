#pragma once

#include "Common.h"
#include "Light.h"

namespace Library
{
	class DirectionalLightData
	{
	public:
		XMFLOAT4 color;
		XMFLOAT3 direct;
	};
	class DirectionalLight : public Light
	{
		RTTI_DECLARATIONS(DirectionalLight, Light)

	public:
		DirectionalLight(Game& game);
		virtual ~DirectionalLight();
		virtual void Initialize() override;
		virtual void Update(const GameTime& gameTime) override;

		const XMFLOAT3& Direction() const;
		const XMFLOAT3& Up() const;
		const XMFLOAT3& Right() const;

		XMVECTOR DirectionVector() const;
		XMVECTOR UpVector() const;
		XMVECTOR RightVector() const;
		void* GetData() const;

		void ApplyRotation(CXMMATRIX transform);
        void ApplyRotation(const XMFLOAT4X4& transform);

	protected:
		XMFLOAT3 mDirection;
		XMFLOAT3 mUp;
		XMFLOAT3 mRight;
		DirectionalLightData data;
	};
}

