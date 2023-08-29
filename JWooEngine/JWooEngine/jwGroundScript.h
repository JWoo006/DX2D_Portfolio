#pragma once
#include "..\\Engine_SOURCE\\jwScript.h"
#include "..\\Engine_SOURCE\\jwCollider2D.h"

namespace jw
{
	class GroundScript : public Script
	{
	public:
		GroundScript();
		~GroundScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void SetOnOffCollider(bool _onoff) { mbOnOff = _onoff; }

	private:
		bool mbOnOff;
	};
}

