#pragma once
#include "..\Engine_SOURCE\jwSceneManager.h"
#include "jwPlayScene.h"
#include "jwTestScene.h"

#include "jwTitleScene.h"
#include "jwFactoryScene_00.h"
#include "jwFactoryScene_01.h"
#include "jwFactoryScene_02.h"
#include "jwFactoryScene_03.h"
#include "jwFactoryScene_03_2.h"

#include "jwStudioScene_00.h"
#include "jwStudioScene_Boss.h"

#include "jwBunkerScene_00.h"
#include "jwBunkerScene_Boss.h"

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
		SceneManager::CreateScene<TestScene>(L"TestScene");

		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<FactoryScene_00>(L"FactoryScene_00");
		SceneManager::CreateScene<FactoryScene_01>(L"FactoryScene_01");
		SceneManager::CreateScene<FactoryScene_02>(L"FactoryScene_02");
		SceneManager::CreateScene<FactoryScene_03>(L"FactoryScene_03");
		SceneManager::CreateScene<FactoryScene_03_2>(L"FactoryScene_03_2");

		SceneManager::CreateScene<StudioScene_00>(L"StudioScene_00");
		SceneManager::CreateScene<StudioScene_Boss>(L"StudioScene_Boss");

		SceneManager::CreateScene<BunkerScene_00>(L"BunkerScene_00");
		SceneManager::CreateScene<BunkerScene_Boss>(L"BunkerScene_Boss");

		//SceneManager::SetActiveScene(L"StudioScene_00");
		
		SceneManager::SetActiveScene(L"PlayScene");

		//SceneManager::SetActiveScene(L"TestScene");
	}
}