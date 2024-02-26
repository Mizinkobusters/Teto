#include "Game.h"
#include <vector>
#include <random>
#include <string>
#include <iostream>
#include <time.h>
#include <random>

int g_mino_type = 0;
int g_mino_angle = 0;

Game::Game()
	:mWindow(nullptr)
	, mRenderer(nullptr)
	, mFont(nullptr)
	, mTicksCount(0)
	, mIsRunning(true)
	, mAutoDownTimer(0.0f)
	, mIsGameOver(false)
	, mScore(0)
	, mLines(0)
{

}

bool Game::Initialize()
{
	// SDL èâä˙âª
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Unenable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Teto v.1.0",
		WINDOW_POS_X,
		WINDOW_POS_Y,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		0
	);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_Image: %s", SDL_GetError());
		return false;
	}

	if (TTF_Init() < 0)
	{
		SDL_Log("Unable to initialize TTF_Font: %s", TTF_GetError());
		return false;
	}
	mFont = TTF_OpenFont("Fonts/Press_Start_2P/PressStart2P-Regular.ttf", 24);
	if (!mFont)
	{
		SDL_Log("Failed to open TTF File: %s", TTF_GetError());
		return false;
	}

	InitGame();
	mCurrentMino = GetNextMino();
	UpdateCurrentMino();

	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown()
{
	TTF_CloseFont(mFont);
	TTF_Quit();
	IMG_Quit();
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

void Game::ProcessInput()
{
	SDL_Event event;
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		case SDL_KEYDOWN:
			if (keyState[SDL_SCANCODE_SPACE])
			{
				InitGame();
				mCurrentMino = GetNextMino();
				UpdateCurrentMino();
			}
			if (mIsGameOver)
			{
				break;
			}
			if (keyState[SDL_SCANCODE_DOWN])
			{
				mAutoDownTimer = TIMER_INTERVAL;
				if (!CheckCollideBottom())
				{
					RemoveOldMino();
					mCurrentPos.y++;
				}
				else
				{
					UpdateOldMino();
					ResetMinoPos();
					mCurrentMino = GetNextMino();
					mIsGameOver = CheckGameOver();
				}
			}
			else if (keyState[SDL_SCANCODE_LEFT])
			{
				if (!CheckCollideLeft())
				{
					RemoveOldMino();
					mCurrentPos.x--;
				}
				else
				{
					if (CheckCollideBottom())
					{
						mAutoDownTimer = TIMER_INTERVAL;
						UpdateOldMino();
						ResetMinoPos();
						mCurrentMino = GetNextMino();
						mIsGameOver = CheckGameOver();
					}
				}
			}
			else if (keyState[SDL_SCANCODE_RIGHT])
			{
				if (!CheckCollideRight())
				{
					RemoveOldMino();
					mCurrentPos.x++;
				}
				else
				{
					if (CheckCollideBottom())
					{
						mAutoDownTimer = TIMER_INTERVAL;
						UpdateOldMino();
						ResetMinoPos();
						mCurrentMino = GetNextMino();
						mIsGameOver = CheckGameOver();
					}
				}
			}
			else if (keyState[SDL_SCANCODE_UP])
			{
				if (CheckAvailableRotate())
				{
					RemoveOldMino();
					if (g_mino_angle == MINO_ANGLE_270)
					{
						g_mino_angle = MINO_ANGLE_0;
					}
					else
					{
						g_mino_angle++;
					}
					mCurrentMino = mMinoShapes[g_mino_type][g_mino_angle];
				}
			}
			break;
		default:
			break;
		}
	}

	if (keyState[SDL_SCANCODE_ESCAPE])
	{		
		mIsRunning = false;
	}
}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	if (mIsGameOver)
	{
		return;
	}

	UpdateCurrentMino();
	if (mAutoDownTimer <= 0.0f)
	{
		mAutoDownTimer = TIMER_INTERVAL;
		if (CheckCollideBottom())
		{
			UpdateOldMino();
			ResetMinoPos();
			mCurrentMino = GetNextMino();
			mIsGameOver = CheckGameOver();
		}
		else
		{
			RemoveOldMino();
			mCurrentPos.y++;
		}
	}
	else
	{
		mAutoDownTimer -= deltaTime;
	}
	CheckLines();
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

	SDL_Rect teto;

	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			if (mStage[y + 4][x + 4] != ENone)
			{
				teto.x = x * (TETO_SIZE + 1);
				teto.y = y * (TETO_SIZE + 1) + SCORE_BOARD;
				teto.w = TETO_SIZE;
				teto.h = TETO_SIZE;

				SDL_RenderFillRect(mRenderer, &teto);
			}
		}
	}

	char buff[64];
	snprintf(buff, sizeof(buff), "LINES: %d", mLines);
	DrawString(mRenderer, mFont, buff, 0, 10);
	snprintf(buff, sizeof(buff), "SCORE: %d", mScore);
	DrawString(mRenderer, mFont, buff, 0, 40);
	if (mIsGameOver)
	{
		DrawString(mRenderer, mFont, ("GAME OVER!"), 0, 70);	}

	SDL_RenderPresent(mRenderer);
}

