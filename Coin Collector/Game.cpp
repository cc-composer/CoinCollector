#include "Game.h"
#include "Texture.h"
#include "Components.h"

#include <vector>

using std::vector;

//Basic SDL components
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

//The game will be set to running after initialization.
bool Game::isRunning = false;

//Initialize the Component manager and add game entities.
Manager manager;
auto& map(manager.AddEntity());
auto& player(manager.AddEntity());
auto& coin1(manager.AddEntity());
auto& coin2(manager.AddEntity());
auto& coin3(manager.AddEntity());
auto& coin4(manager.AddEntity());
auto& winScreen(manager.AddEntity());

//How we check if the coin is collected
bool Game::isCoinCollected[4] = { false, false, false, false };

void Game::Init(const char* title, int xPosition, int yPosition, int width, int height)
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		SDL_Log("Subsystem initialized.");

		//Initialize Window
		window = SDL_CreateWindow(title, xPosition, yPosition, width, height, 0);
		if (window == NULL)
		{
			SDL_Log("SDL failed to create window. Error: %s", SDL_GetError());
			return;
		}

		//Initialize Renderer
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == NULL)
		{
			SDL_Log("SDL failed to create renderer. Error: %s", SDL_GetError());
			return;
		}
		
		//Fill screen with white.
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		isRunning = true;
	}

	//Initialize Map
	map.AddComponent<MapComponent>("graphics/tileset.png", "graphics/map.txt");
	
	//Initialize Player
	player.AddComponent<MovementComponent>();
	player.AddComponent<ImageComponent>("graphics/character_sprite.png", true);
	player.AddComponent<InputComponent>();

	//Initialize Coins
	coin1.AddComponent<MovementComponent>(600, 32, 32, 32);
	coin1.AddComponent<ImageComponent>("graphics/coin.png");
	coin2.AddComponent<MovementComponent>(64, 64, 32, 32);
	coin2.AddComponent<ImageComponent>("graphics/coin.png");
	coin3.AddComponent<MovementComponent>(180, 400, 32, 32);
	coin3.AddComponent<ImageComponent>("graphics/coin.png");
	coin4.AddComponent<MovementComponent>(128, 526, 32, 32);
	coin4.AddComponent<ImageComponent>("graphics/coin.png");
}

void Game::Input()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::Render()
{
	SDL_RenderClear(renderer);

	manager.Draw();

	SDL_RenderPresent(renderer);
}

void Game::Update()
{
	manager.Refresh();
	manager.Update();
	
	if (!isGameWon)
	{
		CheckForCoinCollection();
		isGameWon = CheckForWin();
	}
}

void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

bool Game::Running()
{
	return isRunning;
}

bool Game::GameIsWon()
{
	return isGameWon;
}

void Game::CheckForCoinCollection()
{
	SDL_Rect playerPos = player.GetComponent<MovementComponent>().GetLocation();	
	SDL_Rect coinPos;

	for (int i = 1; i <= 4; i++)
	{
		switch (i)
		{
		case 1:
			if (isCoinCollected[0] == false)
			{
				coinPos = coin1.GetComponent<MovementComponent>().GetLocation();
				
				if (IsColliding(playerPos, coinPos))
				{
					coin1.Destroy();
					isCoinCollected[0] = true;
				}		 
			}
				
			break;
		case 2:
			if (isCoinCollected[1] == false)
			{
				coinPos = coin2.GetComponent<MovementComponent>().GetLocation();

				if (IsColliding(playerPos, coinPos))
				{
					coin2.Destroy();
					isCoinCollected[1] = true;
				}
			}

			break;
		case 3:
			if (isCoinCollected[2] == false)
			{
				coinPos = coin3.GetComponent<MovementComponent>().GetLocation();

				if (IsColliding(playerPos, coinPos))
				{
					coin3.Destroy();
					isCoinCollected[2] = true;
				}
			}

			break;
		case 4:
			if (isCoinCollected[3] == false)
			{
				coinPos = coin4.GetComponent<MovementComponent>().GetLocation();

				if (IsColliding(playerPos, coinPos))
				{
					coin4.Destroy();
					isCoinCollected[3] = true;
				}
			}

			break;
		} //End switch
	} //End for loop
}

bool Game::IsColliding(SDL_Rect player, SDL_Rect coin)
{
	return (player.x + player.w >= coin.x &&
			coin.x + coin.w >= player.x &&
			player.y + player.h >= coin.y &&
			coin.y + coin.h >= player.y);
}

bool Game::CheckForWin()
{
	bool isWinner = true;
	
	for (bool collected : isCoinCollected)
	{
		if (collected == false)
		{
			isWinner = false;
		}
	}
	
	if (isWinner)
	{
		map.Destroy();
		player.Destroy();
		winScreen.AddComponent<MovementComponent>(0, 0, 800, 640);
		winScreen.AddComponent<ImageComponent>("graphics/winScreen.png");
	}

	return isWinner;
}
