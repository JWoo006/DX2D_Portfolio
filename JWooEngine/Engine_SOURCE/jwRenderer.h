#pragma once
#include "JWooEngine.h"
#include "jwGraphicDevice_Dx11.h"
#include "jwMesh.h"
#include "jwShader.h"
#include "jwConstantBuffer.h"
#include "jwCamera.h"

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

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix mWorld;
		Matrix mView;
		Matrix mProjection;
	};

	CBUFFER(GridCB, CBSLOT_GRID)
	{
		Vector4 CameraPosition;
		Vector2 CameraScale;
		Vector2 Resolution;
	};

	CBUFFER(ColliderCB, CBSLOT_OVERLAP)
	{
		bool isOverlap;
	};

	CBUFFER(AnimatorCB, CBSLOT_ANIMATION2D)
	{
		Vector2 spriteLeftTop;
		Vector2 spriteSize;
		Vector2 spriteOffset;
		Vector2 atlasSize;
		UINT animationType;
	};

	extern jw::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End];

	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	extern jw::Camera* mainCamera;
	extern std::vector<jw::Camera*> cameras;
	extern std::vector<DebugMesh> debugMeshs;

	void Initialize();
	void Render();
	void Release();

	void PushDebugMeshAttribute(DebugMesh mesh);
}