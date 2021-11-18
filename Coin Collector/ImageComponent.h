#ifndef IMAGE_COMPONENT_H
#define IMAGE_COMPONENT_H

#include "Components.h"
#include "Texture.h"

#include <SDL.h>
#include <map>
#include <string>

using std::map;
using std::string;

class ImageComponent : public Component
{
public:
	map<string, int> directions;
	int directionIndex;
	
	//Constructors
	ImageComponent(const char* fileName)
	{
		SetTexture(fileName);
	}

	ImageComponent(const char* fileName, int inWidth, int inHeight)
	{
		SetTexture(fileName);
		source.w = inWidth;
		source.h = inHeight;
	}

	ImageComponent(const char* fileName, bool animated)
	{
		isAnimated = animated;

		//Set indexes for the player's direction.
		directions.emplace("Down", 0);
		directions.emplace("Left", 1);
		directions.emplace("Right", 2);
		directions.emplace("Up", 3);
		
		SetTexture(fileName);
	}
	
	//Setters
	void SetTexture(const char* fileName) 
	{
		texture = Texture::LoadTexture(fileName);
	}
	
	void SetDirection(string index)
	{
		directionIndex = directions[index];
	}

	//Component Defaults
	void Init() override
	{
		movement = &entity->GetComponent<MovementComponent>();

		source.x = 0;
		source.y = 0;
		source.w = movement->GetWidth();
		source.h = movement->GetHeight();
	}

	void Update() override
	{
		if (isAnimated)
			source.x = source.w * static_cast<int>((SDL_GetTicks() / 100) % 4);

		source.y = directionIndex * movement->GetHeight();

		destination.x = movement->GetX();
		destination.y = movement->GetY();
		destination.w = movement->GetWidth();
		destination.h = movement->GetHeight();
	}

	void Draw() override
	{
		Texture::DrawTexture(texture, source, destination);
	}

private:
	MovementComponent* movement;
	SDL_Texture* texture;
	SDL_Rect source;
	SDL_Rect destination;

	bool isAnimated = false;
};

#endif