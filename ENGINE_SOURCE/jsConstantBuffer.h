#pragma once
#include "jsGraphics.h"

namespace js::graphics
{
	class ConstantBuffer : public GPUBuffer
	{
	public:
		ConstantBuffer();
		virtual ~ConstantBuffer();

		bool Create(SIZE_T size);
		void Bind(void* data);
		void SetPipline(eShaderStage stage);

	private:
		const eCBType mType;
	};
}