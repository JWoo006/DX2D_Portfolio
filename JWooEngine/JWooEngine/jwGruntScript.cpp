#include "jwGruntScript.h"
#include "jwGameObject.h"
#include "jwAnimator.h"
#include "jwCollider2D.h"
#include "jwRigidbody.h"
#include "jwGroundScript.h"

namespace jw
{
	GruntScript::GruntScript()
		: mState(eGruntState::Idle)
		, mbDead(false)
	{
	}
	GruntScript::~GruntScript()
	{
	}
	void GruntScript::Initialize()
	{
		mAnimator = GetOwner()->GetComponent<Animator>();
		mCollider = GetOwner()->GetComponent<Collider2D>();
		mRigidbody = GetOwner()->GetComponent<Rigidbody>();

		mAnimator->CreateAnimations(L"Grunt_Idle", L"..\\Resources\\Texture\\Enemy\\Grunt\\spr_grunt_idle", 80, 0.1f);
		mAnimator->CreateAnimations(L"Grunt_Run", L"..\\Resources\\Texture\\Enemy\\Grunt\\spr_grunt_run", 80, 0.1f);
		mAnimator->CreateAnimations(L"Grunt_Attack", L"..\\Resources\\Texture\\Enemy\\Grunt\\spr_grunt_attack", 80, 0.1f);
		mAnimator->CreateAnimations(L"Grunt_Dead", L"..\\Resources\\Texture\\Enemy\\Grunt\\spr_grunt_hurtground", 80, 0.1f);
		mAnimator->PlayAnimation(L"Grunt_Idle", true);
		//mAnimator->PlayAnimation(L"Grunt_Attack", false);

		mCollider->SetSize(Vector2(0.3f, 0.4f));
	}
	void GruntScript::Update()
	{
		switch (mState)
		{
		case jw::GruntScript::eGruntState::Idle:
			break;
		case jw::GruntScript::eGruntState::Move_L:
			break;
		case jw::GruntScript::eGruntState::Move_R:
			break;
		case jw::GruntScript::eGruntState::Attack:
			break;
		case jw::GruntScript::eGruntState::Death:
			dead();
			break;
		default:
			break;
		}
	}
	void GruntScript::LateUpdate()
	{
	}
	void GruntScript::OnCollisionEnter(Collider2D* other)
	{
		std::wstring name = other->GetOwner()->GetName();
		Rigidbody* rb = this->GetOwner()->GetComponent<Rigidbody>();

		if (name == L"PlayerAttackSlash")
		{
			if (!mbDead)
			{
				mState = eGruntState::Death;
				mbDead = true;
				mAnimator->PlayAnimation(L"Grunt_Dead", false);

				if (other->GetOwner()->GetComponent<Animator>()->GetAnimDirection() == Animation::eAnimDirection::Left)
				{
					//mAnimator->SetAnimDirection(Animation::eAnimDirection::Right);

					rb->SetGround(false);
					Vector3 velocity = rb->GetVelocity();
					velocity.y = -2.0f;
					velocity.x = 2.0f;
					rb->SetVelocity(velocity);
				}
				else
				{
					rb->SetGround(false);
					Vector3 velocity = rb->GetVelocity();
					velocity.y = -2.0f;
					velocity.x = -2.0f;
					rb->SetVelocity(velocity);
				}
			}
		}

		if (name == L"GroundCol_Base")
		{
			rb->SetGround(true);
		}
		if (name == L"GroundCol_Slope")
		{
			rb->SetGround(true);
		}
		if (name == L"GroundCol_Down")
		{
			other->GetOwner()->GetScript<GroundScript>()->SetOnOffCollider(false);

			Collider2D* playerCol = this->GetOwner()->GetComponent<Collider2D>();
			Vector3 playerPos = this->GetOwner()->GetComponent<Transform>()->GetPosition();
			Collider2D* groundCol = other->GetOwner()->GetComponent<Collider2D>();
			Vector3 groundPos = groundCol->GetPosition();
			if (playerPos.y >= groundPos.y)
			{
				other->GetOwner()->GetScript<GroundScript>()->SetOnOffCollider(true);
				rb->SetGround(true);
			}

		}
	}
	void GruntScript::OnCollisionStay(Collider2D* other)
	{
		
	}
	void GruntScript::OnCollisionExit(Collider2D* other)
	{
	}
	void GruntScript::dead()
	{
		Rigidbody* rb = this->GetOwner()->GetComponent<Rigidbody>();

		if (rb->GetGround())
		{
			rb->SetVelocity(Vector3::Zero);
		}
		
	}
}

