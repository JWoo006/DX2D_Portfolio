#include "jwPlayerScript.h"
#include "jwCameraScript.h"
#include "jwTransform.h"
#include "jwGameObject.h"
#include "jwTime.h"
#include "jwInput.h"
#include "jwAnimator.h"
#include "jwCollider2D.h"
#include "jwRigidbody.h"
#include "jwObject.h"

#include "jwCamera.h"

#include "jwGroundScript.h"

#include "jwPlayerAttackSlash.h"

namespace jw
{

	PlayerScript::PlayerScript()
		: mJumpScale(5.0f)
		, mAtackJumpScale(0.0f)
		, mAttackTime(0.0f)
		, mAttackDelay(0.0f)
		, mbFirstAttack(true)
		, mAttackDirection(Vector3::Zero)
	{
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initialize()
	{
		mJumpScale = 5.0f;
		// ³ëÆ®ºÏ 100, µ¥Å¾ 1000
		mAtackJumpScale = 100.0f;

		mTransform = GetOwner()->GetComponent<Transform>();
		mCollider = GetOwner()->GetComponent<Collider2D>();
		mAnimator = GetOwner()->GetComponent<Animator>();

		mRigidbody = GetOwner()->GetComponent<Rigidbody>();


		mAnimator->CreateAnimations(L"Player_Idle", L"..\\Resources\\Texture\\Player\\spr_idle", 80, 0.1f);
		//mAnimator->CreateAnimation(L"Player_Idle", L"..\\Resources\\Texture\\Player\\spr_idle", Vector2(0.0), Vector2(36.1f, 100.0f)); // ÇÈ¼¿ 36X35

		mAnimator->CreateAnimations(L"Player_Idle_to_Run", L"..\\Resources\\Texture\\Player\\spr_idle_to_run", 80, 0.05f);
		mAnimator->CreateAnimations(L"Player_Run", L"..\\Resources\\Texture\\Player\\spr_run", 80, 0.1f);
		mAnimator->CreateAnimations(L"Player_Run_to_Idle", L"..\\Resources\\Texture\\Player\\spr_run_to_idle", 80, 0.05f);
		//mAnimator->CreateAnimation(L"Player_Idle_to_Run", L"..\\Resources\\Texture\\Player\\spr_idle_to_run", Vector2(0.0), Vector2(44.f, 80.0f), 0.05f); // pixel 44x32
		//mAnimator->CreateAnimation(L"Player_Run", L"..\\Resources\\Texture\\Player\\spr_run", Vector2(0.0), Vector2(44.f, 80.0f)); // ÇÈ¼¿ 44X32
		//mAnimator->CreateAnimation(L"Player_Run_to_Idle", L"..\\Resources\\Texture\\Player\\spr_run_to_idle", Vector2(0, 13.f), Vector2(52.f, 80.0f), 0.05f); // pixel 52x36

		mAnimator->CreateAnimations(L"Player_PreCrouch", L"..\\Resources\\Texture\\Player\\spr_precrouch", 80, 0.05f);
		mAnimator->CreateAnimations(L"Player_Crouch", L"..\\Resources\\Texture\\Player\\spr_crouch", 80, 0.1f);
		mAnimator->CreateAnimations(L"Player_PostCrouch", L"..\\Resources\\Texture\\Player\\spr_postcrouch", 80, 0.1f);
		//mAnimator->CreateAnimation(L"Player_PreCrouch", L"..\\Resources\\Texture\\Player\\spr_precrouch", Vector2(0, 10.f), Vector2(36.f, 100.0f), 0.05f); // pixel 36x40
		//mAnimator->CreateAnimation(L"Player_Crouch", L"..\\Resources\\Texture\\Player\\spr_crouch", Vector2(0, 10.f), Vector2(36.f, 100.0f)); // ÇÈ¼¿ 36x40
		//mAnimator->CreateAnimation(L"Player_PostCrouch", L"..\\Resources\\Texture\\Player\\spr_postcrouch", Vector2(0, 10.f), Vector2(36.f, 100.0f), 0.05f); // pixel 36x40

		mAnimator->CreateAnimations(L"Player_Roll", L"..\\Resources\\Texture\\Player\\spr_roll", 80, 0.05f);
		//mAnimator->CreateAnimation(L"Player_Roll", L"..\\Resources\\Texture\\Player\\spr_roll", Vector2(0, -5.f), Vector2(48.f, 100.0f), 0.05f); // pixel 48x33

		mAnimator->CreateAnimations(L"Player_Attack", L"..\\Resources\\Texture\\Player\\spr_attack", 80, 0.04f);
		//mAnimator->CreateAnimation(L"Player_Attack", L"..\\Resources\\Texture\\Player\\spr_attack", Vector2(0.0), Vector2(62.f, 117.0f), 0.05f); // ÇÈ¼¿ 62X42


		mAnimator->CreateAnimations(L"Player_Jump", L"..\\Resources\\Texture\\Player\\spr_jump", 80, 0.05f);
		mAnimator->CreateAnimations(L"Player_Fall", L"..\\Resources\\Texture\\Player\\spr_fall", 80, 0.05f);
		//mAnimator->CreateAnimation(L"Player_Jump", L"..\\Resources\\Texture\\Player\\spr_jump", Vector2(0, 10.f), Vector2(32.f, 100.0f), 0.05f); // ÇÈ¼¿ 32X42
		//mAnimator->CreateAnimation(L"Player_Fall", L"..\\Resources\\Texture\\Player\\spr_fall", Vector2(0, 20.f), Vector2(42.f, 100.0f), 0.05f); // ÇÈ¼¿ 42x48

		mAnimator->CreateAnimations(L"Player_WallGrab", L"..\\Resources\\Texture\\Player\\spr_wallgrab", 80, 0.1f);
		//mAnimator->CreateAnimation(L"Player_WallGrab", L"..\\Resources\\Texture\\Player\\spr_wallgrab", Vector2(0, 10), Vector2(48.f, 100.0f)); // ÇÈ¼¿ 48x38

		mAnimator->CreateAnimations(L"Player_Hurtfly_Begin", L"..\\Resources\\Texture\\Player\\spr_hurtfly_begin", 80, 0.1f);
		mAnimator->CreateAnimations(L"Player_Hurtfly_Loop", L"..\\Resources\\Texture\\Player\\spr_hurtfly_loop", 80, 0.1f);
		mAnimator->CreateAnimations(L"Player_Death", L"..\\Resources\\Texture\\Player\\spr_hurtground", 80, 0.1f);
		//mAnimator->CreateAnimation(L"Player_Hurtfly_Begin", L"..\\Resources\\Texture\\Player\\spr_hurtfly_begin", Vector2(0, 20.f), Vector2(50.f, 80.0f)); // pixel 50x43
		//mAnimator->CreateAnimation(L"Player_Hurtfly_Loop", L"..\\Resources\\Texture\\Player\\spr_hurtfly_loop", Vector2(0, 20.f), Vector2(50.f, 80.0f)); // pixel 50x43
		//mAnimator->CreateAnimation(L"Player_Death", L"..\\Resources\\Texture\\Player\\spr_hurtground", Vector2(0, -10.f), Vector2(57.f, 80.0f)); // pixel 57x25

		mCollider->SetSize(Vector2(0.3f, 0.4f));
		
		mAnimator->CompleteEvent(L"Player_Idle") = std::bind(&PlayerScript::Complete, this);

		mAnimator->CompleteEvent(L"Player_Idle_to_Run") = std::bind(&PlayerScript::IdletoRunAnimComplete, this);
		mAnimator->CompleteEvent(L"Player_Run_to_Idle") = std::bind(&PlayerScript::RuntoIdleAnimComplete, this);

		mAnimator->CompleteEvent(L"Player_PreCrouch") = std::bind(&PlayerScript::PreCrouchAnimComplete, this);
		mAnimator->CompleteEvent(L"Player_PostCrouch") = std::bind(&PlayerScript::PostCrouchAnimComplete, this);

		mAnimator->CompleteEvent(L"Player_Roll") = std::bind(&PlayerScript::RollAnimComplete, this);

		mAnimator->CompleteEvent(L"Player_Attack") = std::bind(&PlayerScript::AttackAnimComplete, this);


		mAnimator->PlayAnimation(L"Player_Idle", true);
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
			mAnimator->PlayAnimation(L"Player_Idle", true);
			mState = ePlayerState::Idle;
		}
		if (Input::GetKeyDown(eKeyCode::R))
		{
			Vector3 pos = mTransform->GetPosition();

			mTransform->SetPosition(0.0f, 1.0f, pos.z);
		}
		if (Input::GetKey(eKeyCode::X))
		{

		}
		if (Input::GetKeyDown(eKeyCode::V))
		{
			mAnimator->PlayAnimation(L"Player_Death", false);
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
		mAnimator->PlayAnimation(L"Player_Run", true);
	}
	void PlayerScript::RuntoIdleAnimComplete()
	{
		//pos.y -= 0.05f;
		//tr->SetPosition(pos);
		mAnimator->PlayAnimation(L"Player_Idle", true);
	}
	void PlayerScript::PreCrouchAnimComplete()
	{
		mAnimator->PlayAnimation(L"Player_Crouch", true);
	}
	void PlayerScript::PostCrouchAnimComplete()
	{
		mAnimator->PlayAnimation(L"Player_Idle", true);
	}
	void PlayerScript::RollAnimComplete()
	{
		mState = ePlayerState::Idle;
		mAnimator->PlayAnimation(L"Player_Idle", true);
	}
	void PlayerScript::AttackAnimComplete()
	{
		mbFirstAttack = true;
		mState = ePlayerState::Idle;
		mAnimator->PlayAnimation(L"Player_Idle", true);

		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		rb->SetGravity(Vector3(0.0f, 15.0f, 0.0f));
		Vector3 velocity = rb->GetVelocity();
		velocity.x = 0.0f;
		velocity.y = 0.0f;
		rb->SetVelocity(velocity);

		if (rb->GetGround() == true)
		{
			mState = ePlayerState::Idle;
			mAnimator->PlayAnimation(L"Player_Idle", true);
		}
		if (rb->GetGround() == false)
		{
			Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
			Vector3 velocity = rb->GetVelocity();
			mState = ePlayerState::Jump_L;
			mAnimator->PlayAnimation(L"Player_Fall", true);
		}
	}
	void PlayerScript::idle()
	{
		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			mState = ePlayerState::Attack;
		}

		if (Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S))
		{
			mState = ePlayerState::Crouch;
			mAnimator->PlayAnimation(L"Player_PreCrouch", true);

		}

		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A))
		{
			mAnimator->SetAnimDirection(Animation::eAnimDirection::Left);
			mAnimator->PlayAnimation(L"Player_Idle_to_Run", true);
			mState = ePlayerState::Move_L;
		}
		if (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D))
		{
			mAnimator->SetAnimDirection(Animation::eAnimDirection::Right);
			mAnimator->PlayAnimation(L"Player_Idle_to_Run", true);
			mState = ePlayerState::Move_R;
		}

		if (Input::GetKeyDown(eKeyCode::W))
		{
			mRigidbody->SetGround(false);

			Vector3 velocity = mRigidbody->GetVelocity();
			velocity.y = -mJumpScale;
			mRigidbody->SetVelocity(velocity);

			mAnimator->PlayAnimation(L"Player_Jump", true);

			if (mAnimator->GetAnimDirection() == Animation::eAnimDirection::Left)
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
			mTransform->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::D))
		{
			Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
			pos.x += 2.0f * Time::DeltaTime();
			mTransform->SetPosition(pos);
		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			mState = ePlayerState::Roll;
			mAnimator->PlayAnimation(L"Player_Roll", true);
		}

		if (Input::GetKeyUp(eKeyCode::A))
		{
			mState = ePlayerState::Idle;
			mAnimator->PlayAnimation(L"Player_Run_to_Idle", true);
		}
		else if (Input::GetKeyUp(eKeyCode::D))
		{
			mState = ePlayerState::Idle;
			mAnimator->PlayAnimation(L"Player_Run_to_Idle", true);
		}

		if (Input::GetKeyDown(eKeyCode::W))
		{
			mRigidbody->SetGround(false);

			Vector3 velocity = mRigidbody->GetVelocity();
			velocity.y = -6.0f;
			mRigidbody->SetVelocity(velocity);

			mAnimator->PlayAnimation(L"Player_Jump", true);

			if (mAnimator->GetAnimDirection() == Animation::eAnimDirection::Left)
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
			mAnimator->PlayAnimation(L"Player_PostCrouch", true);
		}

		if (Input::GetKeyDown(eKeyCode::A))
		{
			mState = ePlayerState::Roll;
			mAnimator->SetAnimDirection(Animation::eAnimDirection::Left);
			mAnimator->PlayAnimation(L"Player_Roll", true);
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			mState = ePlayerState::Roll;
			mAnimator->SetAnimDirection(Animation::eAnimDirection::Right);
			mAnimator->PlayAnimation(L"Player_Roll", true);
		}
	}
	void PlayerScript::roll()
	{
		if (mAnimator->GetAnimDirection() == Animation::eAnimDirection::Left)
		{
			Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
			pos.x -= 4.0f * Time::DeltaTime();
			mTransform->SetPosition(pos);
		}
		if (mAnimator->GetAnimDirection() == Animation::eAnimDirection::Right)
		{
			Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
			pos.x += 4.0f * Time::DeltaTime();
			mTransform->SetPosition(pos);
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
					mAnimator->SetAnimDirection(Animation::eAnimDirection::Left);
					mAnimator->PlayAnimation(L"Player_Fall", true);
				}
				else
				{
					mAnimator->SetAnimDirection(Animation::eAnimDirection::Left);
					mAnimator->PlayAnimation(L"Player_Jump", true);
				}
			}
			mTransform->SetPosition(pos);
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
					mAnimator->SetAnimDirection(Animation::eAnimDirection::Right);
					mAnimator->PlayAnimation(L"Player_Fall", true);
				}
				else
				{
					mAnimator->SetAnimDirection(Animation::eAnimDirection::Right);
					mAnimator->PlayAnimation(L"Player_Jump", true);
				}
			}
			mTransform->SetPosition(pos);
		}

		Vector3 velocity = mRigidbody->GetVelocity();
		velocity.Normalize();

		float angle = atan2(XMVectorGetY(velocity), XMVectorGetX(velocity));

		XMConvertToDegrees(angle);

		if (angle > 0 && mbFall != true)
		{
			mbFall = true;
			mAnimator->PlayAnimation(L"Player_Fall", true);
		}

		if (mRigidbody->GetGround() == true)
		{
			mJumpTime = 0.0f;
			mbFall = false;
			mState = ePlayerState::Idle;
			mAnimator->PlayAnimation(L"Player_Idle", true);
		}
	}
	void PlayerScript::attack()
	{
		mAttackDelay += Time::DeltaTime();

		Transform* PlayerTr = GetOwner()->GetComponent<Transform>();
		Vector3 PlayerPos = PlayerTr->GetPosition();

		if (mbFirstAttack == true)
		{
			Vector3 MousePos = Input::GetWorldMousePos();

			if (MousePos.x > PlayerPos.x)
			{
				mAnimator->SetAnimDirection(Animation::eAnimDirection::Right);
			}
			else
			{
				mAnimator->SetAnimDirection(Animation::eAnimDirection::Left);
			}

			mAnimator->PlayAnimation(L"Player_Attack", true);
			CreateAttackSlash();

			mRigidbody->SetVelocity(Vector3::Zero);
			

			Vector3 vect;
			vect.x = MousePos.x - PlayerPos.x;
			vect.y = MousePos.y - PlayerPos.y;
			vect.Normalize();
			mAttackDirection = vect;

			if (mRigidbody->GetGround() == true)
			{
				mRigidbody->SetGround(false);

				// Áö»ó ¼öÆò º£±â
				if (abs(MousePos.y - PlayerPos.y) < 0.3)
				{
					mRigidbody->AddVelocity(Vector3(mAttackDirection.x * -3.f, -1.5f, mAttackDirection.z));
				}
				else if (MousePos.y > PlayerPos.y)
				{
					mRigidbody->AddVelocity(mAttackDirection * -5.f);
				}
				else
				{
					mRigidbody->AddVelocity(Vector3(mAttackDirection.x * -3.f, -1.f, mAttackDirection.z));
				}	
			}
			else if (mRigidbody->GetGround() == false)
			{
				// °øÁß ¼öÆò º£±â
				if (abs(MousePos.y - PlayerPos.y) < 0.2 )
				{
					mRigidbody->AddVelocity(Vector3(mAttackDirection.x * -4.f, -2.f, mAttackDirection.z));
				}
				else if (MousePos.y < PlayerPos.y)
				{
					mRigidbody->AddVelocity(Vector3(mAttackDirection.x * -4.f, 0.f, mAttackDirection.z));
				}
				else
				{
					mRigidbody->AddVelocity(mAttackDirection * -4.f);
					//mRigidbody->AddVelocity(Vector3(mAttackDirection.x * -5.f, mAttackDirection.y * -7.f, mAttackDirection.z));
				}

				
			}

			mAttackDelay = 0.f;

			mbFirstAttack = false;
		}

		/*if (mState == ePlayerState::Attack)
		{
			mAttackTime += Time::DeltaTime();
			if (0.15f <= mAttackTime)
			{
				mState = ePlayerState::Idle;
				mAttackTime = 0.f;
				mbFirstAttack = false;
				mAttackDirection = Vector3::Zero;
			}
			else
			{
				if (mbFirstAttack)
					mRigidbody->AddForce(mAttackDirection * 40.f);
			}
		}*/

		
	}
	void PlayerScript::death()
	{
	}
	void PlayerScript::CreateAttackSlash()
	{
		Player* player = dynamic_cast<Player*>(GetOwner());
		Vector3 PlayerPos = mTransform->GetPosition();
		PlayerAttackSlash* SlashObj
			= object::Instantiate<PlayerAttackSlash>(eLayerType::Effect, Vector3(PlayerPos.x, PlayerPos.y, PlayerPos.z - 0.1f), player);
		Transform* SlashTr = SlashObj->GetComponent<Transform>();
		//SlashTr->SetRotation(0.0f, 0.0f, RotateDegree(angle));
		Vector3 MousePos = Input::GetWorldMousePos();
		Vector3 Direction = MousePos - GetOwnerWorldPos();
		Direction.Normalize();

		SlashTr->SetPosition(GetOwnerWorldPos() + Direction);
		Vector3 rotation = SlashObj->GetRotation();

		rotation.z = atan2(MousePos.y - SlashObj->GetPos().y, MousePos.x - SlashObj->GetPos().x);
		rotation.z = rotation.z * 180 / XM_PI;

		if (mAnimator->GetAnimDirection() == Animation::eAnimDirection::Left)
		{
			SlashObj->SetRotation(Vector3(0.0f, 0.0f, RotateDegree(rotation.z - 180)));
		}
		else
		{
			SlashObj->SetRotation(Vector3(0.0f, 0.0f, RotateDegree(rotation.z)));
		}
		
		
	}
}
