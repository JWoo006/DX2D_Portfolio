#pragma once
#include "jwGameObject.h"
#include "jwMeshRenderer.h"
#include "jwTransform.h"
#include "jwMath.h"

namespace jw
{
	using namespace jw::math;
	class MouseCursor : public GameObject
	{
	public:
		MouseCursor();
		~MouseCursor();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		static __forceinline Vector3 GetCursorPos() { return mCursorPos; }
		static __forceinline Vector3 GetCursorWorldPos() { return mCursorWorldPos; }
	private:
		MeshRenderer* mr;
		Transform* tr;
		Vector2 mTextureRatio;
		static Vector3 mCursorPos;
		static Vector3 mCursorEndPos;
		static Vector3 mCursorWorldPos;
	};
}
