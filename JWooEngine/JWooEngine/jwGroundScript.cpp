#include "jwGroundScript.h"
#include "jwGameObject.h"
#include "jwRigidbody.h"
#include "jwTransform.h"
#include "jwPlayer.h"

namespace jw
{
	GroundScript::GroundScript()
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
		Rigidbody* rb = other->GetOwner()->GetComponent<Rigidbody>();
		rb->SetGround(true);

		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player == nullptr)
			return;

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

			Vector3 playerPos = playerTr->GetPosition();
			Vector3 grPos = grTr->GetPosition();

			playerPos.y -= (fSize - fLen) - 1.0f;
			playerTr->SetPosition(playerPos);
		}
	}
	void GroundScript::OnCollisionStay(Collider2D* other)
	{
	}
	void GroundScript::OnCollisionExit(Collider2D* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player == nullptr)
			return;

		Rigidbody* rb = other->GetOwner()->GetComponent<Rigidbody>();
		rb->SetGround(false);
	}
}
