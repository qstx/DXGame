#pragma once
#include "Common.h"

namespace Library
{
	class Texture
	{
	public:
		Texture();
		Texture(std::string file);
		ID3D11ShaderResourceView* mTextureShaderResourceView;
	};
}