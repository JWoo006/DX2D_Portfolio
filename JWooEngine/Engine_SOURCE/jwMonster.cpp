#include "jwMonster.h"
#include "jwRenderer.h"

namespace jw
{
	Monster::Monster()
	{
		SetName(L"Monster");

		UINT64 a = GetID();

		MonsterInfo.pos = Vector4(0.5f, 0.0f, 0.0f, 1.0f);
		MonsterInfo.color = Vector4(0.0f, 1.0f, 1.0f, 1.0f);
		MonsterInfo.scale = Vector4(1.0f, 1.0f, 0.0f, 0.0f);
	}
	Monster::~Monster()
	{
	}
	void Monster::Initialize()
	{
		GameObject::Initialize();
	}
	void Monster::Update()
	{
		GameObject::Update();
	}
	void Monster::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Monster::Render()
	{
		renderer::constantBuffer->SetData(&MonsterInfo);

		GameObject::Render();
	}
}