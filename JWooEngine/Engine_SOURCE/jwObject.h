#pragma once
#include "jwLayer.h"
#include "jwGameObject.h"
#include "jwScene.h"
#include "jwSceneManager.h"
#include "jwTransform.h"


namespace jw::object
{
	template <typename T>
	static __forceinline T* Instantiate(enums::eLayerType layer)
	{
		T* gameObj = new T();

		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, gameObj);

		return gameObj;
	}

	template <typename T>
	static __forceinline T* Instantiate(enums::eLayerType layer, Vector3 pos)
	{
		T* gameObj = new T();
		Transform* tr = gameObj->GetComponent<Transform>();
		tr->SetPosition(pos);

		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, gameObj);
		gameObj->Initialize();

		return gameObj;
	}

	template <typename T>
	static __forceinline T* Instantiate(enums::eLayerType layer, Vector3 pos, auto init)
	{
		T* gameObj = new T(init);
		Transform* tr = gameObj->GetComponent<Transform>();
		tr->SetPosition(pos);

		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, gameObj);
		gameObj->Initialize();

		return gameObj;
	}

	template <typename T>
	static __forceinline T* Instantiate(enums::eLayerType layer, Vector3 pos, Vector3 rotate)
	{
		T* gameObj = new T();
		Transform* tr = gameObj->GetComponent<Transform>();
		tr->SetPosition(pos);
		tr->SetRotation(rotate);

		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, gameObj);

		return gameObj;
	}

	template <typename T>
	static __forceinline T* Instantiate(enums::eLayerType layer, Vector3 pos, Vector3 rotate, Vector3 scale)
	{
		T* gameObj = new T();
		Transform* tr = gameObj->GetComponent<Transform>();
		tr->SetPosition(pos);
		tr->SetRotation(rotate);
		tr->SetScale(scale);

		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, gameObj);

		return gameObj;
	}

	static __forceinline void Destroy(GameObject* gameObj)
	{
		gameObj->SetState(jw::GameObject::eState::Dead);
	}
}