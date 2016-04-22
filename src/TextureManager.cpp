#include "TextureManager.h"



TextureManager::TextureManager()
{
	// TODO: 
}


TextureManager::~TextureManager()
{
	// TODO: Make sure we've cleaned up
	// Track cleanup with a variable?
}

void TextureManager::initTextures()
{
	// TODO: 
}

void TextureManager::loadTextureList(SDL_Renderer * ren)
{
	for each (auto pair in textureList)
	{
		
		SDL_Surface* surface = IMG_Load(pair.first.c_str());
		if (surface == nullptr) {
			std::cout << "SDL IMG_Load Error: " << SDL_GetError() << std::endl;
			//cleanExit(1); TODO: 
		}

		SDL_Texture * tex = SDL_CreateTextureFromSurface(ren, surface);
		SDL_FreeSurface(surface);
		if (tex == nullptr) {
			std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
			//cleanExit(1); TODO: 
		}

		textureMap.insert(make_pair(pair.second, tex));
	}
}

SDL_Texture * TextureManager::getTexture(std::string name)
{
	SDL_Texture * tex;
	try
	{
		tex = textureMap.at(name);
	}
	catch (const std::out_of_range& e) //Tried to load a texture not in TextureList
	{
		std::cout << "ERROR: Tried to load texture " + name + " which didn't exist.";
	}
	if (tex == nullptr)
	{
		tex = textureMap.at("errortex"); // errortex will always be loaded. Program will quit on loadTextures() if it can't be found.
	}
}
