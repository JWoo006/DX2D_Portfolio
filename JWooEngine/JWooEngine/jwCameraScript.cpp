#include "jwCameraScript.h"
#include "jwTransform.h"
#include "jwGameObject.h"
#include "jwTime.h"
#include "jwInput.h"

namespace jw
{
	CameraScript::CameraScript()
		: mPlayer(nullptr)
		, mbCameraFollowX(false)
		, mbCameraFollowY(false)
	{
	}
	CameraScript::~CameraScript()
	{
	}
	void CameraScript::Initialize()
	{
	}
	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::UP))
		{
			pos.y += 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::DOWN))
		{
			pos.y -= 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		/*else if (Input::GetKey(eKeyCode::Q))
		{
			pos.z -= 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::E))
		{
			pos.z += 5.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}*/

		if (mPlayer)
		{
			//tr->SetPosition(mPlayer->GetPos());
		}

	}
	void CameraScript::KeyBoardMove()
	{
	}
	void CameraScript::TargetMove()
	{
	}
	void CameraScript::OnCollisionEnter(Collider2D* other)
	{
	}
	void CameraScript::OnCollisionStay(Collider2D* other)
	{
	}
	void CameraScript::OnCollisionExit(Collider2D* other)
	{
	}
}
