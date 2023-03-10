#pragma once
#include "jsGraphics.h"
#include "jsResource.h"

namespace js
{
	class Mesh : public Resource
	{
	public:
		Mesh();
		virtual ~Mesh();

		virtual HRESULT Load(const std::wstring& path) override;

		bool CreateVertexBuffer(void* data, UINT count);
		bool CreateIndexBuffer(void* data, UINT count);
		void BindBuffer();
		void Render();

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> mVertexBuffer;
		D3D11_BUFFER_DESC mVertexBufferDesc;

		Microsoft::WRL::ComPtr<ID3D11Buffer> mIndexBuffer;
		D3D11_BUFFER_DESC mIndexBufferDesc;
		UINT mIndexCount;
	};
}