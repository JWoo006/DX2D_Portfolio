#pragma once
#include "..\Engine_SOURCE\jwScene.h"

namespace jw
{
	class StudioScene_Boss : public Scene
	{
	public:
		StudioScene_Boss();
		virtual ~StudioScene_Boss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}

