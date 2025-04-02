#pragma once

#include <vector>
#include <memory>
#include "Component.h"

namespace Blue
{
	// 모델링 데이터나 메시를 그려주는 컴포넌트.
	class StaticMeshComponent : public Component
	{
	public:
		StaticMeshComponent();
		virtual ~StaticMeshComponent();

		virtual void Draw() override;

		// 메시 설정 함수.
		void SetMesh(std::shared_ptr<class Mesh> newMesh);

		// 셰이더 설정 함수.
		void AddShader(std::weak_ptr<class Shader> newShader);


	private:
		// 메시(모델링) 데이터.
		std::shared_ptr<class Mesh> mesh;

		// 셰이더 ( 서브 메시 수 만큼 필요).
		std::vector<std::weak_ptr<class Shader>> shaders;
	};
}