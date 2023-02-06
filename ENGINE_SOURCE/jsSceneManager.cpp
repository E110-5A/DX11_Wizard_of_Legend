#include "jsSceneManager.h"
#include "jsTransform.h"
#include "jsMeshRenderer.h"
#include "jsRenderer.h"

namespace js
{
	Scene* SceneManager::mPlayScene = nullptr;

	void SceneManager::Initialize()
	{
		mPlayScene = new Scene();
		mPlayScene->Initialize();

		GameObject* object = new GameObject();
		Transform* transform = new Transform();
		transform->SetPosition(Vector3(0.2f, 0.2f, 0.f));
		object->AddComponent(transform);

		MeshRenderer* meshRenderer = new MeshRenderer();
		meshRenderer->SetMesh(renderer::mesh);
		meshRenderer->SetShader(renderer::shader);
		object->AddComponent(meshRenderer);

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