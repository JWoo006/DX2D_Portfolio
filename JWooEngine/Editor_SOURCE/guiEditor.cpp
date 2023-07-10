#include "guiEditor.h"
#include "jwMesh.h"
#include "jwResources.h"
#include "jwTransform.h"
#include "jwMeshRenderer.h"
#include "jwMaterial.h"
#include "jwGridScript.h"
#include "jwRenderer.h"

namespace gui
{
	using namespace jw::enums;
	std::vector<Widget*> Editor::mWidgets = {};
	std::vector<EditorObject*> Editor::mEditorObjects = {};
	std::vector<DebugObject*> Editor::mDebugOjbects = {};

	void Editor::Initialize()
	{
		mDebugOjbects.resize((UINT)eColliderType::End);

		std::shared_ptr<jw::Mesh> mesh
			= jw::Resources::Find<jw::Mesh>(L"DebugRect");
		std::shared_ptr<jw::Material> material
			= jw::Resources::Find<jw::Material>(L"DebugMaterial");

		mDebugOjbects[(UINT)eColliderType::Rect] = new DebugObject();
		mDebugOjbects[(UINT)eColliderType::Rect]->AddComponent<jw::Transform>();
		jw::MeshRenderer* mr
			= mDebugOjbects[(UINT)eColliderType::Rect]->AddComponent<jw::MeshRenderer>();
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
	}

	void Editor::DebugRender(const jw::graphics::DebugMesh& mesh)
	{
		DebugObject* debugObj = mDebugOjbects[(UINT)mesh.type];

		// 위치 크기 회전 정보를 받아와서
		// 해당 게임오브젝트위에 그려주면된다.



		debugObj->Render();
	}
}
