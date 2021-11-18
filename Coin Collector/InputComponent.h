#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include "Game.h"
#include "Entity.h"
#include "Components.h"

class InputComponent : public Component
{
public:
	MovementComponent* movement;
	ImageComponent* image;

	void Init() override
	{
		movement = &entity->GetComponent<MovementComponent>();
		image = &entity->GetComponent<ImageComponent>();
	}

	void Update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				movement->SetYVelocity(-1);
				image->SetDirection("Up");
				break;
			case SDLK_s:
				movement->SetYVelocity(1);
				image->SetDirection("Down");
				break;
			case SDLK_a:
				movement->SetXVelocity(-1);
				image->SetDirection("Left");
				break;
			case SDLK_d:
				movement->SetXVelocity(1);
				image->SetDirection("Right");
				break;
			default:
				break;

			}
		}

		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				movement->SetYVelocity(0);
				break;
			case SDLK_s:
				movement->SetYVelocity(0);
				break;
			case SDLK_a:
				movement->SetXVelocity(0);
				break;
			case SDLK_d:
				movement->SetXVelocity(0);
				break;
			default:
				break;

			}
		}
	}
};

#endif
