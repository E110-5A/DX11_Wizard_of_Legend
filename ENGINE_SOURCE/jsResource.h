#pragma once
#include "jsEntity.h"

using namespace js::enums;
namespace js
{
	class Resource : public Entity
	{
	public:
		Resource(eResourceType type);
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& strPath) = 0;

		const std::wstring& GetKey() { return mStrKey; }
		const std::wstring& GetPath() { return mStrPath; }

		void SetKey(const std::wstring& strKey) { mStrKey = strKey; }
		void SetPath(const std::wstring& strPath) { mStrPath = strPath; }


	private:
		std::wstring mStrKey;
		std::wstring mStrPath;
		eResourceType mType;
	};
}