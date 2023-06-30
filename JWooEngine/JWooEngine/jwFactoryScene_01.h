#pragma once
#include "..\Engine_SOURCE\jwScene.h"

namespace jw
{
	class FactoryScene_01 : public Scene
	{
	public:
		FactoryScene_01();
		virtual ~FactoryScene_01();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
