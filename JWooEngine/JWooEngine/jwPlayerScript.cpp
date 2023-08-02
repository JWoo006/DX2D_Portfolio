#include "jwPlayerScript.h"
#include "jwCameraScript.h"
#include "jwTransform.h"
#include "jwGameObject.h"
#include "jwTime.h"
#include "jwInput.h"
#include "jwAnimator.h"
#include "jwCollider2D.h"
#include "jwRigidbody.h"

#include "jwCamera.h"

#include "jwGroundScript.h"

#include "jwMyMath.h"

namespace jw
{
	PlayerScript::PlayerScript()
		: mJumpScale(5.0f)
	{
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initialize()
	{
		tr = GetOwner()->GetComponent<Transform>();
		cd = GetOwner()->GetComponent<Collider2D>();
		at = GetOwner()->GetComponent<Animator>();

		rb = GetOwner()->GetComponent<Rigidbody>();


		pos = tr->GetPosition();

		at->CreateAnimations(L"Player_Idle", L"..\\Resources\\Texture\\Player\\spr_idle", 80, 0.1f);
		//at->CreateAnimation(L"Player_Idle", L"..\\Resources\\Texture\\Player\\spr_idle", Vector2(0.0), Vector2(36.1f, 100.0f)); // ÇÈ¼¿ 36X35

		at->CreateAnimations(L"Player_Idle_to_Run", L"..\\Resources\\Texture\\Player\\spr_idle_to_run", 80, 0.05f);
		at->CreateAnimations(L"Player_Run", L"..\\Resources\\Texture\\Player\\spr_run", 80, 0.1f);
		at->CreateAnimations(L"Player_Run_to_Idle", L"..\\Resources\\Texture\\Player\\spr_run_to_idle", 80, 0.05f);
		//at->CreateAnimation(L"Player_Idle_to_Run", L"..\\Resources\\Texture\\Player\\spr_idle_to_run", Vector2(0.0), Vector2(44.f, 80.0f), 0.05f); // pixel 44x32
		//at->CreateAnimation(L"Player_Run", L"..\\Resources\\Texture\\Player\\spr_run", Vector2(0.0), Vector2(44.f, 80.0f)); // ÇÈ¼¿ 44X32
		//at->CreateAnimation(L"Player_Run_to_Idle", L"..\\Resources\\Texture\\Player\\spr_run_to_idle", Vector2(0, 13.f), Vector2(52.f, 80.0f), 0.05f); // pixel 52x36

		at->CreateAnimations(L"Player_PreCrouch", L"..\\Resources\\Texture\\Player\\spr_precrouch", 80, 0.05f);
		at->CreateAnimations(L"Player_Crouch", L"..\\Resources\\Texture\\Player\\spr_crouch", 80, 0.1f);
		at->CreateAnimations(L"Player_PostCrouch", L"..\\Resources\\Texture\\Player\\spr_postcrouch", 80, 0.1f);
		//at->CreateAnimation(L"Player_PreCrouch", L"..\\Resources\\Texture\\Player\\spr_precrouch", Vector2(0, 10.f), Vector2(36.f, 100.0f), 0.05f); // pixel 36x40
		//at->CreateAnimation(L"Player_Crouch", L"..\\Resources\\Texture\\Player\\spr_crouch", Vector2(0, 10.f), Vector2(36.f, 100.0f)); // ÇÈ¼¿ 36x40
		//at->CreateAnimation(L"Player_PostCrouch", L"..\\Resources\\Texture\\Player\\spr_postcrouch", Vector2(0, 10.f), Vector2(36.f, 100.0f), 0.05f); // pixel 36x40

		at->CreateAnimations(L"Player_Roll", L"..\\Resources\\Texture\\Player\\spr_roll", 80, 0.05f);
		//at->CreateAnimation(L"Player_Roll", L"..\\Resources\\Texture\\Player\\spr_roll", Vector2(0, -5.f), Vector2(48.f, 100.0f), 0.05f); // pixel 48x33

		at->CreateAnimations(L"Player_Attack", L"..\\Resources\\Texture\\Player\\spr_attack", 80, 0.05f);
		//at->CreateAnimation(L"Player_Attack", L"..\\Resources\\Texture\\Player\\spr_attack", Vector2(0.0), Vector2(62.f, 117.0f), 0.05f); // ÇÈ¼¿ 62X42


		at->CreateAnimations(L"Player_Jump", L"..\\Resources\\Texture\\Player\\spr_jump", 80, 0.05f);
		at->CreateAnimations(L"Player_Fall", L"..\\Resources\\Texture\\Player\\spr_fall", 80, 0.05f);
		//at->CreateAnimation(L"Player_Jump", L"..\\Resources\\Texture\\Player\\spr_jump", Vector2(0, 10.f), Vector2(32.f, 100.0f), 0.05f); // ÇÈ¼¿ 32X42
		//at->CreateAnimation(L"Player_Fall", L"..\\Resources\\Texture\\Player\\spr_fall", Vector2(0, 20.f), Vector2(42.f, 100.0f), 0.05f); // ÇÈ¼¿ 42x48

		at->CreateAnimations(L"Player_WallGrab", L"..\\Resources\\Texture\\Player\\spr_wallgrab", 80, 0.1f);
		//at->CreateAnimation(L"Player_WallGrab", L"..\\Resources\\Texture\\Player\\spr_wallgrab", Vector2(0, 10), Vector2(48.f, 100.0f)); // ÇÈ¼¿ 48x38

		at->CreateAnimations(L"Player_Hurtfly_Begin", L"..\\Resources\\Texture\\Player\\spr_hurtfly_begin", 80, 0.1f);
		at->CreateAnimations(L"Player_Hurtfly_Loop", L"..\\Resources\\Texture\\Player\\spr_hurtfly_loop", 80, 0.1f);
		at->CreateAnimations(L"Player_Death", L"..\\Resources\\Texture\\Player\\spr_hurtground", 80, 0.1f);
		//at->CreateAnimation(L"Player_Hurtfly_Begin", L"..\\Resources\\Texture\\Player\\spr_hurtfly_begin", Vector2(0, 20.f), Vector2(50.f, 80.0f)); // pixel 50x43
		//at->CreateAnimation(L"Player_Hurtfly_Loop", L"..\\Resources\\Texture\\Player\\spr_hurtfly_loop", Vector2(0, 20.f), Vector2(50.f, 80.0f)); // pixel 50x43
		//at->CreateAnimation(L"Player_Death", L"..\\Resources\\Texture\\Player\\spr_hurtground", Vector2(0, -10.f), Vector2(57.f, 80.0f)); // pixel 57x25

		cd->SetSize(Vector2(0.3f, 0.4f));
		
		at->CompleteEvent(L"Player_Idle") = std::bind(&PlayerScript::Complete, this);

		at->CompleteEvent(L"Player_Idle_to_Run") = std::bind(&PlayerScript::IdletoRunAnimComplete, this);
		at->CompleteEvent(L"Player_Run_to_Idle") = std::bind(&PlayerScript::RuntoIdleAnimComplete, this);

		at->CompleteEvent(L"Player_PreCrouch") = std::bind(&PlayerScript::PreCrouchAnimComplete, this);
		at->CompleteEvent(L"Player_PostCrouch") = std::bind(&PlayerScript::PostCrouchAnimComplete, this);

		at->CompleteEvent(L"Player_Roll") = std::bind(&PlayerScript::RollAnimComplete, this);

		at->CompleteEvent(L"Player_Attack") = std::bind(&PlayerScript::AttackAnimComplete, this);


		at->PlayAnimation(L"Player_Idle", true);
		mState = ePlayerState::Idle;
	}
	void PlayerScript::Update()
	{
		switch (mState)
		{
		case jw::PlayerScript::ePlayerState::Idle:
			idle();
			break;
		case jw::PlayerScript::ePlayerState::Move_L:
			move();
			break;
		case jw::PlayerScript::ePlayerState::Move_R:
			move();
			break;
		case jw::PlayerScript::ePlayerState::Crouch:
			crouch();
			break;
		case jw::PlayerScript::ePlayerState::Roll:
			roll();
			break;
		case jw::PlayerScript::ePlayerState::Jump_L:
			jump();
			break;
		case jw::PlayerScript::ePlayerState::Jump_R:
			jump();
			break;
		case jw::PlayerScript::ePlayerState::Attack:
			attack();
			break;
		case jw::PlayerScript::ePlayerState::Death:
			death();
			break;
		default:
			break;
		}


		if (Input::GetKeyDown(eKeyCode::Z))
		{
			at->PlayAnimation(L"Player_Idle", true);
			mState = ePlayerState::Idle;
		}
		if (Input::GetKeyDown(eKeyCode::R))
		{
			Vector3 pos = tr->GetPosition();

			tr->SetPosition(0.0f, 1.0f, pos.z);
		}
		if (Input::GetKey(eKeyCode::X))
		{

		}
		if (Input::GetKeyDown(eKeyCode::V))
		{
			at->PlayAnimation(L"Player_Death", false);
			//mState = ePlayerState::Idle_R;
		}

	}
	void PlayerScript::LateUpdate()
	{
	}
	void PlayerScript::Complete()
	{
		int a = 0;
	}
	void PlayerScript::IdletoRunAnimComplete()
	{
		int a = 0;

		//pos.y += 0.05f;
		//tr->SetPosition(pos);
		at->PlayAnimation(L"Player_Run", true);
	}
	void PlayerScript::RuntoIdleAnimComplete()
	{
		//pos.y -= 0.05f;
		//tr->SetPosition(pos);
		at->PlayAnimation(L"Player_Idle", true);
	}
	void PlayerScript::PreCrouchAnimComplete()
	{
		at->PlayAnimation(L"Player_Crouch", true);
	}
	void PlayerScript::PostCrouchAnimComplete()
	{
		at->PlayAnimation(L"Player_Idle", true);
	}
	void PlayerScript::RollAnimComplete()
	{
		mState = ePlayerState::Idle;
		at->PlayAnimation(L"Player_Idle", true);
	}
	void PlayerScript::AttackAnimComplete()
	{
		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		rb->SetGravity(Vector3(0.0f, 15.0f, 0.0f));
		Vector3 velocity = rb->GetVelocity();
		velocity.x = 0.0f;
		velocity.y = 0.0f;
		rb->SetVelocity(velocity);

		if (rb->GetGround() == true)
		{
			mState = ePlayerState::Idle;
			at->PlayAnimation(L"Player_Idle", true);
		}
		if (rb->GetGround() == false)
		{
			Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
			Vector3 velocity = rb->GetVelocity();
			mState = ePlayerState::Jump_L;
			at->PlayAnimation(L"Player_Fall", true);
		}
	}
	void PlayerScript::idle()
	{
		mbAttack = false;

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			mState = ePlayerState::Attack;
		}

		if (Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S))
		{
			mState = ePlayerState::Crouch;
			at->PlayAnimation(L"Player_PreCrouch", true);

		}

		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A))
		{
			at->SetAnimDirection(Animation::eAnimDirection::Left);
			at->PlayAnimation(L"Player_Idle_to_Run", true);
			mState = ePlayerState::Move_L;
		}
		if (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D))
		{
			at->SetAnimDirection(Animation::eAnimDirection::Right);
			at->PlayAnimation(L"Player_Idle_to_Run", true);
			mState = ePlayerState::Move_R;
		}

		if (Input::GetKeyDown(eKeyCode::W))
		{
			rb->SetGround(false);

			Vector3 velocity = rb->GetVelocity();
			velocity.y = -mJumpScale;
			rb->SetVelocity(velocity);

			at->PlayAnimation(L"Player_Jump", true);

			if (at->GetAnimDirection() == Animation::eAnimDirection::Left)
			{
				mState = ePlayerState::Jump_L;
			}
			else
			{
				mState = ePlayerState::Jump_R;
			}
		}
	}
	void PlayerScript::move()
	{
		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			mState = ePlayerState::Attack;
		}

		if (Input::GetKey(eKeyCode::A))
		{
			Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();

			pos.x -= 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::D))
		{
			Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
			pos.x += 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			mState = ePlayerState::Roll;
			at->PlayAnimation(L"Player_Roll", true);
		}

		if (Input::GetKeyUp(eKeyCode::A))
		{
			mState = ePlayerState::Idle;
			at->PlayAnimation(L"Player_Run_to_Idle", true);
		}
		else if (Input::GetKeyUp(eKeyCode::D))
		{
			mState = ePlayerState::Idle;
			at->PlayAnimation(L"Player_Run_to_Idle", true);
		}

		if (Input::GetKeyDown(eKeyCode::W))
		{
			rb->SetGround(false);

			Vector3 velocity = rb->GetVelocity();
			velocity.y = -6.0f;
			rb->SetVelocity(velocity);

			at->PlayAnimation(L"Player_Jump", true);

			if (at->GetAnimDirection() == Animation::eAnimDirection::Left)
			{
				mState = ePlayerState::Jump_L;
			}
			else
			{
				mState = ePlayerState::Jump_R;
			}
		}
	}
	void PlayerScript::crouch()
	{
		//pos.y -= 4.0f * Time::DeltaTime();
		//tr->SetPosition(pos);

		if (Input::GetKeyUp(eKeyCode::S))
		{
			mState = ePlayerState::Idle;
			at->PlayAnimation(L"Player_PostCrouch", true);
		}

		if (Input::GetKeyDown(eKeyCode::A))
		{
			mState = ePlayerState::Roll;
			at->SetAnimDirection(Animation::eAnimDirection::Left);
			at->PlayAnimation(L"Player_Roll", true);
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			mState = ePlayerState::Roll;
			at->SetAnimDirection(Animation::eAnimDirection::Right);
			at->PlayAnimation(L"Player_Roll", true);
		}
	}
	void PlayerScript::roll()
	{
		if (at->GetAnimDirection() == Animation::eAnimDirection::Left)
		{
			Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
			pos.x -= 4.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (at->GetAnimDirection() == Animation::eAnimDirection::Right)
		{
			Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
			pos.x += 4.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
	}
	void PlayerScript::jump()
	{
		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			mState = ePlayerState::Attack;
		}

		if (Input::GetKey(eKeyCode::A))
		{
			Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
			pos.x -= 2.0f * Time::DeltaTime();

			if (mState == ePlayerState::Jump_R)
			{
				mState = ePlayerState::Jump_L;

				if (mbFall)
				{
					at->SetAnimDirection(Animation::eAnimDirection::Left);
					at->PlayAnimation(L"Player_Fall", true);
				}
				else
				{
					at->SetAnimDirection(Animation::eAnimDirection::Left);
					at->PlayAnimation(L"Player_Jump", true);
				}
			}
			tr->SetPosition(pos);
		}
		if (Input::GetKey(eKeyCode::D))
		{
			Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
			pos.x += 2.0f * Time::DeltaTime();

			if (mState == ePlayerState::Jump_L)
			{
				mState = ePlayerState::Jump_R;

				if (mbFall)
				{
					at->SetAnimDirection(Animation::eAnimDirection::Right);
					at->PlayAnimation(L"Player_Fall", true);
				}
				else
				{
					at->SetAnimDirection(Animation::eAnimDirection::Right);
					at->PlayAnimation(L"Player_Jump", true);
				}
			}
			tr->SetPosition(pos);
		}

		Vector3 velocity = rb->GetVelocity();
		velocity.Normalize();

		float angle = atan2(XMVectorGetY(velocity), XMVectorGetX(velocity));

		XMConvertToDegrees(angle);

		if (angle > 0 && mbFall != true)
		{
			mbFall = true;
			at->PlayAnimation(L"Player_Fall", true);
		}

		if (rb->GetGround() == true)
		{
			mJumpTime = 0.0f;
			mbFall = false;
			mState = ePlayerState::Idle;
			at->PlayAnimation(L"Player_Idle", true);
		}
	}
	void PlayerScript::attack()
	{

		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		Vector3 velocity = rb->GetVelocity();

		if (!mbAttack)
		{
			mbAttack = true;

			// ¸¶¿ì½º ÁÂÇ¥°è º¯È¯ 
			Vector3 mousepos = Vector3(Input::GetMousePos().x, Input::GetMousePos().y, 0);
			Viewport viewport;
			viewport.width = 1600.0f;
			viewport.height = 900.0f;
			viewport.x = 0;
			viewport.y = 0;
			viewport.minDepth = 0.0f;
			viewport.maxDepth = 1.0f;

			mousepos = viewport.Unproject(mousepos, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);

			Vector3 PlayerPos = tr->GetPosition();

			float angle = 0.0f;

			float x = mousepos.x - PlayerPos.x;
			float y = mousepos.y - PlayerPos.y;
			angle = atan2(y, x);

			angle = angle * (180.0 / 3.141592);

			Vector2 dir = Vector2(1.0f, 0.0f);
			dir = math::Rotate(dir, angle);


			if (rb->GetGround() == true && mousepos.y < PlayerPos.y)
			{
				//rb->AddForce(Vector3(3.f, 3.f, 0.f));
				//rb->SetGround(false);
				//velocity.x = 2.0f * -dir.x;
				//velocity.y = 3.0f * dir.y;
				//rb->SetVelocity(velocity);
				rb->SetGround(false);
				rb->AddForce(Vector3(100.f * -dir.x, -1000.f, 0.f));
			}
			else if (rb->GetGround() == true && mousepos.y > PlayerPos.y)
			{
				/*rb->SetGround(false);

				velocity.x = 5.0f * -dir.x;
				velocity.y = 5.0f * -dir.y;
				rb->SetVelocity(velocity);*/
				rb->SetGround(false);
				rb->AddForce(Vector3(100.f * -dir.x, -1000.f, 0.f));
			}
			else if (rb->GetGround() == false && mousepos.y > PlayerPos.y)
			{
				//rb->AddForce(Vector3(1500.f * -dir.x, 0 * -dir.y, 0.f));
				rb->AddForce(Vector3(500.f * -dir.x, 500.f * -dir.y, 0.f));
				//velocity.x = 5.0f * -dir.x;
				//velocity.y = 5.0f * -dir.y;
				//rb->SetVelocity(velocity);
			}
			else if (rb->GetGround() == false && mousepos.y < PlayerPos.y)
			{
				velocity.x = 5.0f * -dir.x;
				velocity.y = 1.0f * -dir.y;
				rb->SetVelocity(velocity);
			}


			if (mousepos.x > PlayerPos.x)
			{
				at->SetAnimDirection(Animation::eAnimDirection::Right);
			}
			else
			{
				at->SetAnimDirection(Animation::eAnimDirection::Left);
			}
			at->PlayAnimation(L"Player_Attack", true);
		}

		if (rb->GetGround() == true)
		{
			velocity.x = 0.0f;
			velocity.y = 0.0f;
			rb->SetVelocity(velocity);
			mState = ePlayerState::Idle;
			at->PlayAnimation(L"Player_Idle", true);
		}
	}
	void PlayerScript::death()
	{
	}
}
