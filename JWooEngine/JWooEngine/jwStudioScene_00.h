#pragma once
#include "..\Engine_SOURCE\jwScene.h"

namespace jw
{
	class StudioScene_00 : public Scene
	{
	public:
		StudioScene_00();
		virtual ~StudioScene_00();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}


