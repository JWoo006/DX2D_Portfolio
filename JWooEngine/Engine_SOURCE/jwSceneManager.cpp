#include "jwSceneManager.h"

#include "jwPlayScene.h"
#include "jwTitleScene.h"
#include "jwFactoryScene_00.h"
#include "jwFactoryScene_01.h"
#include "jwFactoryScene_02.h"

namespace jw
{
	Scene* SceneManager::mActiveScene = nullptr;
	std::map<std::wstring, Scene*> SceneManager::mScenes;

	void SceneManager::Initialize()
	{
		//mActiveScene = new PlayScene();
		//mScenes.insert(std::make_pair(L"PlayScene", mActiveScene));

		mActiveScene = new TitleScene();
		std::wstring a = mActiveScene->GetName();
		mScenes.insert(std::make_pair(mActiveScene->GetName(), mActiveScene));
		
		Scene* mTempScene = new FactoryScene_00();
		mScenes.insert(std::make_pair(mTempScene->GetName(), mTempScene));
		//mActiveScene = mTempScene;

		mTempScene = new FactoryScene_01();
		mScenes.insert(std::make_pair(mTempScene->GetName(), mTempScene));

		mTempScene = new FactoryScene_02();
		mScenes.insert(std::make_pair(mTempScene->GetName(), mTempScene));
		//mActiveScene = mTempScene;

		mActiveScene->Initialize();
	}
	void SceneManager::Update()
	{
		mActiveScene->Update();
	}
	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
	}
	void SceneManager::Render()
	{
		mActiveScene->Render();
	}
	void SceneManager::Release()
	{
		for (auto iter : mScenes)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	Scene* SceneManager::LoadScene(std::wstring name)
	{
		std::map<std::wstring, Scene*>::iterator iter
			= mScenes.find(name);

		if (iter == mScenes.end())
			return nullptr;

		mActiveScene->OnExit();
		mActiveScene = iter->second;
		mActiveScene->OnEnter();

		return iter->second;
	}
}
