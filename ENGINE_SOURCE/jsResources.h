#pragma once
#include "jsEngine.h"
#include "jsResource.h"

namespace js
{
	class Resources
	{
	public:
		typedef std::map<std::wstring, Resource*>::iterator ResourceIter;

		template <typename T>
		static void Insert(const std::wstring& key, T* resource)
		{
			if (nullptr == resource || key == L"")
				return;

			mResources.insert(std::make_pair(key, resource));
		}


		template <typename T>
		static T* Find(const std::wstring& key)
		{
			ResourceIter iter = mResources.find(key);

			if (iter != mResources.end())
				return dynamic_cast<T*>(iter->second);

			return nullptr;
		}

		template<typename T>
		static T* Load(const std::wstring& key, const std::wstring& path)
		{
			T* resource = Resources::Find<T>(key);
			if (nullptr != resource)
				return resource;

			resource = new T;
			if (FAILED(resource->Load(path)))
			{
				MessageBox(nullptr, L"Image Load Failed!!", L"Error", MB_OK);
				return nullptr;
			}

			resource->SetKey(key);
			resource->SetPath(path);

			mResources.insert(std::make_pair(key, dynamic_cast<Resource*>(resource)));
			return dynamic_cast<T*>(resource);
		}

		static void Release()
		{
			ResourceIter iter = mResources.begin();
			for (; iter != mResources.end(); ++iter)
			{
				if (nullptr == iter->second)
					continue;

				delete (iter->second);
				iter->second = nullptr;
			}
		}

	private:
		static std::map<std::wstring, Resource*> mResources;
	};
}