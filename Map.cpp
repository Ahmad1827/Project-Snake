 #include "Map.h"
#include "game.h"
#include <fstream>
#include "TextureManager.h"


const Uint8* keystates = SDL_GetKeyboardState(NULL);
int keypressed[50];
int direction = 3;
int times = 0;
int len = 4, curr = 1, done = 0;
int gameover = 0;
int prevX[200], prevY[200];
int mouseX, mouseY;

int lvl1[20][25] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,1,2,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };


Map::Map()
{
	bkg = TextureManager::LoadTexture("pics\\bkgsnake.png");
	snake = TextureManager::LoadTexture("pics\\snake.png");
	treat = TextureManager::LoadTexture("pics\\treatsnake.png");
	reset = TextureManager::LoadTexture("pics\\resetsnake.png");
	resethover = TextureManager::LoadTexture("pics\\resetsnakehover.png");
	ulost = TextureManager::LoadTexture("pics\\ulostsnake.png");
	lineup = TextureManager::LoadTexture("pics\\lineupsnake.png");
	lineleft = TextureManager::LoadTexture("pics\\lineleftsnake.png");


	LoadMap(lvl1);

	

	src[1].x = src[1].y = 0;
	src[1].w = dest[1].w = 32;
	src[1].h = dest[1].h = 32;
	dest[1].x = dest[1].y = 0;

	src[2].x = src[2].y = 0;
	src[2].w = src[2].h = 32;
	dest[2].w = dest[2].h = 32;

	src[3].x = src[3].y = 0;
	src[3].w = dest[3].w = src[3].h = dest[3].h = 32;
	dest[3].x = dest[3].y = 0;

	src[4].x = src[4].y = 0;
	src[4].w = dest[4].w = 100;
	src[4].h = dest[4].h = 40;
	dest[4].x = 650;
	dest[4].y = 20;

	src[5].x = src[5].y = 0;
	src[5].w = dest[5].w = 200;
	src[5].h = dest[5].h = 80;
	dest[5].x = -300;
	dest[5].y = 280;

	src[6].x = src[6].y = 0;
	src[6].w = dest[6].w = 100;
	src[6].h = dest[6].h = 40;
	dest[6].x = -650;
	dest[6].y = 20;
	
	src[7].x = src[7].y = 0;
	src[7].w = dest[7].w = 800;
	src[7].h = dest[7].h = 3;
	dest[7].x = 0;
	dest[7].y = 0;

	src[8].x = src[8].y = 0;
	src[8].w = dest[8].w = 800;
	src[8].h = dest[8].h = 3;
	dest[8].x = 0;
	dest[8].y = 637;

	src[9].x = src[9].y = 0;
	src[9].w = dest[9].w = 3;
	src[9].h = dest[9].h = 640;
	dest[9].x = 0;
	dest[9].y = 0;

	src[10].x = src[10].y = 0;
	src[10].w = dest[10].w = 3;
	src[10].h = dest[10].h = 640;
	dest[10].x = 797;
	dest[10].y = 0;

}

