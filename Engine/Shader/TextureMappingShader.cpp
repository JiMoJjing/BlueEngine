#include "TextureMappingShader.h"
#include "Render/Texture.h"

namespace Blue
{
	TextureMappingShader::TextureMappingShader()
		: Shader(L"Default")
	{
	}
	TextureMappingShader::TextureMappingShader(const std::string& textureName)
		: Shader(L"Default")
	{
		texture = std::make_unique<Texture>(textureName);
	}

	TextureMappingShader::TextureMappingShader(const std::wstring& name, const std::string& textureName)
		: Shader(name)
	{
		texture = std::make_unique<Texture>(textureName);
	}

	void TextureMappingShader::Bind()
	{
		Shader::Bind();

		if (texture)
		{
			texture->Bind();
		}
	}
}