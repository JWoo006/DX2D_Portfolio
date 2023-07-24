#include "jwCollider2D.h"
#include "jwGameObject.h"
#include "jwRenderer.h"

namespace jw
{
	UINT Collider2D::mColliderNumber = 0;

	Collider2D::Collider2D()
		: Component(eComponentType::Collider2D)
		, mTransform(nullptr)
		, mSize(Vector2::One)
		, mCenter(Vector2::Zero)
		, misOverlap(false)
	{
		mColliderNumber++;
		mColliderID = mColliderNumber;
	}
	Collider2D::~Collider2D()
	{
	}
	void Collider2D::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
	}

	void Collider2D::Update()
	{
	}
	void Collider2D::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		mScale = tr->GetScale();
		mScale.x *= mSize.x;
		mScale.y *= mSize.y;

		Vector3 pos = tr->GetPosition();
		pos.x += mCenter.x;
		pos.y += mCenter.y;

		mPosition = pos;

		graphics::DebugMesh mesh = {};
		mesh.position = mPosition;
		mesh.scale = mScale;
		mesh.rotation = tr->GetRotation();
		mesh.type = eColliderType::Rect;
		mesh.isOverlap = misOverlap;

		renderer::PushDebugMeshAttribute(mesh);
	}
	void Collider2D::Render()
	{
	}

	void Collider2D::OnCollisionEnter(Collider2D* other)
	{
		misOverlap = true;

		const std::vector<Script*>& scripts
			= GetOwner()->GetComponents<Script>();

		for (Script* script : scripts)
		{
			script->OnCollisionEnter(other);
		}
	}
	void Collider2D::OnCollisionStay(Collider2D* other)
	{
		const std::vector<Script*>& scripts
			= GetOwner()->GetComponents<Script>();

		for (Script* script : scripts)
		{
			script->OnCollisionStay(other);
		}
	}
	void Collider2D::OnCollisionExit(Collider2D* other)
	{
		misOverlap = false;

		const std::vector<Script*>& scripts
			= GetOwner()->GetComponents<Script>();

		for (Script* script : scripts)
		{
			script->OnCollisionExit(other);
		}
	}
}