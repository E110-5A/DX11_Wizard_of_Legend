#pragma once
#include "jsGraphics.h"


namespace js::graphics
{
	class GraphicDevice_DX11
	{
	public:
		GraphicDevice_DX11();
		~GraphicDevice_DX11();

	private:
		Microsoft::WRL::ComPtr<ID3D11Device>			mDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>		mContext;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>			mRenderTarget;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	mRenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>			mDepthStencilView;
		Microsoft::WRL::ComPtr<IDXGISwapChain>			mSwapChain;
	};
}