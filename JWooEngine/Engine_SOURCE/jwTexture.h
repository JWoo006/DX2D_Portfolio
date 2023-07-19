#pragma once
#include "jwResource.h"
#include "jwGraphics.h"

#include "../External/DirectXTex/Include/DirectXTex.h"
#include "../External/DirectXTex/Include/DirectXTex.inl"

#ifdef _DEBUG
#pragma comment(lib, "..\\External\\DirectXTex\\Lib\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\External\\DirectXTex\\Lib\\Release\\DirectXTex.lib")
#endif

namespace jw::graphics
{
	class Texture : public Resource
	{
	public:
		Texture();
		~Texture();

		virtual HRESULT Load(const std::wstring& path) override;
		void BindShader(eShaderStage stage, UINT startSlot);
		void Clear();

		size_t GetWidth() { return mImage.GetMetadata().width; }
		size_t GetHeight() { return mImage.GetMetadata().height; }


	private:
		ScratchImage mImage; // 원본 이미지 확장자
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV; // 셰이더 리소스 뷰
		D3D11_TEXTURE2D_DESC mDesc;
	};

}


