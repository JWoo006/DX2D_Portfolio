#pragma once
#include "..\Engine_SOURCE\jwScene.h"

namespace jw
{
	class BunkerScene_00 : public Scene
	{
	public:
		BunkerScene_00();
		virtual ~BunkerScene_00();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
