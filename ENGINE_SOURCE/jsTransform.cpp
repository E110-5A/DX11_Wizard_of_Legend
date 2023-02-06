#include "jsTransform.h"
#include "jsRenderer.h"

namespace js
{
	Transform::Transform()
		: Component(eComponentType::Transform)
	{
	}
	Transform::~Transform()
	{
	}

	void Transform::Initialize()
	{
	}
	void Transform::Update()
	{
	}
	void Transform::FixedUpdate()
	{
		SetConstantBuffer();
	}
	void Transform::Render()
	{
	}
	void Transform::SetConstantBuffer()
	{
		ConstantBuffer* constantBuffer = renderer::constantBuffers[(UINT)eCBType::Transform];
		Vector4 pos(mPosition.x, mPosition.y, mPosition.z, 0.f);
		constantBuffer->Bind(&pos);
		constantBuffer->SetPipline(eShaderStage::VS);
	}
}