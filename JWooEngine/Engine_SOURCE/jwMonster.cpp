#include "jwMonster.h"
#include "jwRenderer.h"
#include <random>

namespace jw
{
	Monster::Monster()
	{
		SetName(L"Monster");
		UINT64 a = GetID();

		this->SetState(GameObject::Active);

		std::random_device randomPos;
		std::mt19937 genPos(randomPos());
		std::uniform_real_distribution<float> distribute(-1.0f, 1.0f);

		std::random_device randomColor;
		std::mt19937 genColor(randomColor());
		std::uniform_real_distribution<float> distributeColor(0.0f, 1.0f);
		
		MonsterInfo.pos = Vector4(distribute(genPos), distribute(genPos), 0.0f, 1.0f);
		MonsterInfo.color = Vector4(distributeColor(genColor), distributeColor(genColor), distributeColor(genColor), 1.0f);
		MonsterInfo.scale = Vector4(0.5f, 0.5f, 0.0f, 0.0f);

		SetInfo(MonsterInfo);
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