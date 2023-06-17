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

	private:
		ScratchImage mImage; // ���� �̹��� Ȯ����
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV; // ���̴� ���ҽ� ��
		D3D11_TEXTURE2D_DESC mDesc;
	};

}

