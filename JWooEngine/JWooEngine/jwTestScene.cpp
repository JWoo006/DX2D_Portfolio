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

		// player
		{
			Player* player =object::Instantiate<Player>(eLayerType::Player, Vector3(0.0f, 2.0f, 1.001f));

			Collider2D* cd = player->AddComponent<Collider2D>();
			Rigidbody* rb = player->AddComponent<Rigidbody>();
			rb->SetMass(1.0f);
		
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

			Animator* at = player->AddComponent<Animator>();
			
			player->AddComponent<PlayerScript>();
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

			ground->SetName(L"GroundCollider");

			Collider2D* cd = ground->AddComponent<Collider2D>();
			cd->SetSize(Vector2(8.f, 0.5f));
			Transform* tr = ground->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, -2.0f, 1.001f));
			ground->AddComponent<GroundScript>();
		}

		{
			GameObject* ground
				= object::Instantiate<GameObject>(eLayerType::Ground, Vector3(0.0f, 0.0f, 1.001f));

			ground->SetName(L"GroundCollider2");
			

			Collider2D* cd = ground->AddComponent<Collider2D>();
			cd->SetSize(Vector2(8.f, 0.5f));
			Transform* tr = ground->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, -2.0f, 1.001f));
			ground->AddComponent<GroundScript>();
			ground->SetRotation(Vector3(0.0f, 0.0f, RotateDegree(45)));
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
			renderer::cameras.push_back(cameraComp);
			renderer::mainCamera = cameraComp;
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