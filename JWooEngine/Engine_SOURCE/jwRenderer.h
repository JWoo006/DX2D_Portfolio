#pragma once
#include "JWooEngine.h"
#include "jwGraphicDevice_Dx11.h"
#include "jwMesh.h"
#include "jwShader.h"
#include "jwConstantBuffer.h"

using namespace jw::math;

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
	extern jw::Mesh* mesh;
	extern jw::Shader* shader;
	extern jw::graphics::ConstantBuffer* constantBuffer;

	void Initialize();
	void Release();
}