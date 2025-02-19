#pragma once
#include <memory>
#include <Windows.h>
#include <string>
#include "Type.h"
#include <d3d11.h>

namespace Blue
{
	class Engine
	{
	public:
		Engine(uint32 width,
			uint32 height,
			const std::wstring& title,
			HINSTANCE hInstance);
		virtual ~Engine();

		// ¿£Áø ½ÇÇà ÇÔ¼ö.
		void Run();

		// À©µµ¿ì ¸Þ½ÃÁö Ã³¸® ·çÇÁ.
		static LRESULT CALLBACK WindowProc(HWND handle,
			UINT message,
			WPARAM wparam,
			LPARAM lparam);

		// ½Ì±ÛÅæ Á¢±Ù ÇÔ¼ö.
		static Engine& Get();

		// Getter.
		ID3D11Device& Device() const;
		ID3D11DeviceContext& Context() const;


	protected:
		// Ã¢ °´Ã¼.
		std::shared_ptr<class Window> window;

		// ·»´õ·¯ °´Ã¼.
		std::shared_ptr<class Renderer> renderer;

		// ½Ì±ÛÅæ °´Ã¼.
		static Engine* instance;
	};
}