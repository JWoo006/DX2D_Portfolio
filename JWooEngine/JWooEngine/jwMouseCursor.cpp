#include "jwMouseCursor.h"
#include "jwInput.h"
#include "jwCamera.h"
#include "jwRenderer.h"
#include "jwResources.h"
#include "jwApplication.h"

extern jw::Application application;
#define MOUSEZPOS -9.0f;

namespace jw
{
	Vector3 MouseCursor::mCursorPos = {};
	Vector3 MouseCursor::mCursorEndPos = {};
	Vector3 MouseCursor::mCursorWorldPos = {};
	MouseCursor::MouseCursor()
	{
		AddComponent<MeshRenderer>();
	}
	MouseCursor::~MouseCursor()
	{
	}
	void MouseCursor::Initialize()
	{
		SetName(L"MouseCursor");
		mr = GetComponent<MeshRenderer>();
		mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial_MouseCursor"));
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		//mTextureRatio = GetComponent<MeshRenderer>()->GetMaterial()->GetTexture()->GetTextureSize();
		tr = GetComponent<Transform>();
		tr->SetPosition(Vector3(1.0f, 0.0, -9.0f));
		tr->SetScale(Vector3(mTextureRatio.x, mTextureRatio.y, 1.0f));
		//tr->SetRotation(Vector3(0.0f, 0.0f, DegreeToRadian(80.0f)));

		GameObject::Initialize();
	}
	void MouseCursor::Update()
	{
		GameObject::Update();
	}
	void MouseCursor::LateUpdate()
	{
		int a = 0;
		Vector3 testPos = renderer::mainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();
		mCursorPos = Vector3(Input::GetMousePos().x - testPos.x, Input::GetMousePos().y + testPos.y, 0.0f); //ui용도로만 쓰라는건가?
		mCursorWorldPos = Vector3(Input::GetMousePos().x, Input::GetMousePos().y, 0.0f);
		mCursorEndPos = Vector3(800.0f, 450.0f, 0.0f);

		Viewport viewport;
		viewport.width = application.GetWidth();
		viewport.height = application.GetHeight();
		viewport.x = 0;
		viewport.y = 0;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		mCursorPos = viewport.Unproject(mCursorPos, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);
		mCursorPos.z = MOUSEZPOS;

		mCursorWorldPos = viewport.Unproject(mCursorWorldPos, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);
		mCursorWorldPos.z = MOUSEZPOS;
		mCursorEndPos = viewport.Unproject(mCursorEndPos, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);
		mCursorEndPos.z = MOUSEZPOS;

		Input::SetWorldMousePos(mCursorWorldPos);
		Input::SetUIMousePos(mCursorPos);

		tr->SetPosition(mCursorPos);
		GameObject::LateUpdate();
	}
	void MouseCursor::Render()
	{
		GameObject::Render();
	}
}