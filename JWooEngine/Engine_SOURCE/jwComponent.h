#pragma once
#include "jwEntity.h"

namespace jw
{
	using namespace jw::enums;
	using namespace jw::math;

	class GameObject;
	class Component : public Entity
	{
	public:
		Component(eComponentType type);
		~Component();

		virtual void Initialize();
		// ������ ���� ������Ʈ ����
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		GameObject* GetOwner() { return mOwner; }
		void SetOwner(GameObject* owner) { mOwner = owner; }

		Vector3 GetOwnerPos() const;
		Vector3 GetOwnerWorldPos() const;

	private:
		const eComponentType mType;
		GameObject* mOwner;
	};

}


