#pragma once
#include "..\Engine_SOURCE\jwScene.h"

namespace jw
{
	class FactoryScene_03_2 : public Scene
	{
	public:
		FactoryScene_03_2();
		virtual ~FactoryScene_03_2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
