#include "jwTitleScene.h"
#include "jwTransform.h"
#include "jwMeshRenderer.h"
#include "jwResources.h"
#include "jwMesh.h"
#include "jwCameraScript.h"
#include "jwCamera.h"
#include "jwInput.h"
#include "jwSceneManager.h"

#include "jwApplication.h"

extern jw::Application application;

namespace jw
{
	TitleScene::TitleScene()
	{
		SetName(L"TitleScene");
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		{
			GameObject* player = new GameObject();
			AddGameObject(eLayerType::Player, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_Title_Temp"));
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			player->GetComponent<Transform>()->SetScale(Vector3(8.0f, 8.0f, 1.0f));
		}
		

		//Main Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
		}

		//UI Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::Player, false);
		}

	}

	void TitleScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(L"FactoryScene_00");
		}
	}

	void TitleScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void TitleScene::Render()
	{
		Scene::Render();
	}
}