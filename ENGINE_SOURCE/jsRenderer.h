#pragma once
#include "CommonInclude.h"
#include "jsMath.h"
#include "jsGraphicDevice_DX11.h"

#include "jsMesh.h"

#define NumOfVertex 4
#define NumOfInputLayout 2

namespace js::renderer
{
	struct Vertex
	{
		math::Vector3 pos;
		math::Vector4 color;
	};

	extern Vertex vertexes[NumOfVertex];

	extern Mesh* mesh;

	extern Microsoft::WRL::ComPtr<ID3DBlob>				errorBlob;
	extern Microsoft::WRL::ComPtr<ID3D11Buffer>			constantBuffer;
		
	extern Microsoft::WRL::ComPtr<ID3DBlob>				VSBlob;
	extern Microsoft::WRL::ComPtr<ID3D11VertexShader>	VS;

	extern Microsoft::WRL::ComPtr<ID3DBlob>				PSBlob;
	extern Microsoft::WRL::ComPtr<ID3D11PixelShader>	PS;

	extern Microsoft::WRL::ComPtr<ID3D11InputLayout>	inputLayout;

	void Initialize();
	void Release();
}