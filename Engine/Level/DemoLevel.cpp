#include "DemoLevel.h"

#include "Actor/Actor.h"
#include "Actor/QuadActor.h"
#include "Component/StaticMeshComponent.h"
#include "Component/CameraComponent.h"
#include "Render/QuadMesh.h"

#include "Resource/ShaderLoader.h"
#include "Resource/ModelLoader.h"
#include "Resource/TextureLoader.h"

#include "Shader/TextureMappingShader.h"


namespace Blue
{
	DemoLevel::DemoLevel()
	{
		// ���� ��(����) ����.

		// ���� ����.
		std::shared_ptr<QuadActor> quadActor = std::make_shared<QuadActor>();
		quadActor->transform.scale = Vector3::One * 0.5f;
		quadActor->transform.position.x = 0.5f;

		// ī�޶� ���� ����.
		std::shared_ptr<Actor> cameraActor = std::make_shared<Actor>();
		cameraActor->AddComponent(std::make_shared<CameraComponent>());
		cameraActor->transform.position.x = 1.0f;

		// ���͸� ������ �߰�.
		AddActor(quadActor);
		AddActor(cameraActor);
	}

	DemoLevel::~DemoLevel()
	{
	}
}