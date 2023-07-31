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
		Scene* scene = SceneManager::GetActiveScene();

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::UI, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);

		// player
		{
			Player* player =object::Instantiate<Player>(Vector3(0.0f, 2.0f, 1.001f), eLayerType::Player);

			Collider2D* cd = player->AddComponent<Collider2D>();
			Rigidbody* rb = player->AddComponent<Rigidbody>();
			rb->SetMass(1.0f);
		
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

			Animator* at = player->AddComponent<Animator>();

			const float pi = 3.141592f;
			float degree = pi / 8.0f;

			
			
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
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.001f), eLayerType::Ground);

			ground->SetName(L"GroundCollider");

			Collider2D* cd = ground->AddComponent<Collider2D>();
			cd->SetSize(Vector2(8.f, 0.5f));
			Transform* tr = ground->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, -2.0f, 1.001f));
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