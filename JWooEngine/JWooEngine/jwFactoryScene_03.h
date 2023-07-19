#pragma once
#include "..\Engine_SOURCE\jwScene.h"

namespace jw
{
	class FactoryScene_03 : public Scene
	{
	public:
		FactoryScene_03();
		virtual ~FactoryScene_03();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
