#include "jwApplication.h"
#include "jwInput.h"
#include "jwTime.h"
#include "jwRenderer.h"
#include "jwSceneManager.h"
#include "jwCollisionManager.h"

namespace jw
{
	Application::Application()
		: graphicDevice(nullptr)
		, mHwnd(NULL)
		, mWidth(-1)
		, mHeight(-1)
	{

	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
		Destroy();
	}

	void Application::Initialize()
	{
		Time::Initiailize();
		Input::Initialize();

		renderer::Initialize();

		SceneManager::Initialize();
	}

	void Application::Update()
	{
		if (Input::GetKeyDown(eKeyCode::K))
		{
			if (mbColShow)
			{
				mbColShow = false;
			}
			else
			{
				mbColShow = true;
			}
		}

		Time::Update();
		Input::Update();

		CollisionManager::Update();
		SceneManager::Update();
	}

	void Application::LateUpdate()
	{
		SceneManager::LateUpdate();
		
	}

	void Application::Render()
	{
		Time::Render();

		graphicDevice->ClearTarget();
		graphicDevice->UpdateViewPort();
		
		//SceneManager::Render();
		// camera render
		renderer::Render();
		
		//graphicDevice->Draw();
		
	}

	void Application::Destroy()
	{
		SceneManager::Destroy();
	}

	void Application::Present()
	{
		graphicDevice->Present();
	}


	void Application::SetWindow(HWND hwnd, UINT width, UINT height)
	{
		if (graphicDevice == nullptr)
		{
			mHwnd = hwnd;
			mWidth = width;
			mHeight = height;

			graphicDevice = std::make_unique<jw::graphics::GraphicDevice_Dx11>();
			jw::graphics::GetDevice() = graphicDevice.get();
		}

		RECT rt = { 0, 0, (LONG)width , (LONG)height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}

	Vector2 Application::GetResolutionRatio()
	{
		RECT WindowRECT;

		GetClientRect(mHwnd, &WindowRECT);

		float width = static_cast<float>(WindowRECT.right - WindowRECT.left);
		float height = static_cast<float>(WindowRECT.bottom - WindowRECT.top);

		return Vector2(mWidth / width, mHeight / height);

	}
}
