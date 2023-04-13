#pragma once

#include "Common.h"

namespace Library
{
	class DepthStencilStates
	{
	public:
		static ID3D11DepthStencilState* DepthLessEqual_NoWrite;

		static void Initialize(ID3D11Device* direct3DDevice);
		static void Release();

	private:
		DepthStencilStates();
		DepthStencilStates(const DepthStencilStates& rhs);
		DepthStencilStates& operator=(const DepthStencilStates& rhs);
	};
}