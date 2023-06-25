#include "jwFactoryScene_00.h"
#include "jwTransform.h"
#include "jwMeshRenderer.h"
#include "jwResources.h"
#include "jwMesh.h"
#include "jwCameraScript.h"
#include "jwCamera.h"
#include "jwInput.h"
#include "jwSceneManager.h"

namespace jw
{
	FactoryScene_00::FactoryScene_00()
	{
		SetName(L"FactoryScene_00");

		{
			GameObject* player = new GameObject();
			AddGameObject(eLayerType::Player, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_Room_Factory_0"));
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			player->GetComponent<Transform>()->SetScale(Vector3(32.0f, 4.5f, 1.0f));
		}

		//Main Camera
		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::Player, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(-11.0f, 0.f, -10.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();
	}
	FactoryScene_00::~FactoryScene_00()
	{
	}
	void FactoryScene_00::Initialize()
	{

		

	}

	void FactoryScene_00::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(L"FactoryScene_01");
		}
	}

	void FactoryScene_00::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void FactoryScene_00::Render()
	{
		Scene::Render();
	}
}