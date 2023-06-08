#pragma once
#include "jwEntity.h"

namespace jw
{
	using namespace jw::enums;

	class Component : public Entity
	{
	public:
		Component();
		~Component();

		virtual void Initialize();

		// ������ ���� ������Ʈ ����
		virtual void Update();
		virtual void LateUpdate();

		virtual void Render();

	private:
		const eComponentType mType;
	};

}


