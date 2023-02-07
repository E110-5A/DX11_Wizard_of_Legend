#pragma once
#include "jsResource.h"
#include "jsGraphics.h"

namespace js
{
	class Shader : public Resource
	{
	public:
		Shader();
		~Shader();

		virtual HRESULT Load(const std::wstring& strPath) override;

		void Create(graphics::eShaderStage stage, const std::wstring& file, const std::string& funcName);
		void Binds();

		ID3D11InputLayout* GetInputLayout() { return mInputLayout.Get(); }
		ID3D11InputLayout** GetInputLyaoutAddressOf() { return mInputLayout.GetAddressOf(); }

		void* GetVertexBlobBufferPointer() { return mVSBlob->GetBufferPointer(); }
		SIZE_T GetVertexBlobBufferSize() { return mVSBlob->GetBufferSize(); }

	private:
		Microsoft::WRL::ComPtr<ID3D11InputLayout>		mInputLayout;
		D3D11_PRIMITIVE_TOPOLOGY						mTopology;
		graphics::eShaderStage							mStage;

		Microsoft::WRL::ComPtr<ID3DBlob>				mVSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob>				mHSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob>				mDSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob>				mGSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob>				mPSBlob;

		Microsoft::WRL::ComPtr<ID3D11VertexShader>		mVS;
		Microsoft::WRL::ComPtr<ID3D11HullShader>		mHS;
		Microsoft::WRL::ComPtr<ID3D11DomainShader>		mDS;
		Microsoft::WRL::ComPtr<ID3D11GeometryShader>	mGS;
		Microsoft::WRL::ComPtr<ID3D11PixelShader>		mPS;
		
		Microsoft::WRL::ComPtr<ID3DBlob>				mErrorBlob;

	};
}