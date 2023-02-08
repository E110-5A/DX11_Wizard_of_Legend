#include "jsSceneManager.h"
#include "jsRenderer.h"
#include "jsResources.h"

#include "jsTransform.h"
#include "jsMeshRenderer.h"
#include "jsTexture.h"

namespace js
{
	Scene* SceneManager::mPlayScene = nullptr;

	void SceneManager::Initialize()
	{
		mPlayScene = new Scene();
		mPlayScene->Initialize();

		GameObject* object = new GameObject();
		Transform* transform = new Transform();
		transform->SetPosition(Vector3(0.0f, 0.0f, 0.f));
		object->AddComponent(transform);

		MeshRenderer* meshRenderer = new MeshRenderer();
		object->AddComponent(meshRenderer);


		Mesh* mesh = Resources::Find<Mesh>(L"RectMesh");
		Material* material = Resources::Find<Material>(L"RectMaterial");
		meshRenderer->SetMesh(mesh);
		meshRenderer->SetMaterial(material);

		Texture* texture = Resources::Load<Texture>(L"SmileTexture", L"Smile.png");
		texture->BindShader(eShaderStage::PS, 0);

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