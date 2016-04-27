#pragma once

#include "CommonIncludes.h"
#include <map>
#include <exception>

#include "SDL_image.h"

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	void initTextures();
	void loadTextureList(SDL_Renderer * ren);

	void cleanup();

	SDL_Texture * getTexture(std::string name);

private:
	std::map<std::string, SDL_Texture *> textureMap;
};

