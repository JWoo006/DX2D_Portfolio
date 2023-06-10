#pragma once
#include "jwGameObject.h"
#include "jwInput.h"
#include "jwRenderer.h"

namespace jw
{
	using namespace renderer;
	class Player : public GameObject
	{
	public:
		Player();
		~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		Info GetPlayerInfo() { return mPlayerInfo; }
		void SetPlayerInfo( Info info ) { mPlayerInfo = info; }
		void SetPlayerScale(float scale) { mPlayerInfo.scale *= scale; }

	private:
		Info mPlayerInfo;
	};

}


