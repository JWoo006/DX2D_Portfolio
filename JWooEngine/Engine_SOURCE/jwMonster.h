#pragma once
#include "jwGameObject.h"
#include "jwRenderer.h"

namespace jw
{
	using namespace renderer;
	class Monster : public GameObject
	{
	public:
		Monster();
		~Monster();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		Info GetMonsterInfo() { return MonsterInfo; }
		void SetMonsterInfo(Info info) { MonsterInfo = info; }

	private:
		Info MonsterInfo;
	};

}

