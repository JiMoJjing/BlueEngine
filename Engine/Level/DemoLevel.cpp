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
		// 데모 씬(레벨) 구성.

		// 액터 생성.
		std::shared_ptr<QuadActor> quadActor = std::make_shared<QuadActor>();
		quadActor->transform.scale = Vector3::One * 0.5f;
		quadActor->transform.position.x = 0.5f;

		// 카메라 액터 생성.
		std::shared_ptr<Actor> cameraActor = std::make_shared<Actor>();
		cameraActor->AddComponent(std::make_shared<CameraComponent>());
		cameraActor->transform.position.x = 1.0f;

		// 액터를 레벨에 추가.
		AddActor(quadActor);
		AddActor(cameraActor);
	}

	DemoLevel::~DemoLevel()
	{
	}
}