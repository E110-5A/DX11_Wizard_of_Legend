#include "jsPlayerScript.h"
#include "jsTransform.h"
#include "jsGameObject.h"
#include "jsInput.h"
#include "jsTime.h"

namespace js
{
	PlayerScript::PlayerScript()
	{
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initialize()
	{
	}
	void PlayerScript::Update()
	{
		Transform* transform = GetOwner()->GetComponent<Transform>();
		Vector3 position = transform->GetPosition();

		if (eKeyState::PRESSED == Input::GetKeyState(eKeyCode::D))
		{
			position.x += 3.0f * Time::GetDeltaTime();
		}
		else if (eKeyState::PRESSED == Input::GetKeyState(eKeyCode::A))
		{
			position.x -= 3.0f * Time::GetDeltaTime();
		}
		else if (eKeyState::PRESSED == Input::GetKeyState(eKeyCode::W))
		{
			position.y += 3.0f * Time::GetDeltaTime();
		}
		else if (eKeyState::PRESSED == Input::GetKeyState(eKeyCode::S))
		{
			position.y -= 3.0f * Time::GetDeltaTime();
		}
		transform->SetPosition(position);
	}
	void PlayerScript::FixedUpdate()
	{
	}
	void PlayerScript::Render()
	{
	}
}