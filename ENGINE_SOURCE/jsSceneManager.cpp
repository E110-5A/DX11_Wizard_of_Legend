#include "jsSceneManager.h"
#include "jsTransform.h"

namespace js
{
	Scene* SceneManager::mPlayScene = nullptr;

	void SceneManager::Initalize()
	{
		mPlayScene = new Scene();
		mPlayScene->Initalize();

		GameObject* object = new GameObject();
		Transform* transform = new Transform();
		transform->SetPosition(Vector3(0.2f, 0.2f, 0.f));
		object->AddComponent(transform);

		mPlayScene->AddGameObject(object, eLayerType::Player);

	}
	void SceneManager::Update()
	{
		mPlayScene->Update();
	}
	void SceneManager::FixedUpdate()
	{
		mPlayScene->FixedUpdate();
	}
	void SceneManager::Render()
	{
		mPlayScene->Render();
	}

}