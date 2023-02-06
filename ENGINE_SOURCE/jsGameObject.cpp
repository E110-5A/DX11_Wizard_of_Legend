#include "jsGameObject.h"

namespace js
{
	GameObject::GameObject()
		: mState(eState::Active)
	{
		mComponents.resize((UINT)eComponentType::End);
	}
	GameObject::~GameObject()
	{
	}
	void GameObject::Initalize()
	{
		for (Component* component : mComponents)
		{
			if (component == nullptr)
				continue;

			component->Initalize();
		}
	}
	void GameObject::Update()
	{
		for (Component* component : mComponents)
		{
			if (component == nullptr)
				continue;

			component->Update();
		}
	}
	void GameObject::FixedUpdate()
	{
		for (Component* component : mComponents)
		{
			if (component == nullptr)
				continue;

			component->FixedUpdate();
		}
	}
	void GameObject::Render()
	{
		for (Component* component : mComponents)
		{
			if (component == nullptr)
				continue;

			component->Render();
		}
	}
	void GameObject::AddComponent(Component* component)
	{
		int order = component->GetOrder();
		mComponents[order] = component;
		mComponents[order]->SetOwner(this);
	}
}