#include "jsRenderer.h"
#include "jsResources.h"

namespace js::renderer
{
	Vertex vertexes[NumOfVertex] = {};
	ConstantBuffer* constantBuffers[(UINT)eCBType::End] = {};

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

		arrLayoutDesc[2].AlignedByteOffset = 28;
		arrLayoutDesc[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayoutDesc[2].InputSlot = 0;
		arrLayoutDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[2].SemanticName = "TEXCOORD";
		arrLayoutDesc[2].SemanticIndex = 0;

		Shader* shader = Resources::Find<Shader>(L"RectShader");
		graphics::GetDevice()->CreateInputLayout(arrLayoutDesc, NumOfInputLayout
			, shader->GetVertexBlobBufferPointer()
			, shader->GetVertexBlobBufferSize()
			, shader->GetInputLyaoutAddressOf());
	}

	void LoadBuffer()
	{
		Mesh* mesh = new Mesh();
		Resources::Insert<Mesh>(L"RectMesh", mesh);
		mesh->CreateVertexBuffer(vertexes, NumOfVertex);


		std::vector<UINT> indexes;

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		mesh->CreateIndexBuffer(indexes.data(), indexes.size());
				
		math::Vector4 pos(0.2f, 0.2f, 0.f, 0.f);
		constantBuffers[(UINT)eCBType::Transform] = new ConstantBuffer();
		constantBuffers[(UINT)eCBType::Transform]->Create(sizeof(math::Vector4));
		constantBuffers[(UINT)eCBType::Transform]->Bind(&pos);
	}

	void LoadShader()
	{
		Shader* shader = new Shader();
		shader->Create(graphics::eShaderStage::VS, L"TriangleVS.hlsl", "VS_Test");
		shader->Create(graphics::eShaderStage::PS, L"TrianglePS.hlsl", "PS_Test");
		Resources::Insert<Shader>(L"RectShader", shader);
	}

	void Initialize()
	{
		vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.5f);
		vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
		vertexes[0].uv = Vector2(0.f, 0.f);

		vertexes[1].pos = Vector3(0.5f, 0.5f, 0.5f);
		vertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		vertexes[1].uv = Vector2(1.f, 0.f);

		vertexes[2].pos = Vector3(0.5f, -0.5f, 0.5f);
		vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		vertexes[2].uv = Vector2(1.f, 1.f);

		vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.5f);
		vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);
		vertexes[3].uv = Vector2(0.f, 1.f);

		LoadShader();
		SetUpState();
		LoadBuffer();
	}

	void Release()
	{
		for (size_t index = 0; index < (UINT)eCBType::End; ++index)
		{
			delete constantBuffers[index];
			constantBuffers[index] = nullptr;
		}
	}
}

