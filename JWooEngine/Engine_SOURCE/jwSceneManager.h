#pragma once
#include "jwScene.h"

namespace jw
{
	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();
		static void Destroy();
		static void Release();

		template <typename T>
		static bool CreateScene(std::wstring name)
		{
			T* scene = new T();

			std::map<std::wstring, Scene*>::iterator iter
				= mScenes.find(name);

			if (iter != mScenes.end())
				return false;

			mScenes.insert(std::make_pair(name, scene));
			mActiveScene = scene;
			scene->Initialize();
			return true;
		}
		static Scene* LoadScene(std::wstring name);
		static Scene* GetActiveScene() { return mActiveScene; }
		//static void SetActiveScene(Scene* ActiveScene) { mActiveScene = ActiveScene; }
		
		static void SetActiveScene(std::wstring name)
		{
			std::map<std::wstring, Scene*>::iterator iter
				= mScenes.find(name);

			if (iter != mScenes.end())
				

			mActiveScene = iter->second;
			
			
		}

	private:
		static Scene* mActiveScene;
		static std::map<std::wstring, Scene*> mScenes;
	};
}
