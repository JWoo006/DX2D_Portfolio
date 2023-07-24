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

#include "jwPlayerScript.h"
#include "jwCollisionManager.h"
#include "jwAnimator.h"

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
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Player, true);

		{
			GameObject* player
				= object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.001f), eLayerType::Player);

			player->SetName(L"PlayerZero");

			Collider2D* cd = player->AddComponent<Collider2D>();
		
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

			const float pi = 3.141592f;
			float degree = pi / 8.0f;

			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0001f));
			//player->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, degree));

			// idle 애니메이션 기준 collider, transform(scale)
			player->GetComponent<Transform>()->SetScale(Vector3(3.0f, 3.0f, 1.0f));
			cd->SetSize(Vector2(0.1f, 0.16f));
			cd->SetCenter(Vector2(0.f, -0.1f));

			std::shared_ptr<Texture> atlas
				= Resources::Load<Texture>(L"LinkSprite", L"..\\Resources\\Texture\\linkSprites.png");
			Animator* at = player->AddComponent<Animator>();
			
			player->AddComponent<PlayerScript>();
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