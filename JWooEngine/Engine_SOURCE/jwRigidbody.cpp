#include "jwRigidbody.h"
#include "jwTime.h"
#include "jwGameObject.h"
#include "jwTransform.h"


namespace jw
{
	Rigidbody::Rigidbody()
		:Component(eComponentType::Rigidbody)
		, mMass(0.0f)
		, mForce(Vector3::Zero)
		, mAccelation(Vector3::Zero)
		, mVelocity(Vector3::Zero)
	{
		mLimitedVelocity.x = 200.0f;
		mLimitedVelocity.y = 1000.0f;
		mbGround = false;
		mGravity = Vector3(0.0f, 15.0f, 0.0f);
		mFriction = 100.0f;
	}
	Rigidbody::~Rigidbody()
	{
	}
	void Rigidbody::Initialize()
	{
	}
	void Rigidbody::Update()
	{
		// F = M * A
		// A = M / F
		mAccelation = mForce / mMass;

		// 속도에 가속도를 더해준다.
		mVelocity += mAccelation * Time::DeltaTime();

		if (mbGround)
		{
			// 지면에 있을시
			Vector3 gravity = mGravity;
			gravity.Normalize();

			// 경사진 빗탈길에서 미끄러지게끔 구현
			float dot = mVelocity.Dot(gravity);
			mVelocity -= gravity * dot;
		}
		else 
		{
			// 공중에 떠 있을시
			mVelocity += mGravity * Time::DeltaTime();
		}

		{
			Vector3 Dir = mVelocity;
			Dir.Normalize();
		}

		// 중력가속도 최대 속도 제한
		/*vector3 gravity = mgravity;
		gravity.normalize();
		float dot = mvelocity.dot(gravity);
		gravity = gravity * dot;

		vector3 sidevelocity = mvelocity - gravity;
		if (mlimitedvelocity.y < gravity.length())
		{
			gravity.normalize();
			gravity *= mlimitedvelocity.y;
		}

		if (mlimitedvelocity.x < sidevelocity.length())
		{
			sidevelocity.normalize();
			sidevelocity *= mlimitedvelocity.x;
		}*/

		// 물체를 속도에 맞게끔 이동
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos = pos - mVelocity * 1.f * Time::DeltaTime();
		tr->SetPosition(pos);

		mForce = Vector3::Zero;
	}
	void Rigidbody::LateUpdate()
	{
	}
	void Rigidbody::Render()
	{
	}

	void Rigidbody::AddForce(Vector3 force)
	{
		mForce += force;
	}

}