#pragma once
#include "jsEntity.h"
#include "jsMath.h"

namespace js
{
	using namespace js::enums;
	using namespace js::math;
	class GameObject;
	class Component : public Entity
	{
	public:
		Component(eComponentType type);
		virtual ~Component();

		virtual void Initalize() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() = 0;

		UINT GetOrder() { return (UINT)mType; }

		GameObject* GetOwner() { return mOwner; }
		void SetOwner(GameObject* object) { mOwner = object; }

	private:
		const eComponentType mType;
		GameObject*					mOwner;
	};
}