#ifndef TEXTURE_H
#define TEXTURE_H

#include "Game.h"

struct Texture
{
	static SDL_Texture* LoadTexture(const char* fileName)
	{
		SDL_Surface* surface = IMG_Load(fileName);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
		SDL_FreeSurface(surface);

		return texture;
	}

	static void DrawTexture(SDL_Texture* texture, SDL_Rect source, SDL_Rect destination)
	{
		SDL_RenderCopy(Game::renderer, texture, &source, &destination);
	}
};

#endif
