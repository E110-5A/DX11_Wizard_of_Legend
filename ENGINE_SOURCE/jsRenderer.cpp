#include "jsRenderer.h"



namespace js::renderer
{
	Vertex vertexes[NumOfVertex] = {};

	ID3DBlob* errorBlob = nullptr;
	ID3D11Buffer* vertexBuffer = nullptr;
	ID3D11Buffer* indexBuffer = nullptr;
	ID3D11Buffer* constantBuffer = nullptr;


	ID3DBlob* VSBlob = nullptr;
	ID3D11VertexShader* VS = nullptr;
	
	ID3DBlob* PSBlob = nullptr;
	ID3D11PixelShader* PS = nullptr;

	ID3D11InputLayout* inputLayout = nullptr;

	void SetUpState()
	{
		D3D11_INPUT_ELEMENT_DESC arrLayoutDesc[NumOfInputLayout] = {};

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

		graphics::GetDevice()->CreateInputLayout(arrLayoutDesc, NumOfInputLayout
			, VSBlob->GetBufferPointer()
			, VSBlob->GetBufferSize()
			, &inputLayout);
	}

	void LoadBuffer()
	{
		D3D11_BUFFER_DESC vertexDesc = {};

		vertexDesc.ByteWidth = sizeof(Vertex) * NumOfVertex;
		vertexDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		vertexDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		vertexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA subVertexData = {};
		subVertexData.pSysMem = vertexes;

		graphics::GetDevice()->CreateBuffer(&vertexDesc, &subVertexData, &vertexBuffer);


		std::vector<UINT> indexes;
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		D3D11_BUFFER_DESC indexDesc = {};

		indexDesc.ByteWidth = indexes.size() * sizeof(UINT);
		indexDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		indexDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		indexDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA subIndexData = {};
		subIndexData.pSysMem = indexes.data();

		graphics::GetDevice()->CreateBuffer(&indexDesc, &subIndexData, &indexBuffer);





		D3D11_BUFFER_DESC ConstantDesc = {};

		ConstantDesc.ByteWidth = sizeof(math::Vector4);
		ConstantDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		ConstantDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		ConstantDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		graphics::GetDevice()->CreateBuffer(&ConstantDesc, nullptr, &constantBuffer);

		math::Vector4 pos(0.2f, 0.2f, 0.f, 0.f);
		graphics::GetDevice()->BindConstantBuffer(constantBuffer, &pos, sizeof(math::Vector4));
	}

	void LoadShader()
	{
		graphics::GetDevice()->CreateShader();
	}

	void Initialize()
	{
		vertexes[0].pos = math::Vector3(-0.5f, 0.5f, 0.5f);
		vertexes[0].color = math::Vector4(0.f, 1.f, 0.f, 1.f);

		vertexes[1].pos = math::Vector3(0.5f, 0.5f, 0.5f);
		vertexes[1].color = math::Vector4(1.f, 1.f, 1.f, 1.f);

		vertexes[2].pos = math::Vector3(0.5f, -0.5f, 0.5f);
		vertexes[2].color = math::Vector4(1.f, 0.f, 0.f, 1.f);

		vertexes[3].pos = math::Vector3(-0.5f, -0.5f, 0.5f);
		vertexes[3].color = math::Vector4(0.f, 0.f, 1.f, 1.f);

		LoadShader();
		SetUpState();
		LoadBuffer();

		graphics::GetDevice()->BindConstantBuffer(vertexBuffer, vertexes, sizeof(renderer::Vertex) * NumOfVertex);
	}

	void Release()
	{
	}
}

