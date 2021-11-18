#include <memory>
#include <thread>

#include "Game.h"

std::unique_ptr<Game> game = std::make_unique<Game>();
bool delaySet = false;

int main(int argc, char* argv[])
{
	const int frameDelay = 1000 / 60;

	Uint32 frameStart;
	int frameTime;

	game->Init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640);

	while (game->Running())
	{
		frameStart = SDL_GetTicks();

		game->Input();
		game->Update();
		game->Render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}

	game->Clean();

	return 0;
}