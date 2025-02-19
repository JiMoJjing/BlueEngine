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
		// 파라미터 복사.
		this->vertices.assign(vertices.begin(), vertices.end());
		stride = Vertex::Stride();

		this->indices.assign(indices.begin(), indices.end());

		// @Temp: 임시 리소스 생성.
		// 버퍼(buffer) - 메모리 덩어리.
		D3D11_BUFFER_DESC vertexBufferDesc = { };
		vertexBufferDesc.ByteWidth = stride * (uint32)this->vertices.size();			// 버퍼 크기.
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		// 정점 데이터.
		D3D11_SUBRESOURCE_DATA vertexData = { };
		vertexData.pSysMem = this->vertices.data();								// 정점 데이터.

		// (정점) 버퍼 생성.
		ID3D11Device& device = Engine::Get().Device();
		HRESULT result = device.CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);

		if (FAILED(result))
		{
			MessageBoxA(nullptr, "Failed to create buffer.", "Error", MB_OK);
			__debugbreak();
		}

		// 인덱스(색인) 버퍼 생성(정점을 조립하는 순서).
		D3D11_BUFFER_DESC IndexBufferDesc = { };
		IndexBufferDesc.ByteWidth = sizeof(uint32) * (uint32)this->indices.size();
		IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA indexData = {};
		indexData.pSysMem = this->indices.data();

		// 인덱스 버퍼 생성.
		result = device.CreateBuffer(&IndexBufferDesc, &indexData, &indexBuffer);

		if (FAILED(result))
		{
			MessageBoxA(nullptr, "Failed to create index.", "Error", MB_OK);
			__debugbreak();
		}
	}

	MeshData::~MeshData()
	{
		// 리소스 해제.
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
		// 컨텍스트 얻어오기
		static ID3D11DeviceContext& context = Engine::Get().Context();

		// 정점/ 인덱스 버퍼 바인딩.
		static uint32 offset = 0;
		context.IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		context.IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	}

	Mesh::Mesh()
	{

	}

	void Mesh::Draw()
	{
		// 컨텍스트 얻어오기.
		static ID3D11DeviceContext& context = Engine::Get().Context();

		// 루프 순회하면서 바인딩 & 드로우.
		for (uint32 ix = 0; ix < (uint32)meshes.size(); ++ix)
		{
			// context에 정점 버퍼, 인덱스 버퍼, 인풋 레이아웃, 정점 셰이더, 픽셀 셰이더 설정하는데.
			// 그 순서는 상관이 없고 만약 같은 정점 셰이더, 픽셀 셰이더를 쓴다면 정점, 인덱스 버퍼만 바꿔주면 된다.
			meshes[ix]->Bind();
			shaders[ix]->Bind();
			context.DrawIndexed(meshes[ix]->IndexCount(), 0, 0);
		}
	}
}