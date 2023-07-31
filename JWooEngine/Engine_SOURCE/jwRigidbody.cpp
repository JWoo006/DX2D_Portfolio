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

		// �ӵ��� ���ӵ��� �����ش�.
		mVelocity += mAccelation * Time::DeltaTime();

		if (mbGround)
		{
			// ���鿡 ������
			Vector3 gravity = mGravity;
			gravity.Normalize();

			// ����� ��Ż�濡�� �̲������Բ� ����
			float dot = mVelocity.Dot(gravity);
			mVelocity -= gravity * dot;
		}
		else 
		{
			// ���߿� �� ������
			mVelocity += mGravity * Time::DeltaTime();
		}

		// �߷°��ӵ� �ִ� �ӵ� ����
		/*Vector3 gravity = mGravity;
		gravity.Normalize();
		float dot = mVelocity.Dot(gravity);
		gravity = gravity * dot;

		Vector3 sideVelocity = mVelocity - gravity;
		if (mLimitedVelocity.y < gravity.Length())
		{
			gravity.Normalize();
			gravity *= mLimitedVelocity.y;
		}

		if (mLimitedVelocity.x < sideVelocity.Length())
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitedVelocity.x;
		}*/

		// ��ü�� �ӵ��� �°Բ� �̵�
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos = pos - mVelocity * Time::DeltaTime();
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