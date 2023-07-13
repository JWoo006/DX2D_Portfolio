#include "guiEditor.h"
#include "..\\Engine_SOURCE\\jwMesh.h"
#include "..\\Engine_SOURCE\\jwResources.h"
#include "..\\Engine_SOURCE\\jwTransform.h"
#include "..\\Engine_SOURCE\\jwMeshRenderer.h"
#include "..\\Engine_SOURCE\\jwMaterial.h"
#include "..\\Engine_SOURCE\\jwRenderer.h"

#include "jwGridScript.h"

namespace gui
{
	using namespace jw::enums;
	std::vector<Widget*> Editor::mWidgets = {};
	std::vector<EditorObject*> Editor::mEditorObjects = {};
	std::vector<DebugObject*> Editor::mDebugObjects = {};

	void Editor::Initialize()
	{
		mDebugObjects.resize((UINT)eColliderType::End);

		std::shared_ptr<jw::Mesh> mesh
			= jw::Resources::Find<jw::Mesh>(L"DebugRect");
		std::shared_ptr<jw::Material> material
			= jw::Resources::Find<jw::Material>(L"DebugMaterial");

		mDebugObjects[(UINT)eColliderType::Rect] = new DebugObject();
		mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<jw::Transform>();
		jw::MeshRenderer* mr
			= mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<jw::MeshRenderer>();
		mr->SetMaterial(material);
		mr->SetMesh(mesh);


		EditorObject* grid = new EditorObject();
		grid->SetName(L"Grid");

		mr = grid->AddComponent<jw::MeshRenderer>();
		mr->SetMesh(jw::Resources::Find<jw::Mesh>(L"RectMesh"));
		mr->SetMaterial(jw::Resources::Find<jw::Material>(L"GridMaterial"));
		jw::GridScript* gridSc = grid->AddComponent<jw::GridScript>();
		gridSc->SetCamera(renderer::cameras[0]);

		mEditorObjects.push_back(grid);

	}
	void Editor::Run()
	{
		Update();
		LateUpdate();
		Render();
	}
	void Editor::Update()
	{


		for (EditorObject* obj : mEditorObjects)
		{
			obj->Update();
		}
	}
	void Editor::LateUpdate()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->LateUpdate();
		}
	}
	void Editor::Render()
	{
		//Microsoft::WRL::ComPtr<ID3D11DepthStencilState> ds
		//	= renderer::depthStencilStates[(UINT)jw::graphics::eDSType::Less];
		//jw::graphics::GetDevice()->BindDepthStencilState(ds.Get());

		for (EditorObject* obj : mEditorObjects)
		{
			obj->Render();
		}

		for (const jw::graphics::DebugMesh& mesh
			: renderer::debugMeshs)
		{
			DebugRender(mesh);
		}
	}
	void Editor::Release()
	{
		for (auto widget : mWidgets)
		{
			delete widget;
			widget = nullptr;
		}

		for (auto editorObj : mEditorObjects)
		{
			delete editorObj;
			editorObj = nullptr;
		}

		for (auto debugObj : mDebugObjects)
		{
			delete debugObj;
			debugObj = nullptr;
		}
	}

	void Editor::DebugRender(const jw::graphics::DebugMesh& mesh)
	{
		DebugObject* debugObj = mDebugObjects[(UINT)mesh.type];

		// 위치 크기 회전 정보를 받아와서
		// 해당 게임오브젝트위에 그려주면된다.
		jw::Transform* tr = debugObj->GetComponent<jw::Transform>();

		Vector3 pos = mesh.position;
		pos.z -= 0.01f;

		tr->SetPosition(pos);
		tr->SetScale(mesh.scale);
		tr->SetRotation(mesh.rotation);

		tr->LateUpdate();

		/*jw::MeshRenderer * mr
			= debugObj->GetComponent<jw::MeshRenderer>();*/
			// main camera
		jw::Camera* mainCamara = renderer::mainCamera;

		jw::Camera::SetGpuViewMatrix(mainCamara->GetViewMatrix());
		jw::Camera::SetGpuProjectionMatrix(mainCamara->GetProjectionMatrix());



		debugObj->Render();
	}
}
