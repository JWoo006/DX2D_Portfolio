#pragma once
#include "jwScene.h"

namespace jw
{
	class FactoryScene_02 : public Scene
	{
	public:
		FactoryScene_02();
		virtual ~FactoryScene_02();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
