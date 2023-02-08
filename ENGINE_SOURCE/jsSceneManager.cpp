#include "jsSceneManager.h"
#include "jsRenderer.h"
#include "jsResources.h"

// component
#include "jsTransform.h"
#include "jsMeshRenderer.h"

// resource
#include "jsTexture.h"
#include "jsPlayerScript.h"

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

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> material = Resources::Find<Material>(L"RectMaterial");
		meshRenderer->SetMesh(mesh.get());
		meshRenderer->SetMaterial(material.get());

		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"SmileTexture", L"Smile.png");
		texture->BindShader(eShaderStage::PS, 0);
		
		PlayerScript* script = new PlayerScript();
		object->AddComponent(script);


		mPlayScene->AddGameObject(object, eLayerType::Player);


		Vector2 vec2(1.0f, 1.0f);
		material->SetData(eGPUParam::Vector2, &vec2);

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