#include "jwGraphicDevice_Dx11.h"
#include "jwApplication.h"
#include "jwRenderer.h"

extern jw::Application application;

namespace jw::graphics
{
	GraphicDevice_Dx11::GraphicDevice_Dx11()
	{
		// Device, Context 생성
		HWND hWnd = application.GetHwnd();
		UINT deviceFlag = D3D11_CREATE_DEVICE_DEBUG; // 열거형 찾아보자
		D3D_FEATURE_LEVEL featureLevel = (D3D_FEATURE_LEVEL)0;

		D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr
			, deviceFlag, nullptr, 0
			, D3D11_SDK_VERSION
			, mDevice.GetAddressOf(), &featureLevel
			, mContext.GetAddressOf());

		// Swapchain 더블 버퍼링 
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {}; // 쓰레기값이 들어가면 안되므로 초기화
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferDesc.Width = application.GetWidth();
		swapChainDesc.BufferDesc.Height = application.GetHeight();

		if (!CreateSwapChain(&swapChainDesc, hWnd))
			return;

		// get rendertarget by swapchain
		if (FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D)
			, (void**)mRenderTarget.GetAddressOf())))
			return; // FAILED 매크로 - 실패 할시 리턴

		// create rendertarget view
		mDevice->CreateRenderTargetView((ID3D11Resource*)mRenderTarget.Get(), nullptr, mRenderTargetView.GetAddressOf());

		D3D11_TEXTURE2D_DESC depthStencilDesc = {};
		depthStencilDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.CPUAccessFlags = 0;

		depthStencilDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.Width = application.GetWidth();
		depthStencilDesc.Height = application.GetHeight();
		depthStencilDesc.ArraySize = 1;

		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.MipLevels = 0;
		depthStencilDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA data;
		if (!CreateTexture(&depthStencilDesc, &data))
			return;

		RECT winRect = {};
		GetClientRect(hWnd, &winRect);

		//typedef struct D3D11_VIEWPORT
		//{
		//	FLOAT TopLeftX;
		//	FLOAT TopLeftY;
		//	FLOAT Width;
		//	FLOAT Height;
		//	FLOAT MinDepth;
		//	FLOAT MaxDepth;
		//} 	D3D11_VIEWPORT;

		mViewPort =
		{
			0.0f, 0.0f
			, (float)(winRect.right - winRect.left)
			, (float)(winRect.bottom - winRect.top)
			, 0.0f, 1.0f
		};

		BindViewPort(&mViewPort);

		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
	}

	GraphicDevice_Dx11::~GraphicDevice_Dx11()
	{
	}

	bool GraphicDevice_Dx11::CreateSwapChain(const DXGI_SWAP_CHAIN_DESC* desc, HWND hWnd)
	{
		DXGI_SWAP_CHAIN_DESC dxgiDesc = {};

		dxgiDesc.OutputWindow = hWnd;
		dxgiDesc.Windowed = true;
		dxgiDesc.BufferCount = desc->BufferCount;
		dxgiDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;

		dxgiDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		dxgiDesc.BufferDesc.Width = desc->BufferDesc.Width;
		dxgiDesc.BufferDesc.Height = desc->BufferDesc.Height;
		dxgiDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
		dxgiDesc.BufferDesc.RefreshRate.Numerator = 240;
		dxgiDesc.BufferDesc.RefreshRate.Denominator = 1;
		dxgiDesc.BufferDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED;
		dxgiDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

		dxgiDesc.SampleDesc.Count = 1;
		dxgiDesc.SampleDesc.Quality = 0;

		Microsoft::WRL::ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
		Microsoft::WRL::ComPtr<IDXGIAdapter> pAdapter = nullptr;
		Microsoft::WRL::ComPtr<IDXGIFactory> pFactory = nullptr;

		if (FAILED(mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf())))
			return false;

		if (FAILED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pAdapter.GetAddressOf())))
			return false;

		if (FAILED(pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf())))
			return false;

		if (FAILED(pFactory->CreateSwapChain(mDevice.Get(), &dxgiDesc, mSwapChain.GetAddressOf())))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateBuffer(ID3D11Buffer** buffer, D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data)
	{
		if (FAILED(mDevice->CreateBuffer(desc, data, buffer)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateShader()
	{
		ID3DBlob* vsBlob = nullptr;
		std::filesystem::path shaderPath
			= std::filesystem::current_path().parent_path();
		shaderPath += L"\\Shader_SOURCE\\";

		std::filesystem::path vsPath(shaderPath.c_str());
		vsPath += L"TriangleVS.hlsl";

		D3DCompileFromFile(vsPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, "main", "vs_5_0", 0, 0, &jw::renderer::triangleVSBlob, &jw::renderer::errorBlob);

		if (jw::renderer::errorBlob)
		{
			OutputDebugStringA((char*)jw::renderer::errorBlob->GetBufferPointer());
			jw::renderer::errorBlob->Release();
		}

		mDevice->CreateVertexShader(jw::renderer::triangleVSBlob->GetBufferPointer()
			, jw::renderer::triangleVSBlob->GetBufferSize()
			, nullptr, &jw::renderer::triangleVSShader);

		std::filesystem::path psPath(shaderPath.c_str());
		psPath += L"TrianglePS.hlsl";

		D3DCompileFromFile(psPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, "main", "ps_5_0", 0, 0, &jw::renderer::trianglePSBlob, &jw::renderer::errorBlob);

		if (jw::renderer::errorBlob)
		{
			OutputDebugStringA((char*)jw::renderer::errorBlob->GetBufferPointer());
			jw::renderer::errorBlob->Release();
		}

		mDevice->CreatePixelShader(jw::renderer::trianglePSBlob->GetBufferPointer()
			, jw::renderer::trianglePSBlob->GetBufferSize()
			, nullptr, &jw::renderer::trianglePSShader);

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

		mDevice->CreateInputLayout(arrLayout, 2
			, renderer::triangleVSBlob->GetBufferPointer()
			, renderer::triangleVSBlob->GetBufferSize()
			, &renderer::triangleLayout);


		//원
		ID3DBlob* circlevsBlob = nullptr;
		std::filesystem::path circleshaderPath
			= std::filesystem::current_path().parent_path();
		circleshaderPath += L"\\Shader_SOURCE\\";

		std::filesystem::path circlevsPath(circleshaderPath.c_str());
		circlevsPath += L"CircleVS.hlsl";

		D3DCompileFromFile(circlevsPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, "main", "vs_5_0", 0, 0, &jw::renderer::circleVSBlob, &jw::renderer::circleerrorBlob);

		if (jw::renderer::circleerrorBlob)
		{
			OutputDebugStringA((char*)jw::renderer::circleerrorBlob->GetBufferPointer());
			jw::renderer::circleerrorBlob->Release();
		}

		mDevice->CreateVertexShader(jw::renderer::circleVSBlob->GetBufferPointer()
			, jw::renderer::circleVSBlob->GetBufferSize()
			, nullptr, &jw::renderer::circleVSShader);

		std::filesystem::path circlepsPath(circleshaderPath.c_str());
		circlepsPath += L"CirclePS.hlsl";

		D3DCompileFromFile(circlepsPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, "main", "ps_5_0", 0, 0, &jw::renderer::circlePSBlob, &jw::renderer::circleerrorBlob);

		if (jw::renderer::circleerrorBlob)
		{
			OutputDebugStringA((char*)jw::renderer::circleerrorBlob->GetBufferPointer());
			jw::renderer::circleerrorBlob->Release();
		}

		mDevice->CreatePixelShader(jw::renderer::circlePSBlob->GetBufferPointer()
			, jw::renderer::circlePSBlob->GetBufferSize()
			, nullptr, &jw::renderer::circlePSShader);

		// Input layout 정점 구조 정보를 넘겨줘야한다.
		D3D11_INPUT_ELEMENT_DESC circlearrLayout[2] = {};

		circlearrLayout[0].AlignedByteOffset = 0;
		circlearrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		circlearrLayout[0].InputSlot = 0;
		circlearrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		circlearrLayout[0].SemanticName = "POSITION";
		circlearrLayout[0].SemanticIndex = 0;

		circlearrLayout[1].AlignedByteOffset = 12;
		circlearrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		circlearrLayout[1].InputSlot = 0;
		circlearrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		circlearrLayout[1].SemanticName = "COLOR";
		circlearrLayout[1].SemanticIndex = 0;

		mDevice->CreateInputLayout(circlearrLayout, 2
			, renderer::circleVSBlob->GetBufferPointer()
			, renderer::circleVSBlob->GetBufferSize()
			, &renderer::circleLayout);

		return true;
	}

	bool GraphicDevice_Dx11::CreateTexture(const D3D11_TEXTURE2D_DESC* desc, void* data)
	{
		D3D11_TEXTURE2D_DESC dxgiDesc = {};
		dxgiDesc.BindFlags = desc->BindFlags;
		dxgiDesc.Usage = desc->Usage;
		dxgiDesc.CPUAccessFlags = 0;

		dxgiDesc.Format = desc->Format;
		dxgiDesc.Width = desc->Width;
		dxgiDesc.Height = desc->Height;
		dxgiDesc.ArraySize = desc->ArraySize;

		dxgiDesc.SampleDesc.Count = desc->SampleDesc.Count;
		dxgiDesc.SampleDesc.Quality = 0;

		dxgiDesc.MipLevels = desc->MipLevels;
		dxgiDesc.MiscFlags = desc->MiscFlags;

		if (FAILED(mDevice->CreateTexture2D(&dxgiDesc, nullptr, mDepthStencilBuffer.ReleaseAndGetAddressOf())))
			return false;

		if (FAILED(mDevice->CreateDepthStencilView(mDepthStencilBuffer.Get(), nullptr, mDepthStencilView.GetAddressOf())))
			return false;

		return true;
	}

	void GraphicDevice_Dx11::BindViewPort(D3D11_VIEWPORT* viewPort)
	{
		mContext->RSSetViewports(1, viewPort);
	}

	void GraphicDevice_Dx11::Draw()
	{
		// render target clear
		FLOAT bgColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		mContext->ClearRenderTargetView(mRenderTargetView.Get(), bgColor);
		mContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);

		//Bind VS, PS 
		mContext->VSSetShader(renderer::triangleVSShader, 0, 0);
		mContext->PSSetShader(renderer::trianglePSShader, 0, 0);

		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());

		// viewport update
		HWND hWnd = application.GetHwnd();
		RECT winRect = {};
		GetClientRect(hWnd, &winRect);
		mViewPort =
		{
			0.0f, 0.0f
			, (float)(winRect.right - winRect.left)
			, (float)(winRect.bottom - winRect.top)
			, 0.0f, 1.0f
		};
		BindViewPort(&mViewPort);

		// 삼각형
		// input assembler 정점데이터 정보 지정
		UINT vertexsize = sizeof(renderer::Vertex);
		UINT offset = 0;

		mContext->IASetVertexBuffers(0, 1, &renderer::triangleBuffer, &vertexsize, &offset);
		mContext->IASetInputLayout(renderer::triangleLayout);
		mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		mContext->Draw(3, 0);

		// 사각형 1
		// change viewport
		mViewPort =
		{
			0.0f, 0.0f
			, 100
			, 100
			, 0.0f, 1.0f
		};
		BindViewPort(&mViewPort);
		UINT squarevertexsize = sizeof(renderer::Vertex);
		UINT squareoffset = 0;
		mContext->IASetVertexBuffers(0, 1, &renderer::squareBuffer, &squarevertexsize, &squareoffset);
		//mContext->IASetInputLayout(renderer::squareLayout);
		mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		// Draw Render Target
		mContext->Draw(6, 0);

		// 사각형 2
		// change viewport
		mViewPort =
		{
			1100.0f, 0.0f
			, 500
			, 500
			, 0.0f, 1.0f
		};
		BindViewPort(&mViewPort);
		UINT squarevertexsize2 = sizeof(renderer::Vertex);
		UINT squareoffset2 = 0;
		mContext->IASetVertexBuffers(0, 1, &renderer::squareBuffer2, &squarevertexsize2, &squareoffset2);
		mContext->IASetIndexBuffer(renderer::indexBuffer, DXGI_FORMAT_R16_UINT, 0);
		mContext->IASetInputLayout(renderer::squareLayout2);
		mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		mContext->DrawIndexed(6, 0, 0);

		// 마름모
		mViewPort =
		{
			100.0f, 600.0f
			, 300
			, 300
			, 0.0f, 1.0f
		};
		BindViewPort(&mViewPort);
		UINT diamondvertexsize = sizeof(renderer::Vertex);
		UINT diamondoffset = 0;
		mContext->IASetVertexBuffers(0, 1, &renderer::diamondBuffer, &diamondvertexsize, &diamondoffset);
		mContext->IASetInputLayout(renderer::diamondLayout);
		mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		mContext->Draw(6, 0);

		// 원

		//Bind VS, PS 
		mContext->VSSetShader(renderer::circleVSShader, 0, 0);
		mContext->PSSetShader(renderer::circlePSShader, 0, 0);
		mViewPort =
		{
			1100.0f, 100.0f
			, 300
			, 300
			, 0.0f, 1.0f
		};
		
		BindViewPort(&mViewPort);
		UINT circlesize = sizeof(renderer::Vertex);
		UINT circleoffset = 0;
		mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		mContext->IASetInputLayout(renderer::circleLayout);
		mContext->IASetVertexBuffers(0, 1, &renderer::circleBuffer, &circlesize, &circleoffset);
		mContext->Draw(32, 0); // 원의 정점 개수로 구성됨

		// 레더타겟에 있는 이미지를 화면에 그려준다
		mSwapChain->Present(0, 0);
	}

}
