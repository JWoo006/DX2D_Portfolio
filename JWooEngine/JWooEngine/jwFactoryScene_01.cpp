#include "jwFactoryScene_01.h"
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
	FactoryScene_01::FactoryScene_01()
	{
		SetName(L"FactoryScene_01");

		//UI
		{
			// hud_base
			{
				GameObject* UI_Obj = new GameObject();
				AddGameObject(eLayerType::UI, UI_Obj);
				MeshRenderer* mr = UI_Obj->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_spr_hud_0"));
				UI_Obj->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 2.1f, -0.001f));
				UI_Obj->GetComponent<Transform>()->SetScale(Vector3(8.0f, 0.3f, 1.0f));
			}
			// hud_battery
			{
				GameObject* UI_Obj = new GameObject();
				AddGameObject(eLayerType::UI, UI_Obj);
				MeshRenderer* mr = UI_Obj->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_spr_hud_battery_0"));
				UI_Obj->GetComponent<Transform>()->SetPosition(Vector3(-3.5f, 2.1f, -0.002f));
				UI_Obj->GetComponent<Transform>()->SetScale(Vector3(1.0f, 0.25f, 1.0f));
			}
			//keyboard_shift
			{
				GameObject* UI_Obj = new GameObject();
				AddGameObject(eLayerType::UI, UI_Obj);
				MeshRenderer* mr = UI_Obj->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_spr_keyboard_shift_0"));
				UI_Obj->GetComponent<Transform>()->SetPosition(Vector3(-2.8f, 2.1f, -0.003f));
				UI_Obj->GetComponent<Transform>()->SetScale(Vector3(0.4f, 0.2f, 1.0f));
			}
			// hud_timer
			{
				GameObject* UI_Obj = new GameObject();
				AddGameObject(eLayerType::UI, UI_Obj);
				MeshRenderer* mr = UI_Obj->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_spr_hud_timer_0"));
				UI_Obj->GetComponent<Transform>()->SetPosition(Vector3(-0.05f, 2.1f, -0.004f));
				UI_Obj->GetComponent<Transform>()->SetScale(Vector3(1.4f, 0.23f, 1.0f));
			}
			{
				GameObject* UI_Obj = new GameObject();
				AddGameObject(eLayerType::UI, UI_Obj);
				MeshRenderer* mr = UI_Obj->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_spr_timer_0"));
				UI_Obj->GetComponent<Transform>()->SetPosition(Vector3(0.04f, 2.125f, -0.005f));
				UI_Obj->GetComponent<Transform>()->SetScale(Vector3(1.2f, 0.125f, 1.0f));
			}

			//hud_subweapon
			{
				// base_hud
				{
					GameObject* UI_Obj = new GameObject();
					AddGameObject(eLayerType::UI, UI_Obj);
					MeshRenderer* mr = UI_Obj->AddComponent<MeshRenderer>();
					mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
					mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_spr_hud_subweapon_0"));
					UI_Obj->GetComponent<Transform>()->SetPosition(Vector3(3.55f, 2.1f, -0.006f));
					UI_Obj->GetComponent<Transform>()->SetScale(Vector3(0.7f, 0.3f, 1.0f));
				}
				// katana
				{
					GameObject* UI_Obj = new GameObject();
					AddGameObject(eLayerType::UI, UI_Obj);
					MeshRenderer* mr = UI_Obj->AddComponent<MeshRenderer>();
					mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
					mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_spr_katana_pickup_0"));
					UI_Obj->GetComponent<Transform>()->SetPosition(Vector3(3.35f, 2.1f, -0.0065f));
					UI_Obj->GetComponent<Transform>()->SetScale(Vector3(0.3f, 0.3f, 1.0f));
				}

				// left_click
				{
					GameObject* UI_Obj = new GameObject();
					AddGameObject(eLayerType::UI, UI_Obj);
					MeshRenderer* mr = UI_Obj->AddComponent<MeshRenderer>();
					mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
					mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_spr_left_click_1"));
					UI_Obj->GetComponent<Transform>()->SetPosition(Vector3(3.45f, 1.95f, -0.007f));
					UI_Obj->GetComponent<Transform>()->SetScale(Vector3(0.16f, 0.22f, 1.0f));
				}

				// right_click
				{
					GameObject* UI_Obj = new GameObject();
					AddGameObject(eLayerType::UI, UI_Obj);
					MeshRenderer* mr = UI_Obj->AddComponent<MeshRenderer>();
					mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
					mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_spr_right_click_1"));
					UI_Obj->GetComponent<Transform>()->SetPosition(Vector3(3.85f, 1.95f, -0.008f));
					UI_Obj->GetComponent<Transform>()->SetScale(Vector3(0.16f, 0.22f, 1.0f));
				}
			}
		}


		{
			GameObject* player = new GameObject();
			AddGameObject(eLayerType::Player, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_Room_Factory_1"));
			//mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_room_factory_1_1111"));
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			player->GetComponent<Transform>()->SetScale(Vector3(10.0f, 4.5f, 1.0f));
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
	FactoryScene_01::~FactoryScene_01()
	{
	}
	void FactoryScene_01::Initialize()
	{
		

	}

	void FactoryScene_01::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(L"FactoryScene_02");
		}
	}

	void FactoryScene_01::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void FactoryScene_01::Render()
	{
		Scene::Render();
	}
}