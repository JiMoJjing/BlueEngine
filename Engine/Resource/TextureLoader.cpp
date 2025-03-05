#include "TextureLoader.h"
#include "Render/Texture.h"

namespace Blue
{
	TextureLoader* TextureLoader::instance = nullptr;

	TextureLoader::TextureLoader()
	{
		instance = this;
	}

	void TextureLoader::Load(const std::string& name, std::weak_ptr<Texture>& outTexture)
	{
		// 있으면 찾아서 반환.
		auto find = textures.find(name);
		if (find != textures.end())
		{
			outTexture = find->second;
			return;
		}

		// 없으면 생성해서 반환.
		std::shared_ptr<Texture> newTexture = std::make_shared<Texture>(name);
		textures.insert(std::make_pair(name, newTexture));
		outTexture = newTexture;
	}

	TextureLoader& TextureLoader::Get()
	{
		return *instance;
	}
}