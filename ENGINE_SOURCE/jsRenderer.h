#pragma once
#include "CommonInclude.h"
#include "jsMath.h"
#include "jsGraphicDevice_DX11.h"

#include "jsMesh.h"
#include "jsShader.h"

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
	extern Microsoft::WRL::ComPtr<ID3D11Buffer>			constantBuffer;
	
	extern Mesh* mesh;
	extern Shader* shader;

	void Initialize();
	void Release();
}