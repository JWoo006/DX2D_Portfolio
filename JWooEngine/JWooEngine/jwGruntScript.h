#pragma once
//#include "jwScript.h"
#include <jwScript.h>

namespace jw
{
	class GruntScript : public Script
	{
	public:
		enum class eGruntState
		{
			Idle,
			Move_L,
			Move_R,
			Attack,
			Death,
		};
		GruntScript();
		~GruntScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void dead();

	private:
		class Animator* mAnimator;
		class Collider2D* mCollider;
		class Rigidbody* mRigidbody;

		eGruntState mState;
		bool mbDead;
	};
}


