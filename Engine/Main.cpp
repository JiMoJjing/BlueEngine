
#include "Core/Engine.h"
#include <iostream>
#include "Core/Common.h"

#include "Level/DemoLevel.h"


using namespace Blue;

// 창 모드로 할 때 메인 함수 (Entry Point).
// HINSTANCE - 프로그램에 대한 메모리 주소 ( 구조체 ).
//int WINAPI WinMain(
//	_In_ HINSTANCE hInstance,
//	_In_opt_ HINSTANCE hPrevInstance,
//	_In_ LPSTR lpCmdLine,
//	_In_ int nShowCmd
//)
//{
//	// 엔진 생성 및 실행.
//	Engine engine(1280, 800, TEXT("Engine Demo"), hInstance);
//	engine.Run();
//
//	return 0;
//}

// 설정 -> 링커 -> 시스템 -> 창을 콘솔로.

int main()
{
	//TestClass<Engine>();
	//TestClass<TextureMappingShader>();


	// 콘솔과 엔진 창이 동시에 켜지고 콘솔은 디버깅용으로 사용 가능
	Engine engine(1280, 800, TEXT("Engine Demo"), GetModuleHandle(nullptr));
	engine.SetLevel(std::make_shared<DemoLevel>());
	engine.Run();
}