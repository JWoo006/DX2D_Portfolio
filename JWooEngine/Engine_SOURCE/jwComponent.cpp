#include "jwComponent.h"
#include "jwGameObject.h"

namespace jw
{
	Component::Component(eComponentType type)
		: mType(type)
	{
	}
	Component::~Component()
	{
	}
	void Component::Initialize()
	{
	}
	void Component::Update()
	{
	}
	void Component::LateUpdate()
	{
	}
	void Component::Render()
	{
	}

	Vector3 Component::GetOwnerPos() const
	{
		return mOwner->GetPos();
	}

	Vector3 Component::GetOwnerWorldPos() const
	{
		return mOwner->GetWorldPos();
	}
}


