#include "jwPlayer.h"

namespace jw
{
	Player::Player()
	{
	}

	Player::~Player()
	{
	}

	void Player::Initialize()
	{
		SetName(L"Player");

		GameObject::Initialize();
	}

	void Player::Update()
	{

		GameObject::Update();
	}

	void Player::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Player::Render()
	{
		GameObject::Render();
	}

}