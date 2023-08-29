#include "jwPlayerAttackSlash.h"
#include "jwAnimator.h"
#include "jwMeshRenderer.h"
#include "jwResources.h"
#include "jwObject.h"
#include "jwPlayer.h"

namespace jw
{
	PlayerAttackSlash::PlayerAttackSlash(Player* player)
	{
		mPlayer = player;
	}
	PlayerAttackSlash::~PlayerAttackSlash()
	{
	}
	void PlayerAttackSlash::Initialize()
	{
		SetName(L"PlayerAttackSlash");

		MeshRenderer* mMeshRenderer = AddComponent<MeshRenderer>();
		mMeshRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mMeshRenderer->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		mAnimator = AddComponent<Animator>();
		mAnimator->SetAnimDirection(mPlayer->GetComponent<Animator>()->GetAnimDirection());
		mAnimator->CreateAnimations(L"Attack_Slash", L"..\\Resources\\Texture\\Player_SFX\\spr_slash", 100, 0.04f);

		mAnimator->CompleteEvent(L"Attack_Slash") = std::bind(&PlayerAttackSlash::AnimComplete, this);

		mAnimator->PlayAnimation(L"Attack_Slash", true);

		GameObject::Initialize();
	}
	void PlayerAttackSlash::Update()
	{
		Transform* SlashTr = GetComponent<Transform>();

		Transform* PlayerTr = mPlayer->GetComponent<Transform>();
		Vector3 PlayerPos = PlayerTr->GetPosition();
		SlashTr->SetPosition(Vector3(PlayerPos.x, PlayerPos.y, PlayerPos.z - 0.1f));

		GameObject::Update();
	}
	void PlayerAttackSlash::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void PlayerAttackSlash::Render()
	{
		GameObject::Render();
	}
	void PlayerAttackSlash::AnimComplete()
	{
		object::Destroy(this);
	}
}