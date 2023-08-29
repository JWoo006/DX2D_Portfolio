#pragma once
#include "jwGameObject.h"

namespace jw
{
	class Grunt : public GameObject
	{
	public:
		Grunt();
		~Grunt();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
	};

}

