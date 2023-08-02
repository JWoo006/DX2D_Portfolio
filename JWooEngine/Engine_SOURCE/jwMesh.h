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
		 
		void BindBuffer(); // 파이프라인에 사용할 buffer를 바인드
		void Render();
		void RenderInstanced(UINT startIndexLocation);

		UINT GetIndexCount() { return mIndexCount; }

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> mVertexBuffer; // 스마트 포인터 사용
		Microsoft::WRL::ComPtr<ID3D11Buffer> mIndexBuffer; // 내부에서 포인터 사용

		D3D11_BUFFER_DESC mVBDesc;
		D3D11_BUFFER_DESC mIBDesc;

		UINT mIndexCount;

	};
}


