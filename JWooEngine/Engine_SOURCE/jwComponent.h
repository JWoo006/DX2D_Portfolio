#pragma once
#include "jwEntity.h"

namespace jw
{
	class Component : public Entity
	{
	public:
		Component();
		~Component();

		virtual void Initialize();

		// 순서에 따라 업데이트 구분
		virtual void FixedUpdate();
		virtual void Update();
		virtual void LateUpdate();

		virtual void Render();

	private:
		const enums::eComponentType mType;
	};

}


