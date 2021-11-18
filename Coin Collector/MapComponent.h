#ifndef MAP_COMPONENT_H
#define MAP_COMPONENT_H

#include "Entity.h"
#include "MovementComponent.h"
#include "ImageComponent.h"

#include <assert.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <SDL.h>

using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

class MapComponent : public Component
{
public:
	MapComponent(const char* tileSet, string mapFile)
	{
		if (tileSet == nullptr)
		{
			SDL_Log("No tile set to load.");
			return;
		}

		texture = Texture::LoadTexture(tileSet);

		if (mapFile.empty())
		{
			SDL_Log("No map file to load.");
			return;
		}

		SetMap(mapFile);

		source.x = 0;
		source.y = 0;
		source.w = 32;
		source.h = 32;

		destination.x = 0;
		destination.y = 0;
		destination.w = 32;
		destination.h = 32;
	}

	~MapComponent()
	{
		SDL_DestroyTexture(texture);
	}

	vector<int> ParseLine(string line)
	{
		istringstream streamLine(line);
		int n;
		char c;
		vector<int> row;

		while (streamLine >> n >> c)
			row.push_back(n);

		return row;
	}
	
	void Draw() override
	{
		for (int column = 0; column < map.size(); column++)
		{
			for (int row = 0; row < map[column].size(); row++)
			{
				switch (map[column][row])
				{
				case 0:
					source.x = 0;
					break;
				case 1:
					source.x = 32;
					break;
				case 2:
					source.x = 64;
					break;
				default:
					source.x = 0;
					break;
				}

				destination.x = row * 32;
				destination.y = column * 32;

				Texture::DrawTexture(texture, source, destination);
			}
		}
	}
	
	void SetMap(string fileName)
	{
		ifstream inFile(fileName);
		if (inFile)
		{
			string line;
			while (getline(inFile, line))
			{	
				vector<int> row = ParseLine(line);
				map.push_back(row);
			}
		}
	}

private:
	SDL_Texture* texture;
	SDL_Rect source;
	SDL_Rect destination;

	int xPosition, yPosition;
	vector<vector<int>> map;
};

#endif
