#include "Mesh.h"
#include "../Core/Engine.h"
#include "../Shader/Shader.h"

namespace Blue
{
	MeshData::MeshData()
	{
	}

	MeshData::MeshData(const std::vector<Vertex>& vertices, const std::vector<uint32>& indices)
	{
		// �Ķ���� ����.
		this->vertices.assign(vertices.begin(), vertices.end());
		stride = Vertex::Stride();

		this->indices.assign(indices.begin(), indices.end());

		// @Temp: �ӽ� ���ҽ� ����.
		// ����(buffer) - �޸� ���.
		D3D11_BUFFER_DESC vertexBufferDesc = { };
		vertexBufferDesc.ByteWidth = stride * (uint32)this->vertices.size();			// ���� ũ��.
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		// ���� ������.
		D3D11_SUBRESOURCE_DATA vertexData = { };
		vertexData.pSysMem = this->vertices.data();								// ���� ������.

		// (����) ���� ����.
		ID3D11Device& device = Engine::Get().Device();
		HRESULT result = device.CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);

		if (FAILED(result))
		{
			MessageBoxA(nullptr, "Failed to create buffer.", "Error", MB_OK);
			__debugbreak();
		}

		// �ε���(����) ���� ����(������ �����ϴ� ����).
		D3D11_BUFFER_DESC IndexBufferDesc = { };
		IndexBufferDesc.ByteWidth = sizeof(uint32) * (uint32)this->indices.size();
		IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA indexData = {};
		indexData.pSysMem = this->indices.data();

		// �ε��� ���� ����.
		result = device.CreateBuffer(&IndexBufferDesc, &indexData, &indexBuffer);

		if (FAILED(result))
		{
			MessageBoxA(nullptr, "Failed to create index.", "Error", MB_OK);
			__debugbreak();
		}
	}

	MeshData::~MeshData()
	{
		// ���ҽ� ����.
		if (vertexBuffer)
		{
			vertexBuffer->Release();
		}
		if (indexBuffer)
		{
			indexBuffer->Release();
		}
	}

	void MeshData::Bind()
	{
		// ���ؽ�Ʈ ������
		static ID3D11DeviceContext& context = Engine::Get().Context();

		// ����/ �ε��� ���� ���ε�.
		static uint32 offset = 0;
		context.IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		context.IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	}

	Mesh::Mesh()
	{

	}

	void Mesh::Draw()
	{
		// ���ؽ�Ʈ ������.
		static ID3D11DeviceContext& context = Engine::Get().Context();

		// ���� ��ȸ�ϸ鼭 ���ε� & ��ο�.
		for (uint32 ix = 0; ix < (uint32)meshes.size(); ++ix)
		{
			// context�� ���� ����, �ε��� ����, ��ǲ ���̾ƿ�, ���� ���̴�, �ȼ� ���̴� �����ϴµ�.
			// �� ������ ����� ���� ���� ���� ���� ���̴�, �ȼ� ���̴��� ���ٸ� ����, �ε��� ���۸� �ٲ��ָ� �ȴ�.
			meshes[ix]->Bind();
			shaders[ix]->Bind();
			context.DrawIndexed(meshes[ix]->IndexCount(), 0, 0);
		}
	}
}