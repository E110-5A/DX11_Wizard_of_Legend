#include "jsTransform.h"

namespace js
{
	Transform::Transform()
		: Component(eComponentType::Transform)
	{
	}
	Transform::~Transform()
	{
	}

	void Transform::Initalize()
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
	}
}