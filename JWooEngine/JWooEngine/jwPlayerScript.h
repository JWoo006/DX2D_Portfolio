#pragma once
//#include "jwScript.h"
#include <jwScript.h>

namespace jw
{
	class Transform;
	class Collider2D;
	class Animator;
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

		//virtual void OnCollisionEnter(Collider2D* other) override;
		//virtual void OnCollisionStay(Collider2D* other) override;
		//virtual void OnCollisionExit(Collider2D* other) override;

		void idle();
		void move();
		void crouch();
		void roll();
		void jump();
		void attack();
		void death();

	private:
		ePlayerState mState;

		Transform* tr;
		Collider2D* cd;
		Animator* at;

		Vector3 pos;

		float mJumpTime;
		bool mbFall = false;
		
	};
}