#pragma once
//#include "jwScene.h"
#include "..\Engine_SOURCE\jwScene.h"

namespace jw
{
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		virtual ~PlayScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
