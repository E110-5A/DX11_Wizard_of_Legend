#include "jsGameObject.h"

namespace js
{
	GameObject::GameObject()
		: mState(eState::Active)
	{
		mComponents.resize((UINT)eComponentType::End);
		mScripts.resize((UINT)eComponentType::End);
	}
	GameObject::~GameObject()
	{
	}
	void GameObject::Initialize()
	{
		for (Component* component : mComponents)
		{
			if (component == nullptr)
				continue;

			component->Initialize();
		}
		for (Component* scripts : mScripts)
		{
			if (scripts == nullptr)
				continue;

			scripts->Initialize();
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
		for (Component* scripts : mScripts)
		{
			if (scripts == nullptr)
				continue;

			scripts->Update();
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
		for (Component* scripts : mScripts)
		{
			if (scripts == nullptr)
				continue;

			scripts->FixedUpdate();
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
		for (Component* scripts : mScripts)
		{
			if (scripts == nullptr)
				continue;

			scripts->Render();
		}
	}
	void GameObject::AddComponent(Component* component)
	{
		eComponentType order = component->GetOrder();
		if (eComponentType::Script != order)
		{
			mComponents[(UINT)order] = component;
			mComponents[(UINT)order]->SetOwner(this);
		}
		else
		{
			mScripts.push_back(component);
			component->SetOwner(this);
		}
	}
}