void Map::Updater()
{
	SDL_GetMouseState(&mouseX, &mouseY);
	if (mouseX > 650 && mouseX<750 && mouseY>20 && mouseY < 60)
	{
		dest[6].x = 650;
		dest[4].x = -650;
	}
	else
	{
		dest[6].x = -650;
		dest[4].x = 650;
	}
	if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON_LMASK)
	{
		if (mouseX > 650 && mouseX < 750 && mouseY>20 && mouseY < 60)
		{
			len = 4;
			dest[5].x = -300;
			gameover = 0;
			direction = 3;
			LoadMap(lvl1);
		}
	}
	if(gameover==1)
	{
		dest[5].x = 300;
	}
	else if (gameover == 0)
	{
		dest[5].x = -300;
		if (keystates[SDL_SCANCODE_RIGHT])
		{
			if (direction != 3)
				direction = 1;
		}
		if (keystates[SDL_SCANCODE_DOWN])
		{
			if (direction != 4)
				direction = 2;
		}
		if (keystates[SDL_SCANCODE_LEFT])
		{
			if (direction != 1)
				direction = 3;
		}
		if (keystates[SDL_SCANCODE_UP])
		{
			if (direction != 2)
				direction = 4;
		}
		int ok = 0;
		for (int i = 0; i < 20; ++i)
		{
			for (int j = 0; j < 25; ++j)
			{
				if (map[i][j] == -1)
				{
					ok = 1;
				}
			}
		}
		if (ok == 0)
		{
			done = 1;
		}
		if (done == 1)
		{
			int randX = rand() % 25 + 1;
			int randY = rand() % 20 + 1;
			if (map[randX][randY] == 0)
			{
				map[randX][randY] = -1;
				done = 0;
			}
		}
		times += 1;
		if (times >= 5)
		{
			if (direction == 1)
			{
				for (int i = 0; i < 20; ++i)
				{
					for (int j = 0; j < 25; ++j)
					{
						if (map[i][j] != 0)
						{
							prevX[map[i][j]] = j;
							prevY[map[i][j]] = i;
						}
					}
				}
				if (prevX[1] + 1 > 24)
				{
					gameover = 1;
				}
				if (map[prevY[1]][prevX[1] + 1] == -1)
				{
					len++;
					done = 1;
				}
				else if (map[prevY[1]][prevX[1] + 1] != 0)
				{
					gameover = 1;
				}
				map[prevY[1]][prevX[1] + 1] = 1;
				for (int i = 2; i <= len; ++i)
				{
					map[prevY[i - 1]][prevX[i - 1]] = i;
				}
				map[prevY[len]][prevX[len]] = 0;
			}
			else if (direction == 2)
			{
				for (int i = 0; i < 20; ++i)
				{
					for (int j = 0; j < 25; ++j)
					{
						if (map[i][j] != 0)
						{
							prevX[map[i][j]] = j;
							prevY[map[i][j]] = i;
						}
					}
				}
				if (prevY[1] + 1 > 19)
				{
					gameover = 1;
				}
				if (map[prevY[1] + 1][prevX[1]] == -1)
				{
					len++;
					done = 1;
				}
				else if (map[prevY[1] + 1][prevX[1]] != 0)
				{
					gameover = 1;
				}
				map[prevY[1] + 1][prevX[1]] = 1;
				for (int i = 2; i <= len; ++i)
				{
					map[prevY[i - 1]][prevX[i - 1]] = i;
				}
				map[prevY[len]][prevX[len]] = 0;
			}
			else if (direction == 3)
			{
				for (int i = 0; i < 20; ++i)
				{
					for (int j = 0; j < 25; ++j)
					{
						if (map[i][j] != 0)
						{
							prevX[map[i][j]] = j;
							prevY[map[i][j]] = i;
						}
					}
				}
				if (prevX[1] - 1 < 1)
				{
					gameover = 1;
				}
				if (map[prevY[1]][prevX[1] - 1] == -1)
				{
					len++;
					done = 1;
				}
				else if (map[prevY[1]][prevX[1] - 1] != 0)
				{
					gameover = 1;
				}
				map[prevY[1]][prevX[1] - 1] = 1;
				for (int i = 2; i <= len; ++i)
				{
					map[prevY[i - 1]][prevX[i - 1]] = i;
				}
				map[prevY[len]][prevX[len]] = 0;
			}
			else if (direction == 4)
			{
				for (int i = 0; i < 20; ++i)
				{
					for (int j = 0; j < 25; ++j)
					{
						if (map[i][j] != 0)
						{
							prevX[map[i][j]] = j;
							prevY[map[i][j]] = i;
						}
					}
				}
				if (prevY[1] - 1 < 1)
				{
					gameover = 1;
				}
				if (map[prevY[1] - 1][prevX[1]] == -1)
				{
					len++;
					done = 1;
				}
				else if (map[prevY[1] - 1][prevX[1]] != 0)
				{
					gameover = 1;
				}
				map[prevY[1] - 1][prevX[1]] = 1;
				for (int i = 2; i <= len; ++i)
				{
					map[prevY[i - 1]][prevX[i - 1]] = i;
				}
				map[prevY[len]][prevX[len]] = 0;
			}
			times = 0;
		}
	}
	DrawMap();
}

void Map::LoadMap(int arr[20][25])
{
	for (int row = 0; row < 20; ++row)
	{
		for (int column = 0; column < 25; ++column)
		{
			map[row][column] = arr[row][column];
		}
	}
}

void Map::DrawMap()
{
	int type = 0;
	for (int row = 0; row < 20; ++row)
	{
		for (int column = 0; column < 25; ++column)
		{
			type = map[row][column];
			dest[1].x = column * 32;
			dest[1].y = row * 32;
			dest[2].x = column * 32;
			dest[2].y = row * 32;
			dest[3].x = column * 32;
			dest[3].y = row * 32;
			TextureManager::Draw(resethover, src[6], dest[6]);
			TextureManager::Draw(reset, src[4], dest[4]);
			TextureManager::Draw(ulost, src[5], dest[5]);
			TextureManager::Draw(lineup, src[7], dest[7]);
			TextureManager::Draw(lineup, src[8], dest[8]);
			TextureManager::Draw(lineleft, src[9], dest[9]);
			TextureManager::Draw(lineleft, src[10], dest[10]);
			switch (type)
			{
			case 0:
				TextureManager::Draw(bkg, src[1], dest[1]);
				break;
			case -1:
				TextureManager::Draw(treat, src[3], dest[3]);
				break;
			default:
				TextureManager::Draw(snake, src[2], dest[2]);
				break;
				break;
			}

		}
	}
}

