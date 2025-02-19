#pragma once

#include "Math/Vector3.h"
#include "Math/Vector2.h"

namespace Blue
{
	class Vertex
	{
	public:
		// 정점 정보 변경 - 정점 셰이더 변경, 입력 레이아웃 변경.
		Vertex(const Vector3& position, const Vector3& color, const Vector2& texCoord)
			: position(position), color(color), texCoord(texCoord)
		{
		}
		// UV는 어디서? 파일에서.


		static unsigned int Stride() { return sizeof(Vertex); }

	public:
		// 정점의 위치.
		Vector3 position;

		// 정점의 색상.
		Vector3 color;

		// 정점 기준 텍스쳐 좌표.
		Vector2 texCoord;
	};
}