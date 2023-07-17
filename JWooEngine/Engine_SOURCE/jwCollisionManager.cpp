#include "jwCollisionManager.h"
#include "jwGameObject.h"
#include "jwScene.h"
#include "jwSceneManager.h"
#include "jwLayer.h"
#include "jwCollider2D.h"

#include "jwRenderer.h"
#include "jwConstantBuffer.h"
#include "jwGraphicDevice_Dx11.h"

namespace jw
{
	std::bitset<LAYER_MAX> CollisionManager::mMatrix[LAYER_MAX] = {};
	std::map<UINT64, bool> CollisionManager::mCollisionMap = {};

	void CollisionManager::Initialize()
	{
	}

	void CollisionManager::Update()
	{
		for (UINT column = 0; column < (UINT)eLayerType::End; column++)
		{
			for (UINT row = 0; row < (UINT)eLayerType::End; row++)
			{
				if (mMatrix[column][row] == true)
				{
					LayerCollision((eLayerType)column, (eLayerType)row);
				}
			}
		}
	}

	void CollisionManager::LayerCollision(eLayerType left, eLayerType right)
	{
		Scene* activeScene = SceneManager::GetActiveScene();

		const std::vector<GameObject*>& lefts
			= activeScene->GetLayer(left).GetGameObjects();
		const std::vector<GameObject*>& rights
			= activeScene->GetLayer(right).GetGameObjects();

		for (GameObject* leftObj : lefts)
		{
			Collider2D* leftCol = leftObj->GetComponent<Collider2D>();
			if (leftCol == nullptr)
				continue;
			if (leftObj->GetState()
				!= GameObject::eState::Active)
				continue;

			for (GameObject* rightObj : rights)
			{
				Collider2D* rightCol = rightObj->GetComponent<Collider2D>();
				if (rightCol == nullptr)
					continue;
				if (leftObj == rightObj)
					continue;
				if (rightObj->GetState()
					!= GameObject::eState::Active)
					continue;

				ColliderCollision(leftCol, rightCol);
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider2D* left, Collider2D* right)
	{
		// �� �浹ü�� ID bool���� Ȯ��
		ColliderID id = {};
		id.left = left->GetColliderID();
		id.right = right->GetColliderID();

		// �浹������ �����´�
		std::map<UINT64, bool>::iterator iter
			= mCollisionMap.find(id.id);

		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(id.id, false));
			iter = mCollisionMap.find(id.id);
		}

		if (Intersect(left, right))
		{
			// �浹
			if (iter->second == false)
			{
				//���� �浹
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
				iter->second = true;

				XMFLOAT4 colorBufferData;
				colorBufferData = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
				jw::graphics::GetDevice();

				ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Color];
				cb->SetData(&colorBufferData);
				cb->Bind(eShaderStage::PS);
			}
			else
			{
				// �浹 ��
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else
		{
			// �浹 X
			if (iter->second == true)
			{
				// �浹�ϰ� �ִٰ� ������
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
				iter->second = false;
			}
		}
	}

	bool CollisionManager::Intersect(Collider2D* left, Collider2D* right)
	{
		// �׸� �׸� �浹
		// �и��� �̷�
		
		Vector3 LeftColPos = left->GetPosition();
		Vector3 RightColPos = right->GetPosition();

		Vector3 tempaxes = LeftColPos - RightColPos;

		Vector3 LeftColUp = left->GetOwner()->GetComponent<Transform>()->Up();
		Vector3 LeftColRight = left->GetOwner()->GetComponent<Transform>()->Right();
		Vector3 RightColUp = right->GetOwner()->GetComponent<Transform>()->Up();
		Vector3 RightColRight = right->GetOwner()->GetComponent<Transform>()->Right();

		std::vector<Vector3> axes;
		axes.push_back(LeftColUp);
		axes.push_back(LeftColRight);
		axes.push_back(RightColUp);
		axes.push_back(RightColRight);

		for (const auto& axis : axes)
		{
			float Distance = abs(tempaxes.Dot(axis));

			if (Distance > abs((LeftColUp * left->GetScale().y * 0.5f).Dot(axis))
				+ abs((LeftColRight * left->GetScale().x * 0.5f).Dot(axis))
				+ abs((RightColUp * left->GetScale().y * 0.5f).Dot(axis))
				+ abs((RightColRight * left->GetScale().x * 0.5f).Dot(axis)))

				return false;
		}
		// To do... (����)
		// �и����� ��ƴ� �Ͻôºе���
		// �� - �� �浹

		return true;
	}

	void CollisionManager::SetLayer(eLayerType left, eLayerType right, bool enable)
	{
		UINT row = -1;
		UINT col = -1;

		UINT iLeft = (UINT)left;
		UINT iRight = (UINT)right;

		if (iLeft <= iRight)
		{
			row = iLeft;
			col = iRight;
		}
		else
		{
			row = iRight;
			col = iLeft;
		}

		mMatrix[col][row] = enable;
	}

	void CollisionManager::Clear()
	{
		mMatrix->reset();
		mCollisionMap.clear();
	}
	
}
