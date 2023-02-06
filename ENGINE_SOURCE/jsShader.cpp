#include "jsShader.h"
#include "jsGraphicDevice_DX11.h"

namespace js
{
	Shader::Shader()
		: Resource(eResourceType::GraphicShader)
		, mTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	{
	}
	Shader::~Shader()
	{
	}
	HRESULT Shader::Load(const std::wstring& strPath)
	{
		return E_NOTIMPL;
	}

	void Shader::Create(graphics::eShaderStage stage, const std::wstring& file, const std::string& funcName)
	{
		ID3DBlob* errorBlob = nullptr;

		std::filesystem::path path = std::filesystem::current_path().parent_path();
		path += L"\\SHADER_SOURCE\\";

		std::wstring shaderPath(path.c_str());
		shaderPath += file;

		if (graphics::eShaderStage::VS == stage)
		{
			D3DCompileFromFile(shaderPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
				, funcName.c_str(), "vs_5_0", 0, 0, mVSBlob.GetAddressOf(), &errorBlob);

			graphics::GetDevice()->CreateVertexShader(mVSBlob->GetBufferPointer()
				, mVSBlob->GetBufferSize(), nullptr
				, mVS.GetAddressOf());

			if (errorBlob)
			{
				OutputDebugStringA((char*)errorBlob->GetBufferPointer());
				errorBlob->Release();
				errorBlob = nullptr;
			}
		}
		else if (graphics::eShaderStage::PS == stage)
		{
			D3DCompileFromFile(shaderPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
				, funcName.c_str(), "ps_5_0", 0, 0, mPSBlob.GetAddressOf(), &errorBlob);

			graphics::GetDevice()->CreatePixelShader(mPSBlob->GetBufferPointer()
				, mPSBlob->GetBufferSize(), nullptr
				, mPS.GetAddressOf());

			if (errorBlob)
			{
				OutputDebugStringA((char*)errorBlob->GetBufferPointer());
				errorBlob->Release();
				errorBlob = nullptr;
			}
		}
	}
	void Shader::Binds()
	{
		graphics::GetDevice()->BindPrimitiveTopology(mTopology);
		graphics::GetDevice()->BindInputLayout(mInputLayout.Get());
		graphics::GetDevice()->BindVertexShader(mVS.Get(), nullptr, 0);
		graphics::GetDevice()->BindPixelShader(mPS.Get(), nullptr, 0);
	}
}