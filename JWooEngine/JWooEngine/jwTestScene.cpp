#include "jwTestScene.h"
#include "jwTransform.h"
#include "jwMeshRenderer.h"
#include "jwResources.h"
#include "jwMesh.h"
#include "jwCameraScript.h"
#include "jwCamera.h"
#include "jwGridScript.h"
#include "jwObject.h"
#include "jwRenderer.h"
#include "jwCollider2D.h"
#include "jwRigidbody.h"
#include "jwLight.h"

#include "jwPlayer.h"
#include "jwPlayerScript.h"
#include "jwCollisionManager.h"
#include "jwAnimator.h"

#include "jwGroundScript.h"
#include "jwMouseCursor.h"

#include "jwGrunt.h"
#include "jwGruntScript.h"

#include "jwAudioListener.h"
#include "jwAudioClip.h"
#include "jwAudioSource.h"

namespace jw
{
	TestScene::TestScene()
	{
	}
	TestScene::~TestScene()
	{
	}

	void TestScene::Initialize()
	{
		SetName(L"TestScene");
		
		

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::UI, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Effect, true);


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
		//bg
		{
			GameObject* player = new GameObject();
			AddGameObject(eLayerType::Player, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_Room_Factory_2"));
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.01f));
			player->GetComponent<Transform>()->SetScale(Vector3(10.0f, 4.5f, 1.0f));
		}


		// player
		{
			Player* player =object::Instantiate<Player>(eLayerType::Player, Vector3(0.0f, 11.0f, 1.001f));

			Collider2D* cd = player->AddComponent<Collider2D>();
			Rigidbody* rb = player->AddComponent<Rigidbody>();
			rb->SetMass(1.0f);
		
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

			Animator* at = player->AddComponent<Animator>();
			
			player->AddComponent<PlayerScript>();
			mplayer = player;
		}

		//grunt
		{
			Grunt* grunt = object::Instantiate<Grunt>(eLayerType::Monster, Vector3(-2.f, -1.45f, 1.001f));

			Collider2D* cd = grunt->AddComponent<Collider2D>();
			Rigidbody* rb = grunt->AddComponent<Rigidbody>();
			rb->SetMass(1.0f);
			MeshRenderer* mr = grunt->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
			Animator* at = grunt->AddComponent<Animator>();

			grunt->AddComponent<GruntScript>();
		}

		{
			Grunt* grunt = object::Instantiate<Grunt>(eLayerType::Monster, Vector3(-2.f, 7.5f, 1.001f));

			Collider2D* cd = grunt->AddComponent<Collider2D>();
			Rigidbody* rb = grunt->AddComponent<Rigidbody>();
			rb->SetMass(1.0f);
			MeshRenderer* mr = grunt->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
			Animator* at = grunt->AddComponent<Animator>();

			grunt->AddComponent<GruntScript>();
		}

		{
			Grunt* grunt = object::Instantiate<Grunt>(eLayerType::Monster, Vector3(2.f, 7.5f, 1.001f));

			Collider2D* cd = grunt->AddComponent<Collider2D>();
			Rigidbody* rb = grunt->AddComponent<Rigidbody>();
			rb->SetMass(1.0f);
			MeshRenderer* mr = grunt->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
			Animator* at = grunt->AddComponent<Animator>();

			grunt->AddComponent<GruntScript>();
		}
		
		// Mouse
		{
			//GameObject* Cursor = object::Instantiate<MouseCursor>(eLayerType::MouseCursor);
			//Collider2D* cd = Cursor->AddComponent<Collider2D>();
			//cd->Initialize();
			//cd->SetSize(Vector2(1.0f, 1.0f));
		}

		// ground
		{
			GameObject* ground
				= object::Instantiate<GameObject>(eLayerType::Ground, Vector3(0.0f, 0.0f, 1.001f));

			ground->SetName(L"GroundCol_Base");

			Collider2D* cd = ground->AddComponent<Collider2D>();
			cd->SetSize(Vector2(8.f, 0.5f));
			Transform* tr = ground->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, -1.9f, 1.001f));
			ground->AddComponent<GroundScript>();
		}
		{
			GameObject* ground
				= object::Instantiate<GameObject>(eLayerType::Ground, Vector3(0.0f, 0.0f, 1.001f));

			ground->SetName(L"GroundCol_Base");

			Collider2D* cd = ground->AddComponent<Collider2D>();
			cd->SetSize(Vector2(4.f, 0.1f));
			Transform* tr = ground->GetComponent<Transform>();
			tr->SetPosition(Vector3(-3.3f, 0.02f, 1.001f));
			ground->AddComponent<GroundScript>();
		}
		{
			GameObject* ground
				= object::Instantiate<GameObject>(eLayerType::Ground, Vector3(0.0f, 0.0f, 1.001f));

			ground->SetName(L"GroundCol_Base");

			Collider2D* cd = ground->AddComponent<Collider2D>();
			cd->SetSize(Vector2(4.f, 0.1f));
			Transform* tr = ground->GetComponent<Transform>();
			tr->SetPosition(Vector3(3.f, 0.02f, 1.001f));
			ground->AddComponent<GroundScript>();
		}

		{
			GameObject* ground
				= object::Instantiate<GameObject>(eLayerType::Ground, Vector3(0.0f, 0.0f, 1.001f));

			ground->SetName(L"GroundCol_Slope");
		
			Collider2D* cd = ground->AddComponent<Collider2D>();
			cd->SetSize(Vector2(3.f, 0.01f));
			Transform* tr = ground->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, -1.0f, 1.001f));
			ground->SetRotation(Vector3(0.0f, 0.0f, RotateDegree(45)));
			ground->AddComponent<GroundScript>();
		}

		
		{
			GameObject* ground
				= object::Instantiate<GameObject>(eLayerType::Ground, Vector3(0.0f, 0.0f, 1.001f));

			ground->SetName(L"GroundCol_Down");

			Collider2D* cd = ground->AddComponent<Collider2D>();
			cd->SetSize(Vector2(2.7f, 0.01f));
			Transform* tr = ground->GetComponent<Transform>();
			tr->SetPosition(Vector3(-0.3f, 0.078f, 1.001f));
			ground->AddComponent<GroundScript>();
		}

		//Light
		{
			GameObject* light = new GameObject();
			light->SetName(L"Light");
			AddGameObject(eLayerType::Light, light);
			Light* lightComp = light->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			lightComp->SetRadius(3.0f);
		}
		//Main Camera
		Camera* cameraComp = nullptr;
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
			camera->GetScript<CameraScript>()->SetPlayer(mplayer);
			renderer::cameras.push_back(cameraComp);
			renderer::mainCamera = cameraComp;

			camera->AddComponent<AudioListener>();
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

	void TestScene::Update()
	{
		Scene::Update();
	}

	void TestScene::LateUpdate()
	{
		
		Scene::LateUpdate();
	}

	void TestScene::Render()
	{
		Scene::Render();
	}

	void TestScene::OnEnter()
	{

	}

	void TestScene::OnExit()
	{
	}

}