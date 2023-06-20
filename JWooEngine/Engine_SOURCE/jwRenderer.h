#pragma once
#include "JWooEngine.h"
#include "jwGraphicDevice_Dx11.h"
#include "jwMesh.h"
#include "jwShader.h"
#include "jwConstantBuffer.h"

using namespace jw::math;
using namespace jw::graphics;
namespace renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
		Vector2 uv;
	};

	extern Vertex vertexes[];
	extern Vector4 pos;
	extern jw::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End];

	void Initialize();
	void Release();
}