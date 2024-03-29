#include "jwGameObject.h"
#include "jwRenderer.h"
#include "jwGraphicDevice_Dx11.h"
#include "jwTransform.h"

namespace jw
{
	GameObject::GameObject()
		: mState(eState::Active)
	{
		AddComponent<Transform>();
	}

	GameObject::~GameObject()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			delete comp;
			comp = nullptr;
		}

		for (Script* script : mScripts)
		{
			if (script == nullptr)
				continue;

			delete script;
			script = nullptr;
		}
	}

	void GameObject::Initialize()
	{

	}

	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			comp->Update();
		}

		for (Script* script : mScripts)
		{
			script->Update();
		}
	}

	void GameObject::LateUpdate()
	{
		for (Component* comp : mComponents)
		{
			comp->LateUpdate();
		}

		for (Script* script : mScripts)
		{
			script->LateUpdate();
		}
	}

	void GameObject::Render()
	{
		for (Component* comp : mComponents)
		{
			comp->Render();
		}
		//상수버퍼로 위치정보 크기정보, 색깔, 업데이트 해줘야한다.

		for (Script* script : mScripts)
		{
			script->Render();
		}
	}

	Vector3 GameObject::GetScale()
	{
		return GetComponent<Transform>()->GetScale();
	}

	Vector3 GameObject::GetRotation()
	{
		return GetComponent<Transform>()->GetRotation();
	}

	Vector3 GameObject::GetPos()
	{
		return GetComponent<Transform>()->GetPosition();
	}

	Vector3 GameObject::GetWorldPos()
	{
		return GetComponent<Transform>()->GetWorldPosition();
	}

	void GameObject::SetPos(Vector3 pos)
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPosition(pos);
	}

	void GameObject::SetRotation(Vector3 rotate)
	{
		if (nullptr != GetComponent<Transform>())
		{
			GetComponent<Transform>()->SetRotation(rotate);
		}
	}
}
