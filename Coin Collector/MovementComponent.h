#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include "Components.h"
#include <assert.h>

class MovementComponent : public Component
{
public:
	//Constructors/Destructors
	MovementComponent() : xPosition(400), yPosition(320) {}
	MovementComponent(int x, int y) : xPosition(x), yPosition(y) {}

	MovementComponent(int x, int y, int w, int h) : xPosition(x), yPosition(y)
	{
		assert(w >= 0);
		assert(h >= 0);

		width = w;
		height = h;
	}

	//Get Position/Size
	int GetX() { return xPosition; }
	int GetY() { return yPosition; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	SDL_Rect GetLocation()
	{
		SDL_Rect location;
		location.x = GetX();
		location.y = GetY();
		location.w = GetWidth();
		location.h = GetHeight();

		return location;
	}

	//Setters
	void SetScale(int sc)
	{
		assert(sc > 0);
		scale = sc;
	}

	void SetXVelocity(int xv) { xVelocity = xv; }
	void SetYVelocity(int yv) { yVelocity = yv; }

	//Component Defaults
	void Update() override
	{
		xPosition += xVelocity * speed;
		yPosition += yVelocity * speed;
	}

private:
	int xPosition, yPosition;
	int width = 130 / 4;
	int height = 194 / 4;
	int scale = 1;

	int xVelocity = 0; 
	int yVelocity = 0;
	int speed = 3;
};

#endif
