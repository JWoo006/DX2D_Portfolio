#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Enemy : public GameObject
	{
	public:
		Enemy();
		~Enemy();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void CreateRay();

	private:
	};

}

