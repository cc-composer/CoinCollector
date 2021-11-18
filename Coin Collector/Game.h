#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

using std::string;

class Game
{
public:
	Game() = default;
	~Game() = default;

	void Init(const char* title, int xPosition, int yPosition, int width, int height);

	void Input();
	void Update();
	void Render();

	void Clean();

	bool Running();
	bool GameIsWon();

	//Game Events
	void CheckForCoinCollection();
	bool IsColliding(SDL_Rect player, SDL_Rect coin);
	bool CheckForWin();

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static bool isRunning;
	static bool isCoinCollected[4];

private:
	bool isGameWon;
	int count;
	SDL_Window* window;
};

#endif