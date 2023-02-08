#pragma once
#include "jsScript.h"


namespace js
{
	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		virtual ~PlayerScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	private:
	};
}