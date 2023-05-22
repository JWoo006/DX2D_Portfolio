#include "jwGraphicDevice_Dx11.h"
#include "jwApplication.h"

extern jw::Application application;

namespace jw::graphics
{
	GraphicDevice_Dx11::GraphicDevice_Dx11()
	{
		HWND hwnd = application.GetHwnd();

		// Device, Context 생성

		UINT deviceFlag = D3D11_CREATE_DEVICE_DEBUG; // 열거형 찾아보자
		D3D_FEATURE_LEVEL featureLevel = (D3D_FEATURE_LEVEL)0;

		D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr
			, deviceFlag, nullptr, 0
			, D3D11_SDK_VERSION
			, mDevice.GetAddressOf(), &featureLevel
			, mContext.GetAddressOf());

		// Swapchain 더블 버퍼링 

	}

	GraphicDevice_Dx11::~GraphicDevice_Dx11()
	{
	}

}
