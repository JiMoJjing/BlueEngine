#include "Shader.h"
#include <d3dcompiler.h>

#include "../Core/Engine.h"

namespace Blue
{
	Shader::Shader(const std::wstring& name)
		: name(name)
	{
		// ��� �߰�.
		wchar_t path[256] = { };
		swprintf_s(path, 256, L"../CompiledShader/%sVertexShader.cso", name.c_str());


		// ��ġ ��ü ������.
		ID3D11Device& device = Engine::Get().Device();

		// CSO �ε�.
		HRESULT result = D3DReadFileToBlob(path, &vertexShaderBuffer);

		if (FAILED(result))
		{
			MessageBoxA(
				nullptr,
				"Failed to read vertex shader object",
				"Error",
				MB_OK
			);

			__debugbreak();
		}

		// ���� ���̴� ��ü ����.
		result = device.CreateVertexShader(																					
			vertexShaderBuffer->GetBufferPointer(),
			vertexShaderBuffer->GetBufferSize(),
			nullptr,
			&vertexShader
		);

		if (FAILED(result))
		{
			MessageBoxA(nullptr, "Failed to create vertex shader.", "Error", MB_OK);
			__debugbreak();
		}



		// �Է� ���̾ƿ�.
		// ���� ���̴��� ������ ���� �����Ͱ� ��� ������� �˷���.

		// POSITION - �ø�ƽ ( DX���� ���ص� ���� ). 
		// 12�� ���� 0���� �����ؼ� 12��ŭ �ǳʶ� ��ġ���� �о���°�. POSITION�� 12����Ʈ�̹Ƿ�.
		// 24�� ���� 0���� �����ؼ� 12 + 12 ��ŭ �ǳ� �� ��ġ���� �о���°�. POSITION : 12, COLOR : 12 �̹Ƿ�.
		D3D11_INPUT_ELEMENT_DESC inputDesc[] =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}, 
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}
		};

		result = device.CreateInputLayout(
			inputDesc,
			_countof(inputDesc),
			vertexShaderBuffer->GetBufferPointer(),
			vertexShaderBuffer->GetBufferSize(),
			&inputLayout
		);

		if (FAILED(result))
		{
			MessageBoxA(nullptr, "Failed to create input layout.", "Error", MB_OK);
			__debugbreak();
		}

		// �ȼ� ���̴� ������.
		swprintf_s(path, 256, L"../CompiledShader/%sPixelShader.cso", name.c_str());
		
		// CSO �ε�.
		result = D3DReadFileToBlob(path, &pixelShaderBuffer);

		if (FAILED(result))
		{
			MessageBoxA(
				nullptr,
				"Failed to read pixel shader object",
				"Error",
				MB_OK
			);

			__debugbreak();
		}

		// �ȼ� ���̴� ��ü ����.
		result = device.CreatePixelShader(
			pixelShaderBuffer->GetBufferPointer(),
			pixelShaderBuffer->GetBufferSize(),
			nullptr,
			&pixelShader
		);

		if (FAILED(result))
		{
			MessageBoxA(
				nullptr,
				"Failed to create pixel shader.",
				"Error",
				MB_OK
			);
			__debugbreak();
		}
	}

	Shader::~Shader()
	{
		// DX ���ҽ� ����.
		if (inputLayout)
		{
			inputLayout->Release();
		}

		if (vertexShader)
		{
			vertexShader->Release();
		}

		if (vertexShaderBuffer)
		{
			vertexShaderBuffer->Release();
		}

		if (pixelShader)
		{
			pixelShader->Release();
		}

		if (pixelShaderBuffer)
		{
			pixelShaderBuffer->Release();
		}
	}

	void Shader::Bind()
	{
		// ��ġ ���� (Device Context) ������.
		static ID3D11DeviceContext& context = Engine::Get().Context();

		// �Է� ���̾ƿ� ����.
		context.IASetInputLayout(inputLayout);

		// ���� �� ��� ����.
		context.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// ���̴� ����.
		context.VSSetShader(vertexShader, nullptr, 0);
		context.PSSetShader(pixelShader, nullptr, 0);
	}
}