#pragma once
//#include "jwScript.h"
#include <jwScript.h>

namespace jw
{
	class PlayerScript : public Script
	{
	public:
		virtual void Update() override;

		//virtual void OnCollisionEnter(Collider2D* other) override;
		//virtual void OnCollisionStay(Collider2D* other) override;
		//virtual void OnCollisionExit(Collider2D* other) override;

	private:

	};
}