void Game::DrawString(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y)
{
	SDL_Surface* surface = TTF_RenderUTF8_Blended(mFont, text, { 255, 255, 255, 255 });
	SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
	SDL_FreeSurface(surface);

	int iw, ih;
	SDL_QueryTexture(texture, NULL, NULL, &iw, &ih);

	SDL_Rect txtRect = { 0,0,iw,ih };
	SDL_Rect pasteRect = { x,y,iw,ih };
	SDL_RenderCopy(renderer, texture, &txtRect, &pasteRect);
}

void Game::InitGame()
{
	// ÉQÅ[ÉÄÇèâä˙âª
	for (int y = 0; y < STAGE_HEIGHT + 8; y++)
	{
		for (int x = 0; x < STAGE_WIDTH + 8; x++)
		{
			mStage[y][x] = ENone;
		}
	}

	for (int i = 0; i < STAGE_HEIGHT + 8; i++) 
	{
		mStage[i][3] = EWall;
		mStage[i][STAGE_WIDTH + 4] = EWall;
	}

	for (int i = 0; i < STAGE_WIDTH + 8; i++)
	{
		mStage[STAGE_HEIGHT + 4][i] = EWall;
	}
	ResetMinoPos();
	mCurrentMino = {};
	mAutoDownTimer = TIMER_INTERVAL;
	mIsGameOver = false;

	mScore = 0;
	mLines = 0;
}

Mino Game::GetNextMino()
{
	srand((unsigned int)time(NULL));
	g_mino_type = rand() % MINO_TYPE_MAX;
	g_mino_angle = rand() % MINO_ANGLE_MAX;
	return mMinoShapes[g_mino_type][g_mino_angle];
}

void Game::UpdateCurrentMino()
{
	for (int y = 0; y < MINO_HEIGHT; y++)
	{
		for (int x = 0; x < MINO_WIDTH; x++)
		{
			if (mCurrentMino.mMino[y][x] != ENone)
			{
				mStage[mCurrentPos.y + y][mCurrentPos.x + x] = mCurrentMino.mMino[y][x];
			}
		}
	}
}

void Game::UpdateOldMino()
{
	for (int y = 0; y < STAGE_HEIGHT + 8; y++)
	{
		for (int x = 0; x < STAGE_WIDTH + 8; x++)
		{
			if (mStage[y][x] == ECurrent)
			{
				mStage[y][x] = EFixed;
			}
		}
	}
}

void Game::RemoveOldMino()
{
	for (int y = 0; y < STAGE_HEIGHT + 8; y++)
	{
		for (int x = 0; x < STAGE_WIDTH + 8; x++)
		{
			if (mStage[y][x] == ECurrent)
			{
				mStage[y][x] = ENone;
			}
		}
	}
}

