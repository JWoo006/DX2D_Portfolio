#pragma once
#include "jwComponent.h"
#include "jwTransform.h"

namespace jw
{
	class Collider2D : public Component
	{
	public:
		Collider2D();
		~Collider2D();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void OnCollisionEnter(Collider2D* other);
		void OnCollisionStay(Collider2D* other);
		void OnCollisionExit(Collider2D* other);

		void SetType(eColliderType type) { mType = type; }
		void SetSize(Vector2 size) { mSize = size; }
		void SetCenter(Vector2 size) { mCenter = size; }

		UINT GetColliderID() { return mColliderID; }

		Vector3 GetPosition() { return mPosition; }
		Vector3 GetScale() { return mScale; }
		Vector2 GetSize() { return mSize; }

	private:
		static UINT mColliderNumber;
		UINT mColliderID;

		eColliderType mType;
		Transform* mTransform;

		Vector3 mPosition;
		Vector2 mSize;
		Vector2 mCenter;

		Vector3 mScale;

		bool misOverlap;
	};
}
