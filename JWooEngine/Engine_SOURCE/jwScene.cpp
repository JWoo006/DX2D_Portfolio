#include "jwScene.h"

namespace jw
{
	Scene::Scene()
	{
	}
	Scene::~Scene()
	{

	}

	void Scene::Initialize()
	{
		// 여기서 초기 게임 맵데이터를 세팅해줘야 한다.
		player = new Player;
		monster = new Monster;

		mGameObjects.push_back(player);
		mGameObjects.push_back(monster);
	}

	void Scene::Update()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Update();
		}

		if (player != nullptr && monster != nullptr)
		{
			Vector2 PlayerSize = Vector2(0.05 * player->GetPlayerInfo().scale.x, 0.1 * player->GetPlayerInfo().scale.y);
			Vector2 MonsterSize = Vector2(0.05 * monster->GetMonsterInfo().scale.x, 0.1 * monster->GetMonsterInfo().scale.y);

			float ce = fabs(player->GetPlayerInfo().pos.x - monster->GetMonsterInfo().pos.x);

			if (fabs(player->GetPlayerInfo().pos.x - monster->GetMonsterInfo().pos.x) < (PlayerSize.x + MonsterSize.x)
				&& fabs(player->GetPlayerInfo().pos.y - monster->GetMonsterInfo().pos.y) < (PlayerSize.y + MonsterSize.y))
			{
				player->SetPlayerScale(1.2f);


				std::vector<GameObject*>::iterator iter = mGameObjects.begin();
				std::vector<GameObject*>::iterator iter2 = iter + 1;

				mGameObjects.erase(iter2);
				delete monster;
				monster = nullptr;
			}
		}

		

	}

	void Scene::LateUpdate()
	{
	}
	void Scene::Render()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Render();
		}
	}
}