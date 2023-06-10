#include "jwPlayer.h"
#include "jwInput.h"
#include "jwTime.h"

namespace jw
{
	Player::Player()
	{
		SetName(L"Player");
		UINT64 a = GetID();

		this->SetState(GameObject::Active);

		mPlayerInfo.pos = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
		mPlayerInfo.color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		mPlayerInfo.scale = Vector4(0.5f, 0.5f, 0.0f, 0.0f);
	}
	Player::~Player()
	{
	}
	void Player::Initialize()
	{
		GameObject::Initialize();
	}
	void Player::Update()
	{
		// Á¶ÀÛ
		if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT))
		{
			mPlayerInfo.pos.x -= 0.5f * Time::DeltaTime();
		}
		if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT))
		{
			mPlayerInfo.pos.x += 0.5f * Time::DeltaTime();
		}
		if (Input::GetKeyDown(eKeyCode::UP) || Input::GetKey(eKeyCode::UP))
		{
			mPlayerInfo.pos.y += 0.5f * Time::DeltaTime();
		}
		if (Input::GetKeyDown(eKeyCode::DOWN) || Input::GetKey(eKeyCode::DOWN))
		{
			mPlayerInfo.pos.y -= 0.5f * Time::DeltaTime();
		}
		if (Input::GetKeyDown(eKeyCode::V))
		{
			mPlayerInfo.scale *= 1.2f;
		}


		GameObject::Update();
	}
	void Player::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Player::Render()
	{
		renderer::constantBuffer->SetData(&mPlayerInfo);

		GameObject::Render();
	}
}