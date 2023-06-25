#include "jwScene.h"

namespace jw
{
	Scene::Scene()
	{
		mLayers.resize((int)jw::enums::eLayerType::End);
	}
	Scene::~Scene()
	{

	}

	void Scene::Initialize()
	{

	}

	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}

	void Scene::LateUpdate()
	{
		for (Layer& layer : mLayers)
		{
			layer.LateUpdate();
		}
	}
	void Scene::Render()
	{
		for (Layer& layer : mLayers)
		{
			layer.Render();
		}
	}
	void Scene::OnEnter()
	{
	}
	void Scene::OnExit()
	{
	}
	void Scene::SceneText(HDC hdc)
	{
		std::wstring tmp = Scene::GetName();
		TextOut(hdc, 0, 0, tmp.c_str(), tmp.size());
	}
	void Scene::AddGameObject(eLayerType type, GameObject* gameObj)
	{
		mLayers[(int)type].AddGameObject(gameObj);
	}
}
