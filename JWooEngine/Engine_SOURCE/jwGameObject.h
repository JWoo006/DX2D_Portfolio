#pragma once
#include "jwEntity.h"
#include "jwComponent.h"
#include "jwRenderer.h"

namespace jw
{
	using namespace renderer;
	class GameObject : public Entity
	{
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};

		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		eState GetState() { return mState; }
		void SetState(eState state) { mState = state; }

		Info GetInfo() { return mInfo; }
		void SetInfo(Info info) { mInfo = info; }

	private:
		eState mState;
		Info mInfo;

		//std::vector<Component*> mComponents;
	};

}


