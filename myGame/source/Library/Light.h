#pragma once

#include "Common.h"
#include "GameComponent.h"

namespace Library
{
	class Light : public GameComponent
	{
		RTTI_DECLARATIONS(Light, GameComponent)

	public:
		Light();
		virtual ~Light();

		const XMFLOAT4& Color() const;
		const XMVECTOR ColorVector() const;
		void SetColor(FLOAT r, FLOAT g, FLOAT b, FLOAT a);
		void SetColor(XMFLOAT4 color);

	protected:
		XMFLOAT4 mColor;
	};
}

