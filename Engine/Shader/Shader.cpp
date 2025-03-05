#include "Shader.h"
#include <d3dcompiler.h>

#include "../Core/Engine.h"

namespace Blue
{
	Shader::Shader(const std::wstring& name)
		: name(name)
	{
		// 경로 추가.
		wchar_t path[256] = { };
		swprintf_s(path, 256, L"../CompiledShader/%sVertexShader.cso", name.c_str());


		// 장치 객체 얻어오기.
		ID3D11Device& device = Engine::Get().Device();

		// CSO 로드.
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

		// 정점 셰이더 객체 생성.
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



		// 입력 레이아웃.
		// 정점 셰이더에 전달할 정점 데이터가 어떻게 생겼는지 알려줌.

		// POSITION - 시멘틱 ( DX에서 정해둔 변수 ). 
		// 12인 이유 0에서 시작해서 12만큼 건너뛴 위치부터 읽어오는것. POSITION이 12바이트이므로.
		// 24인 이유 0에서 시작해서 12 + 12 만큼 건너 뛴 위치부터 읽어오는것. POSITION : 12, COLOR : 12 이므로.
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

		// 픽셀 셰이더 컴파일.
		swprintf_s(path, 256, L"../CompiledShader/%sPixelShader.cso", name.c_str());
		
		// CSO 로드.
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

		// 픽셀 셰이더 객체 생성.
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
		// DX 리소스 해제.
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
		// 장치 문맥 (Device Context) 얻어오기.
		static ID3D11DeviceContext& context = Engine::Get().Context();

		// 입력 레이아웃 전달.
		context.IASetInputLayout(inputLayout);

		// 조립 할 모양 설정.
		context.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// 셰이더 설정.
		context.VSSetShader(vertexShader, nullptr, 0);
		context.PSSetShader(pixelShader, nullptr, 0);
	}
}