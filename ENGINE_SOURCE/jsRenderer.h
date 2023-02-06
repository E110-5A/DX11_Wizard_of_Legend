#pragma once
#include "CommonInclude.h"
#include "jsMath.h"
#include "jsGraphicDevice_DX11.h"

#include "jsMesh.h"
#include "jsShader.h"
#include "jsConstantBuffer.h"

#define NumOfVertex 4
#define NumOfInputLayout 2

using namespace js::enums;
using namespace js::graphics;

namespace js::renderer
{
	struct Vertex
	{
		math::Vector3 pos;
		math::Vector4 color;
	};

	extern Vertex vertexes[NumOfVertex];
	extern Mesh* mesh;
	extern Shader* shader;
	extern ConstantBuffer* constantBuffers[];
	
	void Initialize();
	void Release();
}