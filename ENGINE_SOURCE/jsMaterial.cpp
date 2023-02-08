#include "jsMaterial.h"

namespace js::graphics
{
	Material::Material()
		: Resource(eResourceType::Material)
	{
	}
	Material::~Material()
	{
	}
	HRESULT Material::Load(const std::wstring& strPath)
	{
		return E_NOTIMPL;
	}

	void Material::SetData(eGPUParam param, void* data)
	{
		switch (param)
		{
		case eGPUParam::Int:
			mConstantBuffer.iData = *static_cast<int*>(data);
			break;
		case eGPUParam::Float:
			mConstantBuffer.fData = *static_cast<float*>(data);
			break;
		case eGPUParam::Vector2:
			mConstantBuffer.xy = *static_cast<Vector2*>(data);
			break;
		case eGPUParam::Vector3:
			mConstantBuffer.xyz = *static_cast<Vector3*>(data);
			break;
		case eGPUParam::Vector4:
			mConstantBuffer.xyzw = *static_cast<Vector4*>(data);
			break;
		case eGPUParam::Matrix:
			mConstantBuffer.matrix = *static_cast<Matrix*>(data);
			break;
		default:
			break;
		}
	}

	void Material::Bind()
	{
		ConstantBuffer* pConstantBuffer = renderer::constantBuffers[(UINT)eCBType::Material];
		pConstantBuffer->Bind(&mConstantBuffer);
		pConstantBuffer->SetPipline(eShaderStage::VS);
		pConstantBuffer->SetPipline(eShaderStage::PS);

		mShader->Binds();
	}
}