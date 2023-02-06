#include "jsMesh.h"
#include "jsRenderer.h"
#include "jsGraphicDevice_DX11.h"

namespace js
{
	Mesh::Mesh()
		: Resource(enums::eResourceType::Mesh)
		, mVertexBufferDesc{}
		, mIndexBufferDesc{}
		, mIndexCount(0)
	{
	}
	Mesh::~Mesh()
	{
	}
	
	HRESULT Mesh::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	bool Mesh::CreateVertexBuffer(void* data, UINT count)
	{
		mVertexBufferDesc.ByteWidth = sizeof(renderer::Vertex) * count;
		mVertexBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		mVertexBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		mVertexBufferDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA subData = {};
		subData.pSysMem = data;

		if (!graphics::GetDevice()->CreateBuffer(&mVertexBufferDesc, &subData, mVertexBuffer.GetAddressOf()))
			return false;

		return true;
	}
	bool Mesh::CreateIndexBuffer(void* data, UINT count)
	{
		mIndexCount = count;
		mIndexBufferDesc.ByteWidth = sizeof(UINT) * count;
		mIndexBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		mIndexBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		mIndexBufferDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA subData = {};
		subData.pSysMem = data;

		if (!graphics::GetDevice()->CreateBuffer(&mIndexBufferDesc, &subData, mIndexBuffer.GetAddressOf()))
			return false;

		return true;
	}
	void Mesh::BindBuffer()
	{
		UINT stride = sizeof(renderer::Vertex);
		UINT offset = 0;

		graphics::GetDevice()->BindVertexBuffer(0, 1, mVertexBuffer.GetAddressOf(), &stride, &offset);
		graphics::GetDevice()->BindIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	}
	void Mesh::Render()
	{
		graphics::GetDevice()->DrawIndexed(mIndexCount, 0, 0);
	}
}