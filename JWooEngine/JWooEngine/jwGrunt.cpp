#include "jwGrunt.h"

namespace jw
{
	Grunt::Grunt()
	{
		SetName(L"Grunt");
	}
	Grunt::~Grunt()
	{
	}
	void Grunt::Initialize()
	{
		GameObject::Initialize();
	}
	void Grunt::Update()
	{
		GameObject::Update();
	}
	void Grunt::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Grunt::Render()
	{
		GameObject::Render();
	}
}