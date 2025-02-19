#pragma once

#include "Shader.h"
#include <memory>

namespace Blue
{
	class TextureMappingShader : public Shader
	{
	public:
		TextureMappingShader();
		TextureMappingShader(const std::string& textureName = "");
		TextureMappingShader(const std::wstring& name = L"Default", const std::string& textureName = "");

		virtual void Bind() override;
	private:
		// 텍스쳐 리소스.
		std::unique_ptr<class Texture> texture;
	};
}