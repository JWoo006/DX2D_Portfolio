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
		mGameObjects.push_back(player);

		//monster = new Monster;
		//mGameObjects.push_back(monster);

		for (int i = 0; i < 20; i++)
		{
			Monster* monsters = new Monster;
			mGameObjects.push_back(monsters);
		}

		//GameObject::eState state = player->GetState();
		//GameObject::eState state2 = monster->GetState();
	}

	void Scene::Update()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Update();
		}

		std::vector<GameObject*>::iterator Playeriter = mGameObjects.begin();
		std::vector<GameObject*>::iterator Monsteriter = Playeriter + 1;

		for (; Monsteriter != mGameObjects.end(); )
		{
			Vector2 PlayerSize = Vector2(0.05 * player->GetPlayerInfo().scale.x, 0.1 * player->GetPlayerInfo().scale.y);
			Vector2 MonsterSize = Vector2(0.05 * ((*Monsteriter)->GetInfo().scale.x), 0.1 * ((*Monsteriter)->GetInfo().scale.y));

			float ce = fabs(player->GetPlayerInfo().pos.x - (*Monsteriter)->GetInfo().pos.x);

			if (fabs(player->GetPlayerInfo().pos.x - (*Monsteriter)->GetInfo().pos.x) < (PlayerSize.x + MonsterSize.x)
				&& fabs(player->GetPlayerInfo().pos.y - (*Monsteriter)->GetInfo().pos.y) < (PlayerSize.y + MonsterSize.y))
			{
				player->SetPlayerScale(1.2f);

				(*Monsteriter)->SetState(GameObject::Dead);
				Monsteriter++;
			}
			else
			{
				Monsteriter++;
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

		std::vector<GameObject*> deleteGameObjects = {};

		for (std::vector<GameObject*>::iterator iter = mGameObjects.begin(); iter != mGameObjects.end(); )
		{
			if ((*iter)->GetState() == GameObject::Dead)
			{
				deleteGameObjects.push_back((*iter));

				iter = mGameObjects.erase(iter);
			}
			else
			{
				iter++;
			}
		}

		for (GameObject* deathObj : deleteGameObjects)
		{
			delete deathObj;
			deathObj = nullptr;
		}

	}
}