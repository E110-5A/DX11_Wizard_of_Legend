#include "jsGraphicDevice_DX11.h"
#include "jsApplication.h"
#include "jsRenderer.h"
#include "jsConstantBuffer.h"
#include "jsMesh.h"

extern js::Application application;

namespace js::graphics
{
	GraphicDevice_DX11::GraphicDevice_DX11(ValidationMode validationMode)
	{
		HWND hwnd = application.GetHwnd();
		UINT DeviceFlag = D3D11_CREATE_DEVICE_DEBUG;
		D3D_FEATURE_LEVEL FeatureLevel = (D3D_FEATURE_LEVEL)0;
		HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, DeviceFlag, nullptr
			, 0, D3D11_SDK_VERSION, mDevice.GetAddressOf(), &FeatureLevel, mContext.GetAddressOf());

		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.OutputWindow = hwnd;
		swapChainDesc.Windowed = true;
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		swapChainDesc.BufferDesc.Width = application.GetWidth();
		swapChainDesc.BufferDesc.Height = application.GetHeight();
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 144;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		if (!CreateSwapChain(&swapChainDesc))
			return;

		hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)mRenderTarget.GetAddressOf());

		hr = mDevice->CreateRenderTargetView(mRenderTarget.Get(), nullptr, mRenderTargetView.GetAddressOf());

		D3D11_TEXTURE2D_DESC depthBuffer = {};
		depthBuffer.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		depthBuffer.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthBuffer.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		depthBuffer.CPUAccessFlags = 0;


		depthBuffer.Width = application.GetWidth();
		depthBuffer.Height = application.GetHeight();
		depthBuffer.ArraySize = 1;
		depthBuffer.SampleDesc.Count = 1;
		depthBuffer.SampleDesc.Quality = 0;
		depthBuffer.MipLevels = 0;
		depthBuffer.MiscFlags = 0;

		if (!CreateTexture(&depthBuffer, mDepthStencilBuffer.GetAddressOf()))
			return;

		if (FAILED(mDevice->CreateDepthStencilView(mDepthStencilBuffer.Get(), nullptr, mDepthStencilView.GetAddressOf())))
			return;

		RECT windowRect;
		GetClientRect(application.GetHwnd(), &windowRect);
		mViewPort = { 0.f, 0.f, FLOAT(windowRect.right - windowRect.left), FLOAT(windowRect.bottom - windowRect.top), 0.f, 1.0f };
		BindViewports(&mViewPort);
		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
	}
	GraphicDevice_DX11::~GraphicDevice_DX11()
	{
		renderer::Release();
	}

	bool GraphicDevice_DX11::CreateSwapChain(DXGI_SWAP_CHAIN_DESC* desc)
	{
		Microsoft::WRL::ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
		Microsoft::WRL::ComPtr<IDXGIAdapter> pDXGIAdapter = nullptr;
		Microsoft::WRL::ComPtr<IDXGIFactory> pDXGIFactory = nullptr;

		if (FAILED(mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf())))
			return false;
		if (FAILED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pDXGIAdapter.GetAddressOf())))
			return false;
		if (FAILED(pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pDXGIFactory.GetAddressOf())))
			return false;
		if (FAILED(pDXGIFactory->CreateSwapChain(mDevice.Get(), desc, mSwapChain.GetAddressOf())))
			return false;

		return true;
	}
	bool GraphicDevice_DX11::CreateTexture(D3D11_TEXTURE2D_DESC* desc, ID3D11Texture2D** ppTexture2D)
	{
		if (FAILED(mDevice->CreateTexture2D(desc, nullptr, ppTexture2D)))
			return false;
		return true;
	}
	bool GraphicDevice_DX11::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* desc, UINT NumElements, const void* byteCode, SIZE_T bytecodeLength, ID3D11InputLayout** ppInputLayout)
	{
		if (FAILED(mDevice->CreateInputLayout(desc, NumElements, byteCode, bytecodeLength, ppInputLayout)))
			return false;
		return true;
	}
	bool GraphicDevice_DX11::CreateBuffer(D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data, ID3D11Buffer** buffer)
	{
		if (FAILED(mDevice->CreateBuffer(desc, data, buffer)))
			return false;
		return true;
	}
	bool GraphicDevice_DX11::CreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11VertexShader** ppVertexShader)
	{
		if (FAILED(mDevice->CreateVertexShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader)))
			return false;
		return true;
	}
	bool GraphicDevice_DX11::CreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11PixelShader** ppPixelShader)
	{
		if (FAILED(mDevice->CreatePixelShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppPixelShader)))
			return false;
		return true;
	}
	bool GraphicDevice_DX11::CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState)
	{
		if (FAILED(mDevice->CreateSamplerState(pSamplerDesc, ppSamplerState)))
			return false;
		return true;
	}
	void GraphicDevice_DX11::BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
	{
		mContext->IASetPrimitiveTopology(topology);
	}
	void GraphicDevice_DX11::BindInputLayout(ID3D11InputLayout* pInputLayout)
	{
		mContext->IASetInputLayout(pInputLayout);
	}
	void GraphicDevice_DX11::BindVertexBuffer(UINT startSlot, UINT NumBuffers, ID3D11Buffer* const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets)
	{
		mContext->IASetVertexBuffers(startSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
	}
	void GraphicDevice_DX11::BindIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT format, UINT offset)
	{
		mContext->IASetIndexBuffer(pIndexBuffer, format, offset);
	}
	void GraphicDevice_DX11::BindVertexShader(ID3D11VertexShader* pVertexShader, ID3D11ClassInstance* const* ppClassInstances, UINT numClassInstances)
	{
		mContext->VSSetShader(pVertexShader, ppClassInstances, numClassInstances);
	}
	void GraphicDevice_DX11::BindPixelShader(ID3D11PixelShader* pPixelShader, ID3D11ClassInstance* const* ppClassInstances, UINT numClassInstances)
	{
		mContext->PSSetShader(pPixelShader, ppClassInstances, numClassInstances);
	}
	void GraphicDevice_DX11::BindViewports(D3D11_VIEWPORT* viewPort)
	{
		mContext->RSSetViewports(1, viewPort);
	}
	void GraphicDevice_DX11::BindConstantBuffer(ID3D11Buffer* buffer, void* data, UINT size)
	{
		D3D11_MAPPED_SUBRESOURCE sub = {};
		mContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);
		memcpy(sub.pData, data, size);
		mContext->Unmap(buffer, 0);
	}
	void GraphicDevice_DX11::SetConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer)
	{
		switch (stage)
		{
		case eShaderStage::VS:
			mContext->VSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::HS:
			mContext->HSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::DS:
			mContext->DSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::GS:
			mContext->GSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::PS:
			mContext->PSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::CS:
			mContext->CSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		default:
			break;
		}
	}
	void GraphicDevice_DX11::SetShaderResource(eShaderStage stage, UINT slot, ID3D11ShaderResourceView* const* ppShdaerResourceViews)
	{
		switch (stage)
		{
		case eShaderStage::VS:
			mContext->VSSetShaderResources(slot, 1, ppShdaerResourceViews);
			break;
		case eShaderStage::HS:
			mContext->HSSetShaderResources(slot, 1, ppShdaerResourceViews);
			break;
		case eShaderStage::DS:
			mContext->DSSetShaderResources(slot, 1, ppShdaerResourceViews);
			break;
		case eShaderStage::GS:
			mContext->GSSetShaderResources(slot, 1, ppShdaerResourceViews);
			break;
		case eShaderStage::PS:
			mContext->PSSetShaderResources(slot, 1, ppShdaerResourceViews);
			break;
		case eShaderStage::CS:
			mContext->CSSetShaderResources(slot, 1, ppShdaerResourceViews);
			break;
		default:
			break;
		}
	}
	void GraphicDevice_DX11::BindSamplers(eShaderStage stage, UINT slot, UINT numSamplers, ID3D11SamplerState* const* ppSamplers)
	{
		switch (stage)
		{
		case eShaderStage::VS:
			mContext->VSSetSamplers(slot, numSamplers, ppSamplers);
			break;
		case eShaderStage::HS:
			mContext->HSSetSamplers(slot, numSamplers, ppSamplers);
			break;
		case eShaderStage::DS:
			mContext->DSSetSamplers(slot, numSamplers, ppSamplers);
			break;
		case eShaderStage::GS:
			mContext->GSSetSamplers(slot, numSamplers, ppSamplers);
			break;
		case eShaderStage::PS:
			mContext->PSSetSamplers(slot, numSamplers, ppSamplers);
			break;
		case eShaderStage::CS:
			mContext->CSSetSamplers(slot, numSamplers, ppSamplers);
			break;
		default:
			break;
		}
	}
	void GraphicDevice_DX11::BindsSamplers(UINT slot, UINT numSamplers, ID3D11SamplerState* const* ppSamplers)
	{
		mContext->VSSetSamplers(slot, numSamplers, ppSamplers);
		mContext->HSSetSamplers(slot, numSamplers, ppSamplers);
		mContext->DSSetSamplers(slot, numSamplers, ppSamplers);
		mContext->GSSetSamplers(slot, numSamplers, ppSamplers);
		mContext->PSSetSamplers(slot, numSamplers, ppSamplers);
	}

	void GraphicDevice_DX11::Clear()
	{
		FLOAT backgroundColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		mContext->ClearRenderTargetView(mRenderTargetView.Get(), backgroundColor);
		mContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
	}
	void GraphicDevice_DX11::AdjustViewPorts()
	{
		RECT windowRect;
		GetClientRect(application.GetHwnd(), &windowRect);
		mViewPort = { 0.f, 0.f, FLOAT(windowRect.right - windowRect.left), FLOAT(windowRect.bottom - windowRect.top), 0.f, 1.0f };
		BindViewports(&mViewPort);
		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
	}
	void GraphicDevice_DX11::Draw()
	{
		mContext->Draw(0, 0);
		
	}
	void GraphicDevice_DX11::DrawIndexed(UINT indexCount, UINT startIndexLocation, UINT baseVertexLocation)
	{
		mContext->DrawIndexed(indexCount, startIndexLocation, baseVertexLocation);
	}
	void GraphicDevice_DX11::Present()
	{
		mSwapChain->Present(0, 0);
	}
}