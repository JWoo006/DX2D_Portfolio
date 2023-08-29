#pragma once
//#include "jwScene.h"
#include "..\Engine_SOURCE\jwScene.h"

namespace jw
{
	class TestScene : public Scene
	{
	public:
		TestScene();
		virtual ~TestScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		class Player* mplayer;
	};
}

