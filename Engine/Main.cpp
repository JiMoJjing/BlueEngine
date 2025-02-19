
#include "Core/Engine.h"
#include <iostream>

using namespace Blue;

// â ���� �� �� ���� �Լ� (Entry Point).
// HINSTANCE - ���α׷��� ���� �޸� �ּ� ( ����ü ).
//int WINAPI WinMain(
//	_In_ HINSTANCE hInstance,
//	_In_opt_ HINSTANCE hPrevInstance,
//	_In_ LPSTR lpCmdLine,
//	_In_ int nShowCmd
//)
//{
//	// ���� ���� �� ����.
//	Engine engine(1280, 800, TEXT("Engine Demo"), hInstance);
//	engine.Run();
//
//	return 0;
//}

// ���� -> ��Ŀ -> �ý��� -> â�� �ַܼ�.
int main()
{
	// �ְܼ� ���� â�� ���ÿ� ������ �ܼ��� ���������� ��� ����
	Engine engine(1280, 800, TEXT("Engine Demo"), GetModuleHandle(nullptr));
	engine.Run();
}