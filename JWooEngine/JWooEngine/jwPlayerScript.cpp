#include "jwPlayerScript.h"
#include "jwCameraScript.h"
#include "jwTransform.h"
#include "jwGameObject.h"
#include "jwTime.h"
#include "jwInput.h"
#include "jwAnimator.h"
#include "jwCollider2D.h"

#include "jwCamera.h"


namespace jw
{
	PlayerScript::PlayerScript()
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

		pos = tr->GetPosition();

		at->CreateAnimation(L"Player_Idle", L"..\\Resources\\Texture\\Player\\spr_idle", Vector2(0.0), Vector2(36.1f, 100.0f)); // ÇÈ¼¿ 36X35

		at->CreateAnimation(L"Player_Idle_to_Run", L"..\\Resources\\Texture\\Player\\spr_idle_to_run", Vector2(0.0), Vector2(44.f, 80.0f), 0.05f); // pixel 44x32
		at->CreateAnimation(L"Player_Run", L"..\\Resources\\Texture\\Player\\spr_run", Vector2(0.0), Vector2(44.f, 80.0f)); // ÇÈ¼¿ 44X32
		at->CreateAnimation(L"Player_Run_to_Idle", L"..\\Resources\\Texture\\Player\\spr_run_to_idle", Vector2(0, 13.f), Vector2(52.f, 80.0f), 0.05f); // pixel 52x36

		at->CreateAnimation(L"Player_PreCrouch", L"..\\Resources\\Texture\\Player\\spr_precrouch", Vector2(0, 10.f), Vector2(36.f, 100.0f), 0.05f); // pixel 36x40
		at->CreateAnimation(L"Player_Crouch", L"..\\Resources\\Texture\\Player\\spr_crouch", Vector2(0, 10.f), Vector2(36.f, 100.0f)); // ÇÈ¼¿ 36x40
		at->CreateAnimation(L"Player_PostCrouch", L"..\\Resources\\Texture\\Player\\spr_postcrouch", Vector2(0, 10.f), Vector2(36.f, 100.0f), 0.05f); // pixel 36x40

		at->CreateAnimation(L"Player_Roll", L"..\\Resources\\Texture\\Player\\spr_roll", Vector2(0, -5.f), Vector2(48.f, 100.0f), 0.05f); // pixel 48x33

		at->CreateAnimation(L"Player_Attack", L"..\\Resources\\Texture\\Player\\spr_attack", Vector2(0.0), Vector2(62.f, 117.0f), 0.05f); // ÇÈ¼¿ 62X42
		at->CreateAnimation(L"Player_Jump", L"..\\Resources\\Texture\\Player\\spr_jump", Vector2(0.0), Vector2(32.f, 117.0f), 0.05f); // ÇÈ¼¿ 32X42

		at->CreateAnimation(L"Player_Death", L"..\\Resources\\Texture\\Player\\spr_hurtground", Vector2(0, -10.f), Vector2(57.f, 80.0f)); // pixel 57x25

		tr->SetScale(Vector3(2.5f, 2.5f, 1.0f));		
		cd->SetSize(Vector2(0.1f, 0.16f));
		cd->SetCenter(Vector2(0.f, -0.05f));

		
		at->CompleteEvent(L"Player_Idle") = std::bind(&PlayerScript::Complete, this);

		at->CompleteEvent(L"Player_Idle_to_Run") = std::bind(&PlayerScript::IdletoRunAnimComplete, this);
		at->CompleteEvent(L"Player_Run_to_Idle") = std::bind(&PlayerScript::RuntoIdleAnimComplete, this);

		at->CompleteEvent(L"Player_PreCrouch") = std::bind(&PlayerScript::PreCrouchAnimComplete, this);
		at->CompleteEvent(L"Player_PostCrouch") = std::bind(&PlayerScript::PostCrouchAnimComplete, this);

		at->CompleteEvent(L"Player_Roll") = std::bind(&PlayerScript::RollAnimComplete, this);

		at->CompleteEvent(L"Player_Attack") = std::bind(&PlayerScript::attack, this);


