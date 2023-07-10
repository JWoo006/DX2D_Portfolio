#include "jwRenderer.h"

#include "jwResources.h"
#include "jwTexture.h"
#include "jwMaterial.h"

namespace renderer
{
	using namespace jw;
	using namespace jw::graphics;

	jw::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End] = {};

	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[(UINT)eSamplerType::End] = {};

	//
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};

	//
	std::vector<jw::Camera*> cameras = {};
	std::vector<DebugMesh> debugMeshs = {};

	void SetupState()
	{
#pragma region InputLayout
		// Input layout 정점 구조 정보를 넘겨줘야한다.
		D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {};

		arrLayout[0].AlignedByteOffset = 0;
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayout[0].InputSlot = 0;
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 12;
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		arrLayout[2].AlignedByteOffset = 28;
		arrLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayout[2].InputSlot = 0;
		arrLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[2].SemanticName = "TEXCOORD";
		arrLayout[2].SemanticIndex = 0;

		std::shared_ptr<Shader> shader = jw::Resources::Find<Shader>(L"TriangleShader");
		jw::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = jw::Resources::Find<Shader>(L"SpriteShader");
		jw::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = jw::Resources::Find<Shader>(L"GridShader");
		jw::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = jw::Resources::Find<Shader>(L"DebugShader");
		jw::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());


#pragma endregion
#pragma region Sampler State
		//Sampler State
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		GetDevice()->CreateSamplerState(&samplerDesc, samplerState[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 0, samplerState[(UINT)eSamplerType::Point].GetAddressOf());

		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSamplerState(&samplerDesc, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 1, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
#pragma endregion
#pragma region Rasterizer State
		D3D11_RASTERIZER_DESC rasterizerDesc = {};
		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizeState(&rasterizerDesc
			, rasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());
#pragma endregion
#pragma region Depth Stencil State
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};

		//less
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::Less].GetAddressOf());

		//Greater
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::Greater].GetAddressOf());

		//No Write
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

		//None
		depthStencilDesc.DepthEnable = false;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc
			, depthStencilStates[(UINT)eDSType::None].GetAddressOf());
#pragma endregion
#pragma region Blend State
		D3D11_BLEND_DESC blendDesc = {};

		//default
		blendStates[(UINT)eBSType::Default] = nullptr;

		// Alpha Blend
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&blendDesc
			, blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

		// one one
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;

		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		GetDevice()->CreateBlendState(&blendDesc
			, blendStates[(UINT)eBSType::OneOne].GetAddressOf());

