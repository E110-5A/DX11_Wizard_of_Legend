#include "jsSceneManager.h"

namespace js
{
	Scene* SceneManager::mPlayScene = nullptr;

	void SceneManager::Initalize()
	{

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