		at->PlayAnimation(L"Player_Idle", true);
		mPlayerState = ePlayerState::Idle;
	}
	void PlayerScript::Update()
	{
		switch (mPlayerState)
		{
		case jw::PlayerScript::ePlayerState::Idle:
			tr->SetScale(Vector3(2.5f, 2.5f, 1.0f));
			cd->SetSize(Vector2(0.1f, 0.16f));
			cd->SetCenter(Vector2(0.f, -0.05f));
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
		
		if (Input::GetKey(eKeyCode::W))
		{
			pos.y += 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			at->PlayAnimation(L"Player_Idle", true);
			mPlayerState = ePlayerState::Idle;
		}
		if (Input::GetKey(eKeyCode::X))
		{
			
		}
		if (Input::GetKeyDown(eKeyCode::V))
		{
			at->PlayAnimation(L"Player_Death", false);
			//mPlayerState = ePlayerState::Idle_R;
		}

	}
	void PlayerScript::LateUpdate()
	{
		// ¸¶¿ì½º ÁÂÇ¥°è º¯È¯ 
		Vector3 pos(600, 450, 0.0f);
		Vector3 pos2(600, 450, 1000.0f);
		Viewport viewport;
		viewport.width = 1600.0f;
		viewport.height = 900.0f;
		viewport.x = 0;
		viewport.y = 0;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		pos = viewport.Unproject(pos, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);
		pos2 = viewport.Unproject(pos2, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);
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
		mPlayerState = ePlayerState::Idle;
		at->PlayAnimation(L"Player_Idle", true);
	}
	void PlayerScript::idle()
	{
		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			//mPlayerState = ePlayerState::Attack;
			at->PlayAnimation(L"Player_Attack", true);
		}

		if (Input::GetKeyDown(eKeyCode::S) || Input::GetKey(eKeyCode::S))
		{
			mPlayerState = ePlayerState::Crouch;
			at->PlayAnimation(L"Player_PreCrouch", true);
		}

		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKey(eKeyCode::A))
		{
			at->SetAnimDirection(Animation::eAnimDirection::Left);
			at->PlayAnimation(L"Player_Idle_to_Run", true);
			mPlayerState = ePlayerState::Move_L;
		}
		if (Input::GetKeyDown(eKeyCode::D) || Input::GetKey(eKeyCode::D))
		{
			at->SetAnimDirection(Animation::eAnimDirection::Right);
			at->PlayAnimation(L"Player_Idle_to_Run", true);
			mPlayerState = ePlayerState::Move_R;
		}
	}
	void PlayerScript::move()
	{
		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			//mPlayerState = ePlayerState::Attack;
			at->PlayAnimation(L"Player_Attack", true);
		}

		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::D))
		{
			pos.x += 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			mPlayerState = ePlayerState::Roll;
			at->PlayAnimation(L"Player_Roll", true);
		}

		if (Input::GetKeyUp(eKeyCode::A))
		{
			mPlayerState = ePlayerState::Idle;
			at->PlayAnimation(L"Player_Run_to_Idle", true);
		}
		else if (Input::GetKeyUp(eKeyCode::D))
		{
			mPlayerState = ePlayerState::Idle;
			at->PlayAnimation(L"Player_Run_to_Idle", true);
		}

	}
	void PlayerScript::crouch()
	{
		if (Input::GetKeyUp(eKeyCode::S))
		{
			mPlayerState = ePlayerState::Idle;
			at->PlayAnimation(L"Player_PostCrouch", true);
		}

		if (Input::GetKeyDown(eKeyCode::A))
		{
			mPlayerState = ePlayerState::Roll;
			at->SetAnimDirection(Animation::eAnimDirection::Left);
			at->PlayAnimation(L"Player_Roll", true);
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			mPlayerState = ePlayerState::Roll;
			at->SetAnimDirection(Animation::eAnimDirection::Right);
			at->PlayAnimation(L"Player_Roll", true);
		}
	}
	void PlayerScript::roll()
	{
		if (at->GetAnimDirection() == Animation::eAnimDirection::Left)
		{
			pos.x -= 4.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (at->GetAnimDirection() == Animation::eAnimDirection::Right)
		{
			pos.x += 4.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		
	}
	void PlayerScript::jump()
	{
	}
	void PlayerScript::attack()
	{
		if (at->GetAnimDirection() == Animation::eAnimDirection::Left)
		{
			mPlayerState = ePlayerState::Idle;
			at->PlayAnimation(L"Player_Idle", true);
		}
		else
		{
			mPlayerState = ePlayerState::Idle;
			at->PlayAnimation(L"Player_Idle", true);
		}
	}
	void PlayerScript::death()
	{
	}
}
