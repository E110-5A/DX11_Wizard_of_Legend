#pragma once
#include "jsEngine.h"

namespace js
{
	class Entity
	{
	public:
		Entity();
		Entity(const Entity& other);
		virtual ~Entity();

		UINT32 GetID() { return mID; }

		void SetName(const std::wstring name) { mName = name; }
		const std::wstring GetName() { return mName; }


	private:
		const UINT32	mID;
		std::wstring	mName;
	};

}
