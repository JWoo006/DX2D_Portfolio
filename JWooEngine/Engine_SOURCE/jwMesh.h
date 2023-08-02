#pragma once
#include "jwResource.h"
#include "jwGraphicDevice_Dx11.h"

namespace jw
{
	class Mesh : public Resource
	{
	public:
		Mesh();
		~Mesh();

		virtual HRESULT Load(const std::wstring& path) override;

		bool CreateVertexBuffer(void* data, UINT count);
		bool CreateIndexBuffer(void* data, UINT count);
		 
		void BindBuffer(); // ���������ο� ����� buffer�� ���ε�
		void Render();
		void RenderInstanced(UINT startIndexLocation);

		UINT GetIndexCount() { return mIndexCount; }

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> mVertexBuffer; // ����Ʈ ������ ���
		Microsoft::WRL::ComPtr<ID3D11Buffer> mIndexBuffer; // ���ο��� ������ ���

		D3D11_BUFFER_DESC mVBDesc;
		D3D11_BUFFER_DESC mIBDesc;

		UINT mIndexCount;

	};
}


