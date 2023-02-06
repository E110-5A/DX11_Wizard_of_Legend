#pragma once
#include "CommonInclude.h"
#include "jsMath.h"
#include "jsGraphicDevice_DX11.h"


namespace js::renderer
{
#define NumOfVertex 4
	struct Vertex
	{
		math::Vector3 pos;
		math::Vector4 color;
	};


	extern Vertex vertexes[NumOfVertex];

	extern ID3D11Buffer*		vertexBuffer;
	extern ID3D11Buffer*		IndexBuffer;
	extern ID3D11Buffer*		ConstantBuffer;
	extern ID3DBlob*			errorBlob;
	extern ID3DBlob*			VSBlob;
	extern ID3DBlob*			PSBlob;

	extern ID3D11VertexShader*	VS;
	extern ID3D11PixelShader*	PS;
	extern ID3D11InputLayout*	inputLayout;

	void Initialize();
	void Release();
}