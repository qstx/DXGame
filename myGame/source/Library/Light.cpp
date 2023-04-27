#include "Light.h"
//#include "ColorHelper.h"

namespace Library
{
	RTTI_DEFINITIONS(Light)

	Light::Light()
		: mColor(1.0f,1.0f,1.0f,1.0f)
	{
	}

	Light::~Light()
	{
	}

	const XMFLOAT4& Light::Color() const
	{
		return mColor;
	}

	const XMVECTOR Light::ColorVector() const
	{
		return XMLoadFloat4(&mColor);
	}

	void Light::SetColor(FLOAT r, FLOAT g, FLOAT b, FLOAT a)
	{
		mColor = XMFLOAT4(r, g, b, a);
	}

	void Light::SetColor(XMFLOAT4 color)
	{
		mColor = color;
	}
}