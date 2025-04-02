#pragma once

#include <vector>
#include <memory>
#include "Component.h"

namespace Blue
{
	// �𵨸� �����ͳ� �޽ø� �׷��ִ� ������Ʈ.
	class StaticMeshComponent : public Component
	{
	public:
		StaticMeshComponent();
		virtual ~StaticMeshComponent();

		virtual void Draw() override;

		// �޽� ���� �Լ�.
		void SetMesh(std::shared_ptr<class Mesh> newMesh);

		// ���̴� ���� �Լ�.
		void AddShader(std::weak_ptr<class Shader> newShader);


	private:
		// �޽�(�𵨸�) ������.
		std::shared_ptr<class Mesh> mesh;

		// ���̴� ( ���� �޽� �� ��ŭ �ʿ�).
		std::vector<std::weak_ptr<class Shader>> shaders;
	};
}