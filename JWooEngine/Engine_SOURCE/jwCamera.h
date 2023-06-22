#pragma once
#include "jwComponent.h"
#include "jwGraphics.h"

namespace jw
{
	class Camera : public Component
	{
	public:
		Camera();
		~Camera();

	private:
		static Matrix mView;
		static Matrix mProjection;
	};
}
