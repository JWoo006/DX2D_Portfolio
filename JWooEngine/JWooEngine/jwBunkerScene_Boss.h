#pragma once
#include "..\Engine_SOURCE\jwScene.h"

namespace jw
{
	class BunkerScene_Boss : public Scene
	{
	public:
		BunkerScene_Boss();
		virtual ~BunkerScene_Boss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}

