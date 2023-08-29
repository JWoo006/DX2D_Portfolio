#include "jwGroundScript.h"
#include "jwGameObject.h"
#include "jwRigidbody.h"
#include "jwTransform.h"
#include "jwPlayer.h"

namespace jw
{
	GroundScript::GroundScript()
		: mbOnOff(true)
	{
	}
	GroundScript::~GroundScript()
	{
	}
	void GroundScript::Initialize()
	{
	}
	void GroundScript::Update()
	{
	}
	void GroundScript::LateUpdate()
	{
	}
	void GroundScript::Render()
	{
	}
	void GroundScript::OnCollisionEnter(Collider2D* other)
	{

		if (mbOnOff)
		{
			//Rigidbody* rb = other->GetOwner()->GetComponent<Rigidbody>();
					//rb->SetVelocityY(0.0f);
					//rb->SetGround(true);
			Rigidbody* rb = other->GetOwner()->GetComponent<Rigidbody>();
			rb->SetGround(true);

			Collider2D* playerCol = other->GetOwner()->GetComponent<Collider2D>();
			Vector3 playerPos = other->GetOwner()->GetComponent<Transform>()->GetPosition();

			Collider2D* groundCol = this->GetOwner()->GetComponent<Collider2D>();
			Vector3 groundPos = groundCol->GetPosition();

			float fLen = fabs(playerPos.y - groundPos.y);
			float fSize = (playerCol->GetSize().y / 2.0f) + (groundCol->GetSize().y / 2.0f);

			if (fLen < fSize)
			{
				Transform* playerTr = other->GetOwner()->GetComponent<Transform>();
				Vector3 a = playerTr->GetRotation();
				Transform* grTr = this->GetOwner()->GetComponent<Transform>();

				Vector3 playerPos2 = playerTr->GetPosition();
				Vector3 grPos = grTr->GetPosition();

				playerPos2.y += (fSize - fLen);
				playerTr->SetPosition(playerPos2);
			}
		}
		
	}
	void GroundScript::OnCollisionStay(Collider2D* other)
	{

		if (mbOnOff)
		{
			Collider2D* playerCol = other->GetOwner()->GetComponent<Collider2D>();
			Vector3 playerPos = other->GetOwner()->GetComponent<Transform>()->GetPosition();

			Collider2D* groundCol = this->GetOwner()->GetComponent<Collider2D>();
			Vector3 groundPos = groundCol->GetPosition();

			float fLen = fabs(playerPos.y - groundPos.y);
			float fSize = (playerCol->GetSize().y / 2.0f) + (groundCol->GetSize().y / 2.0f);

			if (fLen < fSize)
			{
				Transform* playerTr = other->GetOwner()->GetComponent<Transform>();
				Transform* grTr = this->GetOwner()->GetComponent<Transform>();

				Vector3 playerPos2 = playerTr->GetPosition();
				Vector3 grPos = grTr->GetPosition();

				playerPos2.y += (fSize - fLen);
				playerTr->SetPosition(playerPos2);
			}
		}

		
	}
	void GroundScript::OnCollisionExit(Collider2D* other)

	{
		Rigidbody* rb = other->GetOwner()->GetComponent<Rigidbody>();
		//rb->SetGround(false);
	}
}
