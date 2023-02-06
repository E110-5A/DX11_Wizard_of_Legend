#include "jsApplication.h"
#include "jsRenderer.h"
#include "jsTime.h"
#include "jsInput.h"

namespace js
{
	using namespace graphics;

	Application::Application()
		: mHwnd(nullptr)
		, mHdc(nullptr)
		, mHeight(0)
		, mWidth(0)
	{
	}
	Application::~Application()
	{
	}

	void Application::Initalize()
	{
		Time::Initialize();
		Input::Initialize();

		renderer::Initialize();
	}
	void Application::Update()
	{
		Time::Update();
		Input::Update();

	}
	void Application::FixedUpdate()
	{
	}
	void Application::Render()
	{
		Time::Render(mHdc);

		graphicDevice->Draw();
	}

	void Application::Run()
	{
		Update();
		FixedUpdate();
		Render();
	}
	void Application::Release()
	{
		renderer::Release();
	}

	void Application::SetWindow(HWND hwnd, UINT width, UINT height)
	{
		if (nullptr == graphicDevice)
		{
			mHwnd = hwnd;
			mHdc = GetDC(mHwnd);
			mWidth = width;
			mHeight = height;

			ValidationMode validationMode = ValidationMode::Disabled;
			graphicDevice = std::make_unique<GraphicDevice_DX11>();
			graphics::GetDevice() = graphicDevice.get();
		}

		RECT rect = { 0, 0, (LONG)width, (LONG)height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, rect.right - rect.left, rect.bottom - rect.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}
}