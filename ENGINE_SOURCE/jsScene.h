#pragma once
#include "jsEntity.h"
#include "jsLayer.h"
#include "jsGameObject.h"

namespace js
{
	using namespace js::enums;
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void AddGameObject(GameObject* gameObject, const eLayerType type);

	private:
		std::vector<Layer> mLayers;
	};
}