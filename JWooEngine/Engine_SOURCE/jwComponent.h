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
		// 순서에 따라 업데이트 구분
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		GameObject* GetOwner() { return mOwner; }
		void SetOwner(GameObject* owner) { mOwner = owner; }

	private:
		const eComponentType mType;
		GameObject* mOwner;
	};

}


