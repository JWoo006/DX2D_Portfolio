#include "jwLayer.h"

namespace jw
{
	Layer::Layer()
	{
	}
	Layer::~Layer()
	{
	}
	void Layer::Initialize()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			delete gameObj;
			gameObj = nullptr;
		}
	}
	void Layer::Update()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Update();
		}
	}
	void Layer::LateUpdate()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->LateUpdate();
		}
	}
	void Layer::Render()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			//gameObj->LateUpdate();
			gameObj->Render();
		}
	}
	void Layer::AddGameObject(GameObject* gameObj)
	{
		mGameObjects.push_back(gameObj);
	}
}
