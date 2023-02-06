#include "jsLayer.h"

namespace js
{
	Layer::Layer()
	{
	}
	Layer::~Layer()
	{
	}
	void Layer::Initalize()
	{
		for (GameObject* object : mGameObjects)
		{
			if (object == nullptr)
				continue;

			object->Initalize();
		}
	}
	void Layer::Update()
	{
		for (GameObject* object : mGameObjects)
		{
			if (object == nullptr)
				continue;

			object->Update();
		}
	}
	void Layer::FixedUpdate()
	{
		for (GameObject* object : mGameObjects)
		{
			if (object == nullptr)
				continue;

			object->FixedUpdate();
		}
	}
	void Layer::Render()
	{
		for (GameObject* object : mGameObjects)
		{
			if (object == nullptr)
				continue;

			object->Render();
		}
	}
	void Layer::AddGameObject(GameObject* gameObject)
	{
		if (nullptr == gameObject)
			return;

		mGameObjects.push_back(gameObject);
	}
}