#pragma once

#include "Math/Vector3.h"
#include "Math/Vector2.h"

namespace Blue
{
	class Vertex
	{
	public:
		// ���� ���� ���� - ���� ���̴� ����, �Է� ���̾ƿ� ����.
		Vertex(const Vector3& position, const Vector3& color, const Vector2& texCoord)
			: position(position), color(color), texCoord(texCoord)
		{
		}
		// UV�� ���? ���Ͽ���.


		static unsigned int Stride() { return sizeof(Vertex); }

	public:
		// ������ ��ġ.
		Vector3 position;

		// ������ ����.
		Vector3 color;

		// ���� ���� �ؽ��� ��ǥ.
		Vector2 texCoord;
	};
}