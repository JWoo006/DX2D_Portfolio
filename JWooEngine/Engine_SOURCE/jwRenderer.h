#pragma once
#include "JWooEngine.h"
#include "jwGraphicDevice_Dx11.h"

using namespace jw::math;

namespace jw::renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};

	extern Vertex vertexes[];
	extern ID3D11InputLayout* triangleLayout;
	extern ID3D11Buffer* triangleBuffer;
	extern ID3DBlob* errorBlob;
	extern ID3DBlob* triangleVSBlob;
	extern ID3D11VertexShader* triangleVSShader;
	extern ID3DBlob* trianglePSBlob;
	extern ID3D11PixelShader* trianglePSShader;


	// 사각형 1
	extern Vertex squareVertexes[];
	extern ID3D11InputLayout* squareLayout;
	extern ID3D11Buffer* squareBuffer;
	extern ID3DBlob* squareVSBlob;
	extern ID3D11VertexShader* squareVSShader;
	extern ID3DBlob* squarePSBlob;
	extern ID3D11PixelShader* squarePSShader;

	// 사각형 2
	extern Vertex squareVertexes2[];
	extern WORD squreIndices[];
	extern ID3D11Buffer* indexBuffer;
	extern ID3D11InputLayout* squareLayout2;
	extern ID3D11Buffer* squareBuffer2;
	extern ID3DBlob* squareVSBlob2;
	extern ID3D11VertexShader* squareVSShader2;
	extern ID3DBlob* squarePSBlob2;
	extern ID3D11PixelShader* squarePSShader2;

	// 마름모
	extern Vertex diamondVertexes[];
	extern ID3D11InputLayout* diamondLayout;
	extern ID3D11Buffer* diamondBuffer;
	extern ID3DBlob* diamondVSBlob;
	extern ID3D11VertexShader* diamondVSShader;
	extern ID3DBlob* diamondPSBlob;
	extern ID3D11PixelShader* diamondPSShader;

	//원
	extern ID3D11InputLayout* circleLayout;
	extern ID3D11Buffer* circleBuffer;
	extern ID3DBlob* circleerrorBlob;
	extern ID3DBlob* circleVSBlob;
	extern ID3D11VertexShader* circleVSShader;
	extern ID3DBlob* circlePSBlob;
	extern ID3D11PixelShader* circlePSShader;

	void Initialize();
}

