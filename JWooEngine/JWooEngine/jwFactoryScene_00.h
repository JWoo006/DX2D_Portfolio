#pragma once
#include "..\Engine_SOURCE\jwScene.h"

namespace jw
{
	class FactoryScene_00 : public Scene
	{
	public:
		FactoryScene_00();
		virtual ~FactoryScene_00();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
