#include "jwRenderer.h"

namespace renderer
{
	using namespace jw;
	using namespace jw::graphics;

	Vertex vertexes[4] = {};
	Vector4 pos(0.0f, 0.0f, 0.0f, 1.0f);

	jw::Mesh* mesh = nullptr;
	jw::Shader* shader = nullptr;
	jw::graphics::ConstantBuffer* constantBuffer = nullptr;

	void SetupState()
	{
		// Input layout 정점 구조 정보를 넘겨줘야한다.
		D3D11_INPUT_ELEMENT_DESC arrLayout[2] = {};

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


		jw::graphics::GetDevice()->CreateInputLayout(arrLayout, 2
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());
	}

	void LoadBuffer()
	{
		// Vertex Buffer
		mesh = new jw::Mesh();
		mesh->CreateVertexBuffer(vertexes, 4);

		// Index Buffer
		std::vector<UINT> indexes = {};
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		mesh->CreateIndexBuffer(indexes.data(), indexes.size());
		
		// Constant Buffer
		constantBuffer = new ConstantBuffer(eCBType::Transform);
		constantBuffer->Create(sizeof(Info));

		//Info infoinit = {};
		Info infoinit =
		Info{ Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector4(0.0f, 0.0f, 1.0f, 1.0f) ,Vector4(1.0f, 1.0f, 0.0f, 0.0f)	};
		constantBuffer->SetData(&infoinit);
		constantBuffer->Bind(eShaderStage::VS);
	}

	void LoadShader()
	{
		//jw::graphics::GetDevice()->CreateShader();

		shader = new jw::Shader();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
	}

	void Initialize()
	{
		vertexes[0].pos = Vector3(-0.05f, 0.1f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[1].pos = Vector3(0.05f, 0.1f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[2].pos = Vector3(0.05f, -0.1f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		vertexes[3].pos = Vector3(-0.05f, -0.1f, 0.0f);
		vertexes[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		LoadBuffer();
		LoadShader();
		SetupState();
	}

	void Release()
	{
		delete mesh;
		delete shader;
		delete constantBuffer;
	}

}