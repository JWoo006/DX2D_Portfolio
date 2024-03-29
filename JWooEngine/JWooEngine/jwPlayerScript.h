#pragma once
//#include "jwScript.h"
#include <jwScript.h>

namespace jw
{
	class Transform;
	class Collider2D;
	class Animator;
	class Rigidbody;
	class PlayerScript : public Script
	{
	public:
		enum class ePlayerState
		{
			Idle,
			Move_L,
			Move_R,
			Crouch,
			Roll,
			Jump_L,
			Jump_R,
			Attack,
			Death,
		};
		PlayerScript();
		~PlayerScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;

		void Complete();
		void IdletoRunAnimComplete();
		void RuntoIdleAnimComplete();
		void PreCrouchAnimComplete();
		void PostCrouchAnimComplete();
		void RollAnimComplete();
		void AttackAnimComplete();

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void idle();
		void move();
		void crouch();
		void roll();
		void jump();
		void attack();
		void death();

		void CreateAttackSlash();

	private:
		ePlayerState mState;

		Transform* mTransform;
		Collider2D* mCollider;
		Animator* mAnimator;
		Rigidbody* mRigidbody;

		float mJumpScale;
		float mJumpTime;
		float mAtackJumpScale;
		bool mbFall = false;

		float mAttackDelay;
		float mAttackTime;
		bool mbFirstAttack;
		Vector3 mAttackDirection;

		float mGroundAngle;
		bool OnSlope;
		bool OnGround;

		bool mbOnJump;
		bool mbSlopeJumpInputKeyCheck;
	};
}