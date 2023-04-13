#include "DepthStencilStates.h"
#include "GameException.h"

namespace Library
{
	ID3D11DepthStencilState* DepthStencilStates::DepthLessEqual_NoWrite = nullptr;

	void DepthStencilStates::Initialize(ID3D11Device* direct3DDevice)
	{
		assert(direct3DDevice != nullptr);

		CD3D11_DEPTH_STENCIL_DESC depthStencilStateDesc(CD3D11_DEFAULT{});
		ZeroMemory(&depthStencilStateDesc, sizeof(depthStencilStateDesc));
		depthStencilStateDesc.DepthEnable = true;
		depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		HRESULT hr = direct3DDevice->CreateDepthStencilState(&depthStencilStateDesc, &DepthLessEqual_NoWrite);
		if (FAILED(hr))
		{
			throw GameException("ID3D11Device::CreateDepthStencilState() failed.", hr);
		}
	}

	void DepthStencilStates::Release()
	{
		ReleaseObject(DepthLessEqual_NoWrite);
	}
}