#pragma once
#include "jwComponent.h"

namespace jw
{
	using namespace jw::enums;
	using namespace jw::math;

	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetGround(bool ground) { mbGround = ground; }
		void SetMass(float mass) { mMass = mass; }
		bool GetGround() { return mbGround; }
		void SetGravity(Vector3 gravity) { mGravity = gravity; }

		Vector3 GetVelocity() { return mVelocity; }
		void SetVelocity(Vector3 vel) { mVelocity = vel; }
		void SetVelocityX(float _Value) { mVelocity.x = _Value; }
		void SetVelocityY(float _Value) { mVelocity.y = _Value; }
		void AddVelocity(Vector3 vel) { mVelocity += vel; }
		void AddForce(Vector3 force);

		void SetLimitVelocity(Vector3 vel) { mLimitedVelocity = vel; }

	private:
		float mMass;
		Vector3 mForce;
		Vector3 mAccelation;
		Vector3 mVelocity;
		Vector3 mLimitedVelocity;

		Vector3 mGravity;
		float mFriction;
		bool mbGround;
		bool mbAttack;
		Rigidbody* mRigidbody;
	};

}
