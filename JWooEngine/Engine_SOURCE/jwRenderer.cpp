#include "jwRenderer.h"

namespace jw::renderer
{
	Vertex vertexes[3] = {};

	// Input Layout (���� ����)
	ID3D11InputLayout* triangleLayout = nullptr;
	// Vertex Buffer
	ID3D11Buffer* triangleBuffer = nullptr;
	// error blob
	ID3DBlob* errorBlob = nullptr;
	// Vertex Shader code -> Binary Code
	ID3DBlob* triangleVSBlob = nullptr;
	// Vertex Shader
	ID3D11VertexShader* triangleVSShader = nullptr;
	// Pixel Shader code -> Binary Code
	ID3DBlob* trianglePSBlob = nullptr;
	// Vertex Shader
	ID3D11PixelShader* trianglePSShader = nullptr;

	// �簢�� 1
	Vertex squareVertexes[6] = {};
	ID3D11InputLayout* squareLayout = nullptr;
	ID3D11Buffer* squareBuffer = nullptr;
	ID3DBlob* squareVSBlob = nullptr;
	ID3D11VertexShader* squareVSShader = nullptr;
	ID3DBlob* squarePSBlob = nullptr;
	ID3D11PixelShader* squarePSShader = nullptr;

	// �簢�� 2
	Vertex squareVertexes2[4] = {};
	WORD squreIndices[6] = {};
	ID3D11Buffer* indexBuffer = nullptr;
	ID3D11InputLayout* squareLayout2 = nullptr;
	ID3D11Buffer* squareBuffer2 = nullptr;
	ID3DBlob* squareVSBlob2 = nullptr;
	ID3D11VertexShader* squareVSShader2 = nullptr;
	ID3DBlob* squarePSBlob2 = nullptr;
	ID3D11PixelShader* squarePSShader2 = nullptr;

	// ������
	Vertex diamondVertexes[6] = {};
	ID3D11InputLayout* diamondLayout = nullptr;
	ID3D11Buffer* diamondBuffer = nullptr;
	ID3DBlob* diamondVSBlob = nullptr;
	ID3D11VertexShader* diamondVSShader = nullptr;
	ID3DBlob* diamondPSBlob = nullptr;
	ID3D11PixelShader* diamondPSShader = nullptr;

	// ��
	ID3D11InputLayout* circleLayout = nullptr;
	ID3D11Buffer* circleBuffer = nullptr;
	ID3DBlob* circleerrorBlob = nullptr;
	ID3DBlob* circleVSBlob = nullptr;
	ID3D11VertexShader* circleVSShader = nullptr;
	ID3DBlob* circlePSBlob = nullptr;
	ID3D11PixelShader* circlePSShader = nullptr;


	void SetupState()
	{

	}

	void LoadBuffer()
	{
		D3D11_BUFFER_DESC triangleDesc = {};
		triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		triangleDesc.ByteWidth = sizeof(Vertex) * 3;
		triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		triangleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA triangleData = {};
		triangleData.pSysMem = vertexes;
		jw::graphics::GetDevice()->CreateBuffer(&triangleBuffer, &triangleDesc, &triangleData);


		// �簢�� 1
		D3D11_BUFFER_DESC squareDesc = {};
		squareDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		squareDesc.ByteWidth = sizeof(Vertex) * 6;
		squareDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		squareDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA squareData = {};
		squareData.pSysMem = squareVertexes;
		jw::graphics::GetDevice()->CreateBuffer(&squareBuffer, &squareDesc, &squareData);

		// �簢�� 2
		D3D11_BUFFER_DESC squareDesc2 = {};
		squareDesc2.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		squareDesc2.ByteWidth = sizeof(Vertex) * 4;
		squareDesc2.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		squareDesc2.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA squareData2 = {};
		squareData2.pSysMem = squareVertexes2;
		jw::graphics::GetDevice()->CreateBuffer(&squareBuffer2, &squareDesc2, &squareData2);

		// �ε��� ���� ����
		D3D11_BUFFER_DESC indexBufferDesc;
		ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(WORD) * 6; // �簢���� �ε��� 6���� ������
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA indexBufferData;
		ZeroMemory(&indexBufferData, sizeof(indexBufferData));
		indexBufferData.pSysMem = squreIndices;

		
		jw::graphics::GetDevice()->CreateBuffer(&indexBuffer, &indexBufferDesc, &indexBufferData);


		// ������
		D3D11_BUFFER_DESC diamondDesc = {};
		diamondDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		diamondDesc.ByteWidth = sizeof(Vertex) * 6;
		diamondDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		diamondDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA diamondData = {};
		diamondData.pSysMem = diamondVertexes;
		jw::graphics::GetDevice()->CreateBuffer(&diamondBuffer, &diamondDesc, &diamondData);

		// ��
		// ���� ���� ������
		const int circleResolution = 32; // ���� �ػ� (���� ����)
		Vertex circleVertices[circleResolution];

		const float radius = 0.5f; // ���� ������
		const float angleIncrement = XM_2PI / circleResolution; // ���� �׸��� ���� ���� ����

		for (int i = 0; i < circleResolution; ++i)
		{
			float theta = i * angleIncrement;
			circleVertices[i].pos = XMFLOAT3(cos(theta) * radius, sin(theta) * radius, 0.0f);
			circleVertices[i].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f); // ���� ����
		}

