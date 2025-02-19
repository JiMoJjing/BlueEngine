#pragma once

#include "Core/Type.h"
#include <d3d11.h>
#include <string>
#include <memory>

namespace Blue
{
	// �ؽ�ó ������ �о ������ ����ü.
	struct TextureData
	{
		TextureData() = default;
		~TextureData()
		{
			// ���� ���ҽ� ����.
			free(data);
			data = nullptr;

			// DX ���ҽ� ����.
			if (shaderResourceView)
			{
				shaderResourceView->Release();
				shaderResourceView = nullptr;
			}

			if (samplerState)
			{
				samplerState->Release();
				samplerState = nullptr;
			}
		}

		// �ؽ�ó ���� ������.
		int32 width = 0;
		int32 height = 0;
		int32 channelCount = 0;
		void* data = nullptr;

		// DX ���ҽ�.
		ID3D11ShaderResourceView* shaderResourceView = nullptr;

		// ���ø��� ��� ����.
		ID3D11SamplerState* samplerState = nullptr;
	};

	// �ؽ�ó Ŭ����
	class Texture
	{
		// ���ε� �� ���̴� ������.
		enum class BindType
		{
			VertexShader,
			PixelShader
		};

	public:
		Texture();
		Texture(const std::string& name, BindType bindType = BindType::PixelShader, uint32 index = 0u);
		~Texture();

		void Bind();

	private:
		void LoadTexture(const std::string& name);

	private:
		// �̹��� �̸�.
		std::string name;
		
		// �ؽ�ó ����.
		uint32 index = 0u;

		// ���ε� ���̴� Ÿ��.
		BindType bindType = BindType::PixelShader;

		// �ؽ�ó ������ (���ҽ�).
		std::unique_ptr<TextureData> textureData;
	};
}