bool Game::CheckCollideLeft()
{
	for (int y = 0; y < MINO_HEIGHT; y++)
	{
		for (int x = 0; x < MINO_WIDTH; x++)
		{
			if (mStage[mCurrentPos.y + y][mCurrentPos.x + x] == ECurrent)
			{
				if (mStage[mCurrentPos.y + y][mCurrentPos.x + x - 1] != ENone)
				{
					if (mStage[mCurrentPos.y + y][mCurrentPos.x + x - 1] == ECurrent)
					{
						continue;
					}
					else
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Game::CheckCollideRight()
{
	for (int y = 0; y < MINO_HEIGHT; y++)
	{
		for (int x = 0; x < MINO_WIDTH; x++)
		{
			if (mStage[mCurrentPos.y + y][mCurrentPos.x + x] == ECurrent)
			{
				if (mStage[mCurrentPos.y + y][mCurrentPos.x + x + 1] != ENone)
				{
					if (mStage[mCurrentPos.y + y][mCurrentPos.x + x + 1] == ECurrent)
					{
						continue;
					}
					else
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Game::CheckCollideBottom()
{
	for (int y = 0; y < MINO_HEIGHT; y++)
	{
		for (int x = 0; x < MINO_WIDTH; x++)
		{
			if (mStage[mCurrentPos.y + y][mCurrentPos.x + x] == ECurrent)
			{
				if (mStage[mCurrentPos.y + y + 1][mCurrentPos.x + x] != ENone)
				{
					if (mStage[mCurrentPos.y + y + 1][mCurrentPos.x + x] == ECurrent)
					{
						continue;
					}
					else
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Game::CheckAvailableRotate()
{
	for (int y = 0; y < MINO_HEIGHT; y++)
	{
		for (int x = 0; x < MINO_WIDTH; x++)
		{
			if (mStage[mCurrentPos.y + y][mCurrentPos.x + x] != ENone)
			{
				if (mStage[mCurrentPos.y + y][mCurrentPos.x + x] == ECurrent)
				{
					continue;
				}
				else
				{
					return false;
				}
			}
		}
	}
	return true;
}

void Game::ResetMinoPos()
{
	mCurrentPos.x = 4;
	mCurrentPos.y = 4;
}

void Game::CheckLines()
{
	int lines = 0;
	for (int y = 0; y < STAGE_HEIGHT + 8; y++)
	{
		int cnt = 0;
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			if (mStage[y][x + 4] == EFixed)
			{
				cnt++;
			}
			else if (mStage[y][x + 4] == EWall)
			{
				continue;
			}
			else
			{
				break;
			}
		}
		if (cnt == STAGE_WIDTH)
		{
			MoveStageToDown(y);
			lines++;
		}
	}
	mLines += lines;
	mScore += CalcScore(lines);
}

void Game::MoveStageToDown(int y)
{
	while (y > 1)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			mStage[y][x + 4] = mStage[y - 1][x + 4];
		}
		y--;
	}
	for (int x = 0; x < STAGE_WIDTH; x++)
	{
		mStage[4][x + 4] = ENone;
	}
}

int Game::CalcScore(int score)
{
	int i = 0;
	switch (score)
	{
	case 1:
		i = 10;
		break;
	case 2:
		i = 40;
		break;
	case 3:
		i = 90;
		break;
	case 4:
		i = 160;
		break;
	default:
		i = 0;
		break;
	}
	return i;
}

bool Game::CheckGameOver()
{
	for (int y = 0; y < MINO_HEIGHT; y++)
	{
		for (int x = 0; x < MINO_WIDTH; x++)
		{
			if (mStage[4 + y][4 + x] == EFixed)
			{
				return true;
			}
		}
	}
	return false;
}