		D3D11_BUFFER_DESC circleVertexBufferDesc;
		ZeroMemory(&circleVertexBufferDesc, sizeof(circleVertexBufferDesc));
		circleVertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		circleVertexBufferDesc.ByteWidth = sizeof(Vertex) * circleResolution; // ���� ���� ������ŭ ������ ���� ���� ����
		circleVertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		circleVertexBufferDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA circleVertexData;
		ZeroMemory(&circleVertexData, sizeof(circleVertexData));
		circleVertexData.pSysMem = circleVertices;

		
		jw::graphics::GetDevice()->CreateBuffer(&circleBuffer, &circleVertexBufferDesc, &circleVertexData);

	}

	void LoadShader()
	{
		jw::graphics::GetDevice()->CreateShader();
	}

	void Initialize()
	{
		//triangle
		vertexes[0].pos = Vector3(0.0f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[1].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[2].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		//square
		squareVertexes[0].pos = Vector3(-0.5f, -0.5f, 0.0f);
		squareVertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
					  
		squareVertexes[1].pos = Vector3(-0.5f, 0.5f, 0.0f);
		squareVertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
					  
		squareVertexes[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		squareVertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		squareVertexes[3].pos = Vector3(-0.5f, 0.5f, 0.0f);
		squareVertexes[3].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		squareVertexes[4].pos = Vector3(0.5f, 0.5f, 0.0f);
		squareVertexes[4].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		squareVertexes[5].pos = Vector3(0.5f, -0.5f, 0.0f);
		squareVertexes[5].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		//square2
		squareVertexes2[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		squareVertexes2[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		squareVertexes2[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		squareVertexes2[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		squareVertexes2[2].pos = Vector3(-0.5f, -0.5f, 0.0f);
		squareVertexes2[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		squareVertexes2[3].pos = Vector3(0.5f, -0.5f, 0.0f);
		squareVertexes2[3].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		WORD rectangleIndices[] =
		{
			0, 1, 2,    // �ﰢ�� 1
			2, 1, 3     // �ﰢ�� 2
		};

		//diamond
		diamondVertexes[0].pos = Vector3(-0.5f, 0.0f, 0.0f);
		diamondVertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		diamondVertexes[1].pos = Vector3(0.0f, 0.5f, 0.0f);
		diamondVertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		diamondVertexes[2].pos = Vector3(0.0f, -0.5f, 0.0f);
		diamondVertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		diamondVertexes[3].pos = Vector3(0.0f, 0.5f, 0.0f);
		diamondVertexes[3].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		diamondVertexes[4].pos = Vector3(0.5f, 0.0f, 0.0f);
		diamondVertexes[4].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		diamondVertexes[5].pos = Vector3(0.0f, -0.5f, 0.0f);
		diamondVertexes[5].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		//��
		

		SetupState();
		LoadBuffer();
		LoadShader();
	}
}