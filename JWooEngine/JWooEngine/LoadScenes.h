#pragma once
#include "..\Engine_SOURCE\jwSceneManager.h"
#include "jwPlayScene.h"
#include "jwTitleScene.h"
#include "jwFactoryScene_00.h"
#include "jwFactoryScene_01.h"
#include "jwFactoryScene_02.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\JWooEngine.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\JWooEngine.lib")
#endif

namespace jw
{
	void InitializeScenes()
	{
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<FactoryScene_00>(L"FactoryScene_00");
		SceneManager::CreateScene<FactoryScene_01>(L"FactoryScene_01");
		SceneManager::CreateScene<FactoryScene_02>(L"FactoryScene_02");

		SceneManager::SetActiveScene(L"PlayScene");
	}
}