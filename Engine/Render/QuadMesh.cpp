#include "QuadMesh.h"
#include "Shader/TextureMappingShader.h"

namespace Blue
{
	QuadMesh::QuadMesh()
	{
		// 정점 배열.
		std::vector<Vertex> vertices =
		{
			Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(1.f, 0.f, 0.f), Vector2(0.f, 0.f)),
			Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(0.f, 1.f, 0.f), Vector2(1.f, 0.f)),
			Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(0.f, 0.f, 1.f), Vector2(1.f, 1.f)),
			Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(1.f, 1.f, 1.f), Vector2(0.f, 1.f))
		};

		// 인덱스 배열.
		std::vector<uint32> indices = { 0, 1, 2, 0, 2, 3 };
		meshes.emplace_back(std::make_shared<MeshData>(vertices, indices));
		shaders.emplace_back(std::make_shared<TextureMappingShader>(L"Default", "T_coord.png"));
	}
}