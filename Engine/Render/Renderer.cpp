#include "Renderer.h"
#include <vector>
#include <d3dcompiler.h>
#include "../Math/Vector3.h"
#include "TriangleMesh.h"
#include "QuadMesh.h"

#include "Core/Common.h"

namespace Blue
{
	Renderer::Renderer(uint32 width, uint32 height, HWND window)
	{
		// ��ġ ������ ����ϴ� �ɼ�.
		uint32 flag = 0u;

#if _DEBUG
		flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		// ������ ���̺귯�� ����.
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0
		};

		// ���� ü�� ���� ����ü.
		DXGI_SWAP_CHAIN_DESC swapChainDesc = { };
		swapChainDesc.Windowed = true;			// â ���?.
		swapChainDesc.OutputWindow = window;    // � â?
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2;			// �� ���� ����.
		swapChainDesc.SampleDesc.Count = 1;		// ��Ƽ ���ø� ����.
		swapChainDesc.SampleDesc.Quality = 0;   // ��Ƽ ���ø� ����.
		swapChainDesc.BufferDesc.Width = width; // ȭ�� ũ��.
		swapChainDesc.BufferDesc.Height = height;// ȭ�� ũ��.
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

		// ��ġ ����.
		ThrowIfFailed(D3D11CreateDeviceAndSwapChain(
			nullptr,					// �׷��� ī�� ����.
			D3D_DRIVER_TYPE_HARDWARE,	// ��ġ�ε� ����.
			nullptr,
			flag,						// ����� ���� ������ �÷���.
			featureLevels,				// DX ���� ���� �迭.
			_countof(featureLevels),	// DX ���� ���� �迭 ũ��.
			D3D11_SDK_VERSION,			// SDK ����.
			&swapChainDesc,				// ���� ü�� ����.
			&swapChain,					// ���� ü�� - ���۰���.
			&device,					// ����̽� - ���ҽ� ����.
			nullptr,
			&context					// ���ؽ�Ʈ - ���ε�.
		), TEXT("Failed to create devices."));


		/*if (FAILED(result))
		{
			MessageBoxA(nullptr, "Failed to create devices.", "Error", MB_OK);
			__debugbreak();
		}*/

		// ���� Ÿ�� �� ���� ( ���ҽ�(��(����â��)) = �޸� ���( �����ּ�, ��� ũ�� )).
		ID3D11Texture2D* backbuffer = nullptr;
		//swapChain->GetBuffer(0, __uuidof(backbuffer), reinterpret_cast<void**>(&backbuffer));
		auto result = swapChain->GetBuffer(0, IID_PPV_ARGS(&backbuffer));

		if (FAILED(result))
		{
			MessageBoxA(nullptr, "Failed to get backbuffer.", "Error", MB_OK);
			__debugbreak();
		}

		result = device->CreateRenderTargetView(backbuffer, nullptr, &renderTargetView);

		if (FAILED(result))
		{
			MessageBoxA(nullptr, "Failed to create render target view.", "Error", MB_OK);
			__debugbreak();
		}

		// ���� Ÿ�� �� ���ε� (����).
		context->OMSetRenderTargets(1, &renderTargetView, nullptr);

		// ����Ʈ (ȭ��).
		viewport.TopLeftX = 0.f;
		viewport.TopLeftY = 0.f;
		viewport.Width = (float)width;
		viewport.Height = (float)height;
		viewport.MaxDepth = 1.f;
		viewport.MinDepth = 0.f;

		// ����Ʈ ����.
		context->RSSetViewports(1, &viewport);
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::Draw()
	{
		// @�ӽ�/Test
		if (mesh == nullptr)
		{
			//mesh = std::make_unique<TriangleMesh>();
			mesh = std::make_unique<QuadMesh>();
		}

		// �׸��� �� �۾� (BeginScene).
		context->OMSetRenderTargets(1, &renderTargetView, nullptr);


		// ����� (Clear).
		float color[] = { 0.6f, 0.7f, 0.8f, 1.0f };
		context->ClearRenderTargetView(renderTargetView, color);

		// Test Update.
		mesh->Update(1.0f / 60.f);

		// ��ο�(Draw).
		mesh->Draw();

		// ���� ��ȯ (EndScene/Present).
		swapChain->Present(1u, 0u);
	}
}