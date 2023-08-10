#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <vector>
#include <string>
#include <unordered_map>

const int TETO_SIZE = 16;

const int WINDOW_POS_X = 100;
const int WINDOW_POS_Y = 100;
const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

const int STAGE_WIDTH = 10;
const int STAGE_HEIGHT = 20;

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();
	void LoadData();
	void UnloadData();

	SDL_Texture* GetTexture(const std::string& fileName);

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	Uint32 mTicksCount;
	bool mIsRunning;

	int mStage[STAGE_WIDTH][STAGE_HEIGHT];

	std::unordered_map<std::string, SDL_Texture*> mTextures;
};