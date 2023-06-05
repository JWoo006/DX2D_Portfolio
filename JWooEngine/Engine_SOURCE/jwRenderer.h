#pragma once
#include "JWooEngine.h"
#include "jwGraphicDevice_Dx11.h"
#include "jwMesh.h"
#include "jwShader.h"

using namespace jw::math;

namespace renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};

	extern Vertex vertexes[];
	extern Vector4 pos;
	extern ID3D11InputLayout* triangleLayout;
	extern jw::Mesh* mesh;
	extern ID3D11Buffer* triangleConstantBuffer;
	extern jw::Shader* shader;
	extern ID3D11PixelShader* trianglePSShader;

	void Initialize();
	void Release();
}