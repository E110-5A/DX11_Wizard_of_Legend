#include "jsRenderer.h"


#define NumofInputLayout 2

namespace js::renderer
{
	Vertex vertexes[NumOfVertex] = {};

	ID3DBlob* errorBlob = nullptr;
	ID3D11Buffer* vertexBuffer = nullptr;

	ID3DBlob* VSBlob = nullptr;
	ID3D11VertexShader* VS = nullptr;
	
	ID3DBlob* PSBlob = nullptr;
	ID3D11PixelShader* PS = nullptr;

	ID3D11InputLayout* inputLayout = nullptr;

	void SetUpState()
	{
		D3D11_INPUT_ELEMENT_DESC arrLayoutDesc[NumofInputLayout] = {};

		arrLayoutDesc[0].AlignedByteOffset = 0;
		arrLayoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayoutDesc[0].InputSlot = 0;
		arrLayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[0].SemanticName = "POSITION";
		arrLayoutDesc[0].SemanticIndex = 0;

		arrLayoutDesc[1].AlignedByteOffset = 12;
		arrLayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayoutDesc[1].InputSlot = 0;
		arrLayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[1].SemanticName = "COLOR";
		arrLayoutDesc[1].SemanticIndex = 0;

		graphics::GetDevice()->CreateInputLayout(arrLayoutDesc, NumofInputLayout
			, VSBlob->GetBufferPointer()
			, VSBlob->GetBufferSize()
			, &inputLayout);
	}

	void LoadBuffer()
	{
		D3D11_BUFFER_DESC vertexDesc = {};

		vertexDesc.ByteWidth = sizeof(Vertex) * NumOfVertex;
		vertexDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		vertexDesc.Usage = D3D11_USAGE_DYNAMIC;
		vertexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA subData = {};
		subData.pSysMem = vertexes;

		graphics::GetDevice()->CreateBuffer(&vertexDesc, &subData, &vertexBuffer);
	}

	void LoadShader()
	{
		graphics::GetDevice()->CreateShader();
	}

	void Initialize()
	{
		vertexes[0].pos = math::Vector3(0.f, 0.5f, 0.5f);
		vertexes[0].color = math::Vector4(0.f, 1.f, 0.f, 1.f);

		vertexes[1].pos = math::Vector3(0.5f, -0.5f, 0.5f);
		vertexes[1].color = math::Vector4(1.f, 0.f, 0.f, 1.f);

		vertexes[2].pos = math::Vector3(-0.5f, -0.5f, 0.5f);
		vertexes[2].color = math::Vector4(0.f, 0.f, 1.f, 1.f);

		LoadShader();
		SetUpState();
		LoadBuffer();
	}

	void Release()
	{
	}
}

