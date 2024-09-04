#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


class Map {
public:
	Map();
	

	void LoadMap(int arr[20][25]);
	void DrawMap();
	void Updater();
private:
	SDL_Rect src[200], dest[200];
	SDL_Texture* snake;
	SDL_Texture* bkg;
	SDL_Texture* treat;
	SDL_Texture* reset;
	SDL_Texture* resethover;
	SDL_Texture* ulost;
	SDL_Texture* lineleft;
	SDL_Texture* lineup;
	int map[20][25];
};