#pragma endregion


	}

	void LoadMesh()
	{
		std::vector<Vertex> vertexes = {};
		std::vector<UINT> indexes = {};

		//RECT
		vertexes.resize(4);
		vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		// Vertex Buffer
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		Resources::Insert(L"RectMesh", mesh);

		mesh->CreateVertexBuffer(vertexes.data(), vertexes.size());

		// Index Buffer
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		mesh->CreateIndexBuffer(indexes.data(), indexes.size());

		// Rect Debug Mesh
		std::shared_ptr<Mesh> rectDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugRect", rectDebug);
		rectDebug->CreateVertexBuffer(vertexes.data(), vertexes.size());
		rectDebug->CreateIndexBuffer(indexes.data(), indexes.size());

		// Circle Debug Mesh
		vertexes.clear();
		indexes.clear();

		Vertex center = {};
		center.pos = Vector3(0.0f, 0.0f, 0.0f);
		center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes.push_back(center);

		int iSlice = 40;
		float fRadius = 0.5f;
		float fTheta = XM_2PI / (float)iSlice;

		for (int i = 0; i < iSlice; ++i)
		{
			center.pos = Vector3(fRadius * cosf(fTheta * (float)i)
				, fRadius * sinf(fTheta * (float)i)
				, 0.0f);
			center.color = Vector4(0.0f, 1.0f, 0.0f, 1.f);
			vertexes.push_back(center);
		}

		//for (UINT i = 0; i < (UINT)iSlice; ++i)
		//{
		//	indexes.push_back(0);
		//	if (i == iSlice - 1)
		//	{
		//		indexes.push_back(1);
		//	}
		//	else
		//	{
		//		indexes.push_back(i + 2);
		//	}
		//	indexes.push_back(i + 1);
		//}

		for (int i = 0; i < vertexes.size() - 2; ++i)
		{
			indexes.push_back(i + 1);
		}
		indexes.push_back(1);

		std::shared_ptr<Mesh> circleDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugCircle", circleDebug);
		circleDebug->CreateVertexBuffer(vertexes.data(), vertexes.size());
		circleDebug->CreateIndexBuffer(indexes.data(), indexes.size());

	}


	void LoadBuffer()
	{
		// Constant Buffer
		constantBuffer[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffer[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		// Grid Buffer
		constantBuffer[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffer[(UINT)eCBType::Grid]->Create(sizeof(TransformCB));
	}

	void LoadShader()
	{
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
		jw::Resources::Insert(L"TriangleShader", shader);

		std::shared_ptr<Shader> spriteShader = std::make_shared<Shader>();
		spriteShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		spriteShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		jw::Resources::Insert(L"SpriteShader", spriteShader);

		std::shared_ptr<Shader> girdShader = std::make_shared<Shader>();
		girdShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		girdShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		jw::Resources::Insert(L"GridShader", girdShader);

		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);
		debugShader->SetRSState(eRSType::SolidNone);
		//debugShader->SetDSState(eDSType::NoWrite);
		jw::Resources::Insert(L"DebugShader", debugShader);
	}

	void LoadMaterial()
	{
		// 마테리얼 추가
		std::shared_ptr<Shader> spriteShader
			= Resources::Find<Shader>(L"SpriteShader");

		std::shared_ptr<Texture> texture
			= Resources::Load<Texture>(L"Link", L"..\\Resources\\Texture\\Link.png");

		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		Resources::Insert(L"SpriteMaterial", material);

		texture = Resources::Load<Texture>(L"Smile", L"..\\Resources\\Texture\\Smile.png");
		material = std::make_shared<Material>();
		material->SetShader(spriteShader);
		material->SetTexture(texture);
		material->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"SpriteMaterial02", material);

		std::shared_ptr<Shader> gridShader
			= Resources::Find<Shader>(L"GridShader");

		material = std::make_shared<Material>();
		material->SetShader(gridShader);
		Resources::Insert(L"GridMaterial", material);

		std::shared_ptr<Shader> debugShader
			= Resources::Find<Shader>(L"DebugShader");

		material = std::make_shared<Material>();
		material->SetShader(debugShader);
		Resources::Insert(L"DebugMaterial", material);

		// UI
		{
			// hud_base
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"spr_hud_0", L"..\\Resources\\Texture\\UI\\spr_hud\\spr_hud_0.png");

				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"SpriteMaterial_spr_hud_0", spriteMateiral);
			}
			// battery_base
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"spr_hud_battery_0", L"..\\Resources\\Texture\\UI\\spr_hud_battery\\spr_hud_battery_0.png");

				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"SpriteMaterial_spr_hud_battery_0", spriteMateiral);
			}
			// spr_keyboard_shift
			{
				{
					std::shared_ptr<Texture> texture
						= Resources::Load<Texture>(L"spr_keyboard_shift_0", L"..\\Resources\\Texture\\UI\\keyboard\\spr_keyboard_shift\\spr_keyboard_shift_0.png");

					std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
					spriteMateiral->SetShader(spriteShader);
					spriteMateiral->SetTexture(texture);
					spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
					Resources::Insert(L"SpriteMaterial_spr_keyboard_shift_0", spriteMateiral);
				}
				{
					std::shared_ptr<Texture> texture
						= Resources::Load<Texture>(L"spr_keyboard_shift_1", L"..\\Resources\\Texture\\UI\\keyboard\\spr_keyboard_shift\\spr_keyboard_shift_1.png");

					std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
					spriteMateiral->SetShader(spriteShader);
					spriteMateiral->SetTexture(texture);
					spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
					Resources::Insert(L"SpriteMaterial_spr_keyboard_shift_1", spriteMateiral);
				}
			}
			// hud_timer
			{
				{
					std::shared_ptr<Texture> texture
						= Resources::Load<Texture>(L"spr_hud_timer_0", L"..\\Resources\\Texture\\UI\\spr_hud_timer\\spr_hud_timer_0.png");

					std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
					spriteMateiral->SetShader(spriteShader);
					spriteMateiral->SetTexture(texture);
					spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
					Resources::Insert(L"SpriteMaterial_spr_hud_timer_0", spriteMateiral);
				}
				{
					std::shared_ptr<Texture> texture
						= Resources::Load<Texture>(L"spr_hud_timer_1", L"..\\Resources\\Texture\\UI\\spr_hud_timer\\spr_hud_timer_1.png");

					std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
					spriteMateiral->SetShader(spriteShader);
					spriteMateiral->SetTexture(texture);
					spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
					Resources::Insert(L"SpriteMaterial_spr_hud_timer_1", spriteMateiral);
				}
				{
					std::shared_ptr<Texture> texture
						= Resources::Load<Texture>(L"spr_timer_0", L"..\\Resources\\Texture\\UI\\spr_timer\\spr_timer_0.png");

					std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
					spriteMateiral->SetShader(spriteShader);
					spriteMateiral->SetTexture(texture);
					spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
					Resources::Insert(L"SpriteMaterial_spr_timer_0", spriteMateiral);
				}
			}
			//hud_subweapon
			{
				// base_hud
				{
					std::shared_ptr<Texture> texture
						= Resources::Load<Texture>(L"spr_hud_subweapon_0", L"..\\Resources\\Texture\\UI\\spr_hud_subweapon\\spr_hud_subweapon_0.png");

					std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
					spriteMateiral->SetShader(spriteShader);
					spriteMateiral->SetTexture(texture);
					spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
					Resources::Insert(L"SpriteMaterial_spr_hud_subweapon_0", spriteMateiral);
				}
				// spr_katana_pickup
				{
					std::shared_ptr<Texture> texture
						= Resources::Load<Texture>(L"spr_katana_pickup_0", L"..\\Resources\\Texture\\UI\\spr_katana_pickup\\spr_katana_pickup_0.png");

					std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
					spriteMateiral->SetShader(spriteShader);
					spriteMateiral->SetTexture(texture);
					spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
					Resources::Insert(L"SpriteMaterial_spr_katana_pickup_0", spriteMateiral);
				}
			}
			//hud_Click
			{
				// click_base
				{
					std::shared_ptr<Texture> texture
						= Resources::Load<Texture>(L"spr_left_click_0", L"..\\Resources\\Texture\\UI\\spr_left_click\\spr_left_click_0.png");

					std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
					spriteMateiral->SetShader(spriteShader);
					spriteMateiral->SetTexture(texture);
					spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
					Resources::Insert(L"SpriteMaterial_spr_left_click_0", spriteMateiral);
				}
				// spr_left_click
				{
					std::shared_ptr<Texture> texture
						= Resources::Load<Texture>(L"spr_left_click_1", L"..\\Resources\\Texture\\UI\\spr_left_click\\spr_left_click_1.png");

					std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
					spriteMateiral->SetShader(spriteShader);
					spriteMateiral->SetTexture(texture);
					spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
					Resources::Insert(L"SpriteMaterial_spr_left_click_1", spriteMateiral);
				}
				// spr_right_click
				{
					std::shared_ptr<Texture> texture
						= Resources::Load<Texture>(L"spr_right_click_1", L"..\\Resources\\Texture\\UI\\spr_right_click\\spr_right_click_1.png");

					std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
					spriteMateiral->SetShader(spriteShader);
					spriteMateiral->SetTexture(texture);
					spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
					Resources::Insert(L"SpriteMaterial_spr_right_click_1", spriteMateiral);
				}
			}
		}

		// title
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"Title_Temp", L"..\\Resources\\Texture\\Title\\title_temp.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"SpriteMaterial_Title_Temp", spriteMateiral);
		}

		// Room_Factory
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"Room_Factory_0", L"..\\Resources\\Texture\\Room\\01_Factory\\room_factory_0.png");

				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"SpriteMaterial_Room_Factory_0", spriteMateiral);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"Room_Factory_1", L"..\\Resources\\Texture\\Room\\01_Factory\\room_factory_1.png");

				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"SpriteMaterial_Room_Factory_1", spriteMateiral);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"room_factory_1_1111", L"..\\Resources\\Texture\\Room\\01_Factory\\room_factory_1_1111.png");

				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"SpriteMaterial_room_factory_1_1111", spriteMateiral);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"Room_Factory_2", L"..\\Resources\\Texture\\Room\\01_Factory\\room_factory_2.png");

				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"SpriteMaterial_Room_Factory_2", spriteMateiral);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"Room_Factory_3", L"..\\Resources\\Texture\\Room\\01_Factory\\room_factory_3.png");

				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"SpriteMaterial_Room_Factory_3", spriteMateiral);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"Room_Factory_4", L"..\\Resources\\Texture\\Room\\01_Factory\\room_factory_4.png");

				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"SpriteMaterial_Room_Factory_4", spriteMateiral);
			}
		}
		// temp
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"bg_apt_hallway_0", L"..\\Resources\\Texture\\bg_apt_hallway_0.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"SpriteMaterial_bg_apt_hallway_0", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"bg_bar_0", L"..\\Resources\\Texture\\bg_bar_0.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(spriteShader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"SpriteMaterial_bg_bar_0", spriteMateiral);
		}

		// player
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"spr_idle_0", L"..\\Resources\\Texture\\Player\\spr_idle\\spr_idle_0.png");

				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(spriteShader);
				spriteMateiral->SetTexture(texture);
				spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"SM_spr_idle_0", spriteMateiral);
			}
		}
	}

	void Initialize()
	{
		LoadMesh();
		LoadBuffer();
		LoadShader();
		SetupState();
		LoadMaterial();
	}

	void PushDebugMeshInfo(DebugMesh& mesh)
	{
		debugMeshs.push_back(mesh);
	}


	void Render()
	{
		for (Camera* cam : cameras)
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}

		cameras.clear();
	}


	void Release()
	{
		for (ConstantBuffer* buff : constantBuffer)
		{
			if (buff == nullptr)
				continue;

			delete buff;
			buff = nullptr;
		}
	}

}