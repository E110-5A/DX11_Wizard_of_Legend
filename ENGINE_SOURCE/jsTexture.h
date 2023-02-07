#pragma once
#include "jsResource.h"
#include "../External/DirectXTex/include/DirectXTex.h"
#include "jsGraphicDevice_DX11.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\External\\DirectXTex\\lib\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\External\\DirectXTex\\lib\\Release\\DirectXTex.lib")
#endif

using namespace js::enums;
namespace js::graphics
{
	class Texture : public Resource
	{
	public:
		Texture();
		virtual ~Texture();

		virtual HRESULT Load(const std::wstring& strPath) override;

		void BindShader(eShaderStage stage, UINT slot);

	private:
		ScratchImage mImage;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mShaderResourceView;
		D3D11_TEXTURE2D_DESC mDesc;
	};
}