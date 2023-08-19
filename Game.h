#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <vector>
#include <string>
#include "Mino.h"

const int TETO_SIZE = 24;

const int STAGE_WIDTH = 10;
const int STAGE_HEIGHT = 20;

const int SCORE_BOARD = 100;

const int WINDOW_POS_X = 100;
const int WINDOW_POS_Y = 100;
const int WINDOW_WIDTH = TETO_SIZE * STAGE_WIDTH + STAGE_WIDTH;
const int WINDOW_HEIGHT = TETO_SIZE * STAGE_HEIGHT + STAGE_HEIGHT  + SCORE_BOARD;

const float TIMER_INTERVAL = 1.25f;

class Game
{
public:
	struct Vector2
	{
		int x;
		int y;
	};

	enum BLOCK_TYPE
	{
		ENone,
		ECurrent,
		EFixed,
		EWall,
	};

	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	void DrawString(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y);

	void InitGame();
	Mino GetNextMino();
	void UpdateCurrentMino();
	void UpdateOldMino();
	void RemoveOldMino();
	bool CheckCollideLeft();
	bool CheckCollideRight();
	bool CheckCollideBottom();
	bool CheckAvailableRotate();
	void ResetMinoPos();
	void CheckLines();
	void MoveStageToDown(int y);
	int CalcScore(int score);
	bool CheckGameOver();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	TTF_Font* mFont;

	Uint32 mTicksCount;
	bool mIsRunning;

	int mStage[STAGE_HEIGHT + 8][STAGE_WIDTH + 8];
	float mAutoDownTimer;
	Vector2 mCurrentPos;
	Mino mCurrentMino;
	bool mIsGameOver;

	int mScore;
	int mLines;
};