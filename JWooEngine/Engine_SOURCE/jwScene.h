#pragma once
#include "jwEntity.h"
#include "jwGameObject.h"
#include "jwPlayer.h"
#include "jwMonster.h"

namespace jw
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:
		std::vector<GameObject*> mGameObjects;

		Player* player;
		Monster* monster;
	};
}