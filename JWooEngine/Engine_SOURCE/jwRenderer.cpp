#include "jwRenderer.h"

#include "jwResources.h"
#include "jwTexture.h"
#include "jwMaterial.h"
#include "jwStructedBuffer.h"
#include "jwPaintShader.h"
#include "jwParticleShader.h"

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

	// light
	std::vector<Light*> lights = {};
	StructedBuffer* lightsBuffer = nullptr;

	//
	jw::Camera* mainCamera = nullptr;
	std::vector<jw::Camera*> cameras = {};
	std::vector<DebugMesh> debugMeshs = {};

	void SetupState()
	{
#pragma region InputLayout
		// Input layout ���� ���� ������ �Ѱ�����Ѵ�.
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

		std::shared_ptr<Shader> Spriteshader = jw::Resources::Find<Shader>(L"SpriteShader");
		jw::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, Spriteshader->GetVSCode()
			, Spriteshader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> GridShader = jw::Resources::Find<Shader>(L"GridShader");
		jw::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, GridShader->GetVSCode()
			, GridShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> DebugShader = jw::Resources::Find<Shader>(L"DebugShader");
		jw::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, DebugShader->GetVSCode()
			, DebugShader->GetInputLayoutAddressOf());

		shader = jw::Resources::Find<Shader>(L"SpriteAnimationShader");
		jw::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = jw::Resources::Find<Shader>(L"ParticleShader");
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

		// PointMesh
		Vertex v = {};
		v.pos = Vector3(0.0f, 0.0f, 0.0f);
		vertexes.push_back(v);
		indexes.push_back(0);
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		mesh->CreateVertexBuffer(vertexes.data(), vertexes.size());
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());
		Resources::Insert(L"PointMesh", mesh);

		vertexes.clear();
		indexes.clear();

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
		mesh = std::make_shared<Mesh>();
		Resources::Insert(L"RectMesh", mesh);

		mesh->CreateVertexBuffer(vertexes.data(), vertexes.size());

		// Index Buffer
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(2);
		indexes.push_back(3);
		indexes.push_back(0);

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

		// Collider
		constantBuffer[(UINT)eCBType::Collider] = new ConstantBuffer(eCBType::Collider);
		constantBuffer[(UINT)eCBType::Collider]->Create(sizeof(ColliderCB));

		// Animator
		constantBuffer[(UINT)eCBType::Animator] = new ConstantBuffer(eCBType::Animator);
		constantBuffer[(UINT)eCBType::Animator]->Create(sizeof(AnimatorCB));

		//ParticleCB
		constantBuffer[(UINT)eCBType::Particle] = new ConstantBuffer(eCBType::Particle);
		constantBuffer[(UINT)eCBType::Particle]->Create(sizeof(ParticleCB));

		//NoiseCB
		constantBuffer[(UINT)eCBType::Noise] = new ConstantBuffer(eCBType::Noise);
		constantBuffer[(UINT)eCBType::Noise]->Create(sizeof(NoiseCB));

		// light structed buffer
		lightsBuffer = new StructedBuffer();
		lightsBuffer->Create(sizeof(LightAttribute), 2, eViewType::SRV, nullptr, true);
	}

	void LoadShader()
	{
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
		jw::Resources::Insert(L"TriangleShader", shader);

		shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		jw::Resources::Insert(L"SpriteShader", shader);

		std::shared_ptr<Shader> girdShader = std::make_shared<Shader>();
		girdShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		girdShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		jw::Resources::Insert(L"GridShader", girdShader);

		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);
		debugShader->SetRSState(eRSType::WireframeNone);
		jw::Resources::Insert(L"DebugShader", debugShader);

		std::shared_ptr<Shader> spriteAniShader = std::make_shared<Shader>();
		spriteAniShader->Create(eShaderStage::VS, L"SpriteAnimationVS.hlsl", "main");
		spriteAniShader->Create(eShaderStage::PS, L"SpriteAnimationPS.hlsl", "main");
		jw::Resources::Insert(L"SpriteAnimationShader", spriteAniShader);

		std::shared_ptr<PaintShader> paintShader = std::make_shared<PaintShader>();
		paintShader->Create(L"PaintCS.hlsl", "main");
		jw::Resources::Insert(L"PaintShader", paintShader);

		std::shared_ptr<ParticleShader> psSystemShader = std::make_shared<ParticleShader>();
		psSystemShader->Create(L"ParticleCS.hlsl", "main");
		jw::Resources::Insert(L"ParticleSystemShader", psSystemShader);

		std::shared_ptr<Shader> paritcleShader = std::make_shared<Shader>();
		paritcleShader->Create(eShaderStage::VS, L"ParticleVS.hlsl", "main");
		paritcleShader->Create(eShaderStage::GS, L"ParticleGS.hlsl", "main");
		paritcleShader->Create(eShaderStage::PS, L"ParticlePS.hlsl", "main");
		paritcleShader->SetRSState(eRSType::SolidNone);
		paritcleShader->SetDSState(eDSType::NoWrite);
		paritcleShader->SetBSState(eBSType::AlphaBlend);
		paritcleShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
		jw::Resources::Insert(L"ParticleShader", paritcleShader);
	}

	void LoadTexture()
	{
		//paint texture
		std::shared_ptr<Texture> uavTexture = std::make_shared<Texture>();
		uavTexture->Create(1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
		jw::Resources::Insert(L"PaintTexuture", uavTexture);

		std::shared_ptr<Texture> particle = std::make_shared<Texture>();
		Resources::Load<Texture>(L"CartoonSmoke", L"..\\Resources\\particle\\CartoonSmoke.png");

		Resources::Load<Texture>(L"Noise01", L"..\\Resources\\noise\\noise_01.png");
		Resources::Load<Texture>(L"Noise02", L"..\\Resources\\noise\\noise_02.png");
		Resources::Load<Texture>(L"Noise03", L"..\\Resources\\noise\\noise_03.png");
	}

	void LoadMaterial()
	{
		// ���׸��� �߰�
		std::shared_ptr<Shader> shader
			= Resources::Find<Shader>(L"SpriteShader");

		std::shared_ptr<Texture> texture
			= Resources::Load<Texture>(L"Link", L"..\\Resources\\Texture\\Link.png");

		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		Resources::Insert(L"SpriteMaterial", material);

		//texture = Resources::Load<Texture>(L"Smile", L"..\\Resources\\Texture\\Smile.png");
		texture = Resources::Find<Texture>(L"PaintTexuture");
		material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		material->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"SpriteMaterial02", material);

		// UI
		{
			// hud_base
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"spr_hud_0", L"..\\Resources\\Texture\\UI\\spr_hud\\spr_hud_0.png");

				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"SpriteMaterial_spr_hud_0", spriteMateiral);
			}
			// battery_base
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"spr_hud_battery_0", L"..\\Resources\\Texture\\UI\\spr_hud_battery\\spr_hud_battery_0.png");

				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
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
					spriteMateiral->SetShader(shader);
					spriteMateiral->SetTexture(texture);
					spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
					Resources::Insert(L"SpriteMaterial_spr_keyboard_shift_0", spriteMateiral);
				}
				{
					std::shared_ptr<Texture> texture
						= Resources::Load<Texture>(L"spr_keyboard_shift_1", L"..\\Resources\\Texture\\UI\\keyboard\\spr_keyboard_shift\\spr_keyboard_shift_1.png");

					std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
					spriteMateiral->SetShader(shader);
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
					spriteMateiral->SetShader(shader);
					spriteMateiral->SetTexture(texture);
					spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
					Resources::Insert(L"SpriteMaterial_spr_hud_timer_0", spriteMateiral);
				}
				{
					std::shared_ptr<Texture> texture
						= Resources::Load<Texture>(L"spr_hud_timer_1", L"..\\Resources\\Texture\\UI\\spr_hud_timer\\spr_hud_timer_1.png");

					std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
					spriteMateiral->SetShader(shader);
					spriteMateiral->SetTexture(texture);
					spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
					Resources::Insert(L"SpriteMaterial_spr_hud_timer_1", spriteMateiral);
				}
				{
					std::shared_ptr<Texture> texture
						= Resources::Load<Texture>(L"spr_timer_0", L"..\\Resources\\Texture\\UI\\spr_timer\\spr_timer_0.png");

					std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
					spriteMateiral->SetShader(shader);
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
					spriteMateiral->SetShader(shader);
					spriteMateiral->SetTexture(texture);
					spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
					Resources::Insert(L"SpriteMaterial_spr_hud_subweapon_0", spriteMateiral);
				}
				// spr_katana_pickup
				{
					std::shared_ptr<Texture> texture
						= Resources::Load<Texture>(L"spr_katana_pickup_0", L"..\\Resources\\Texture\\UI\\spr_katana_pickup\\spr_katana_pickup_0.png");

					std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
					spriteMateiral->SetShader(shader);
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
					spriteMateiral->SetShader(shader);
					spriteMateiral->SetTexture(texture);
					spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
					Resources::Insert(L"SpriteMaterial_spr_left_click_0", spriteMateiral);
				}
				// spr_left_click
				{
					std::shared_ptr<Texture> texture
						= Resources::Load<Texture>(L"spr_left_click_1", L"..\\Resources\\Texture\\UI\\spr_left_click\\spr_left_click_1.png");

					std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
					spriteMateiral->SetShader(shader);
					spriteMateiral->SetTexture(texture);
					spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
					Resources::Insert(L"SpriteMaterial_spr_left_click_1", spriteMateiral);
				}
				// spr_right_click
				{
					std::shared_ptr<Texture> texture
						= Resources::Load<Texture>(L"spr_right_click_1", L"..\\Resources\\Texture\\UI\\spr_right_click\\spr_right_click_1.png");

					std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
					spriteMateiral->SetShader(shader);
					spriteMateiral->SetTexture(texture);
					spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
					Resources::Insert(L"SpriteMaterial_spr_right_click_1", spriteMateiral);
				}
			}
			// MouseCursor
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"MouseCursor", L"..\\Resources\\Texture\\spr_cursor\\spr_cursor_0.png");

				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"SpriteMaterial_MouseCursor", spriteMateiral);
			}
		}

		// title
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"Title_Temp", L"..\\Resources\\Texture\\Title\\title_temp.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(shader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"SpriteMaterial_Title_Temp", spriteMateiral);

			// background
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"Title_Background", L"..\\Resources\\Texture\\Title\\spr_title_background\\spr_title_background_0.png");

				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"SpriteMaterial_Title_Background", spriteMateiral);
			}

			//fence
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"Title_Fence", L"..\\Resources\\Texture\\Title\\spr_title_fence\\spr_title_fence_0.png");

				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"SpriteMaterial_Title_Fence", spriteMateiral);
			}

			//bottom_grass
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"Title_Grass", L"..\\Resources\\Texture\\Title\\spr_title_grass\\spr_title_grass_0.png");

				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"SpriteMaterial_Title_Grass", spriteMateiral);
			}
		}

		// Room_Factory
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"Room_Factory_0", L"..\\Resources\\Texture\\Room\\01_Factory\\room_factory_0.png");

				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"SpriteMaterial_Room_Factory_0", spriteMateiral);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"Room_Factory_1", L"..\\Resources\\Texture\\Room\\01_Factory\\room_factory_1.png");

				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"SpriteMaterial_Room_Factory_1", spriteMateiral);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"room_factory_1_1111", L"..\\Resources\\Texture\\Room\\01_Factory\\room_factory_1_1111.png");

				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"SpriteMaterial_room_factory_1_1111", spriteMateiral);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"Room_Factory_2", L"..\\Resources\\Texture\\Room\\01_Factory\\room_factory_2.png");

				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"SpriteMaterial_Room_Factory_2", spriteMateiral);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"Room_Factory_3", L"..\\Resources\\Texture\\Room\\01_Factory\\room_factory_3.png");

				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"SpriteMaterial_Room_Factory_3", spriteMateiral);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"room_factory_3_2", L"..\\Resources\\Texture\\Room\\01_Factory\\room_factory_3_2.png");

				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"SpriteMaterial_room_factory_3_2", spriteMateiral);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"Room_Factory_4", L"..\\Resources\\Texture\\Room\\01_Factory\\room_factory_4.png");

				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"SpriteMaterial_Room_Factory_4", spriteMateiral);
			}
		}
		// Room_Studio
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"room_haunted_alien1", L"..\\Resources\\Texture\\Room\\02_Studio\\room_haunted_alien1.png");

				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"SpriteMaterial_room_haunted_alien1", spriteMateiral);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"room_haunted_finale2_boss", L"..\\Resources\\Texture\\Room\\02_Studio\\room_haunted_finale2.png");

				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"SpriteMaterial_room_haunted_finale2_boss", spriteMateiral);
			}
		}
		// Room_Bunker
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"room_bunker_0", L"..\\Resources\\Texture\\Room\\03_Bunker\\room_bunker_0.png");

				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"SpriteMaterial_room_bunker_0", spriteMateiral);
			}
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"room_bunker2_boss_final", L"..\\Resources\\Texture\\Room\\03_Bunker\\room_bunker2_boss_final.png");

				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				Resources::Insert(L"SpriteMaterial_room_bunker2_boss_final", spriteMateiral);
			}
		}
		// temp
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"bg_apt_hallway_0", L"..\\Resources\\Texture\\bg_apt_hallway_0.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(shader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"SpriteMaterial_bg_apt_hallway_0", spriteMateiral);
		}
		{
			std::shared_ptr<Texture> texture
				= Resources::Load<Texture>(L"bg_bar_0", L"..\\Resources\\Texture\\bg_bar_0.png");

			std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
			spriteMateiral->SetShader(shader);
			spriteMateiral->SetTexture(texture);
			Resources::Insert(L"SpriteMaterial_bg_bar_0", spriteMateiral);
		}

		// player
		{
			{
				std::shared_ptr<Texture> texture
					= Resources::Load<Texture>(L"spr_idle_0", L"..\\Resources\\Texture\\Player\\spr_idle\\spr_idle_0.png");

				std::shared_ptr<Material> spriteMateiral = std::make_shared<Material>();
				spriteMateiral->SetShader(shader);
				spriteMateiral->SetTexture(texture);
				spriteMateiral->SetRenderingMode(eRenderingMode::Transparent);
				Resources::Insert(L"SM_spr_idle_0", spriteMateiral);
			}
		}

		//shader
		{
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

			shader
				= Resources::Find<Shader>(L"SpriteAnimationShader");
			material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"SpriteAnimaionMaterial", material);

			shader
				= Resources::Find<Shader>(L"ParticleShader");
			material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetRenderingMode(eRenderingMode::Transparent);

			std::shared_ptr<Texture> particleTexx
				= Resources::Find<Texture>(L"CartoonSmoke");
			material->SetTexture(particleTexx);
			Resources::Insert(L"ParticleMaterial", material);

			//std::shared_ptr<Shader> debugShader
			//	= Resources::Find<Shader>(L"DebugShader");

			//material = std::make_shared<Material>();
			//material->SetShader(debugShader);
			//Resources::Insert(L"PaintMaterial", material);
		}
	}

	void Initialize()
	{
		LoadMesh();
		LoadBuffer();
		LoadShader();
		SetupState();
		LoadTexture();
		LoadMaterial();
	}

	void PushDebugMeshAttribute(DebugMesh mesh)
	{
		debugMeshs.push_back(mesh);
	}

	void BindLights()
	{
		std::vector<LightAttribute> lightsAttributes = {};
		for (Light* light : lights)
		{
			LightAttribute attribute = light->GetAttribute();
			lightsAttributes.push_back(attribute);
		}

		lightsBuffer->SetData(lightsAttributes.data(), lightsAttributes.size());
		lightsBuffer->BindSRV(eShaderStage::VS, 13);
		lightsBuffer->BindSRV(eShaderStage::PS, 13);
	}

	void BindNoiseTexture()
	{
		std::shared_ptr<Texture> texture
			= Resources::Find<Texture>(L"Noise01");

		texture->BindShaderResource(eShaderStage::VS, 15);
		texture->BindShaderResource(eShaderStage::HS, 15);
		texture->BindShaderResource(eShaderStage::DS, 15);
		texture->BindShaderResource(eShaderStage::GS, 15);
		texture->BindShaderResource(eShaderStage::PS, 15);
		texture->BindShaderResource(eShaderStage::CS, 15);

		ConstantBuffer* cb = constantBuffer[(UINT)eCBType::Noise];
		NoiseCB data = {};
		data.size.x = texture->GetWidth();
		data.size.y = texture->GetHeight();

		cb->SetData(&data);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::GS);
		cb->Bind(eShaderStage::PS);
		cb->Bind(eShaderStage::CS);
	}

	void Render()
	{
		BindNoiseTexture();
		BindLights();

		for (Camera* cam : cameras)
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}

		cameras.clear();
		lights.clear();
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

		delete lightsBuffer;
		lightsBuffer = nullptr;
	}

}