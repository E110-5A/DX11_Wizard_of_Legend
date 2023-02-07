#include "jsTexture.h"

namespace js::graphics
{
	Texture::Texture()
		: Resource(eResourceType::Texture)
		, mDesc{}
	{
	}
	Texture::~Texture()
	{
	}

	HRESULT Texture::Load(const std::wstring& strPath)
	{
		wchar_t szExtension[256] = {};
		_wsplitpath_s(strPath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExtension, 256);
		std::wstring extension(szExtension);

		if (L".dds" == extension || L".DDS" == extension)
		{
			if (FAILED(LoadFromDDSFile(strPath.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, mImage)))
				return S_FALSE;
		}
		else if (L".tga" == extension || L".TGA" == extension)
		{
			if (FAILED(LoadFromTGAFile(strPath.c_str(), nullptr, mImage)))
				return S_FALSE;
		}
		else  // WIC (png, jpg, jpeg, bmp)
		{
			if (FAILED(LoadFromWICFile(strPath.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, mImage)))
				return S_FALSE;
		}

		CreateShaderResourceView(GetDevice()->GetID3D11Device()
			, mImage.GetImages()
			, mImage.GetImageCount()
			, mImage.GetMetadata()
			, mShaderResourceView.GetAddressOf());

		mShaderResourceView->GetResource((ID3D11Resource**)mTexture.GetAddressOf());

		return S_OK;
	}
	void Texture::BindShader(eShaderStage stage, UINT slot)
	{
		GetDevice()->SetShaderResource(stage, slot, mShaderResourceView.GetAddressOf());
	}
}