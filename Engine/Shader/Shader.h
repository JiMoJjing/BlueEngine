#pragma once

#include <string>
#include <d3d11.h>

namespace Blue
{
	class Shader
	{
	public:
		Shader(const std::wstring& name = L"Default");
		virtual ~Shader();

		// GPU에 셰이더 객체를 연결(바인딩) 하는 함수.
		virtual void Bind();

	protected:
		// 셰이더 이름.
		std::wstring name;

		// 인풋 레이아웃.
		ID3D11InputLayout* inputLayout = nullptr;

		// 정점 셰이더 객체, 버퍼.
		ID3D11VertexShader* vertexShader = nullptr;
		ID3DBlob* vertexShaderBuffer = nullptr;

		// 픽셀 셰이더 객체, 버퍼.
		ID3D11PixelShader* pixelShader = nullptr;
		ID3DBlob* pixelShaderBuffer = nullptr;
	};
}