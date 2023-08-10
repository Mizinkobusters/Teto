#pragma once

const int MINO_WIDTH = 4;
const int MINO_HEIGHT = 4;

class Mino
{
public:
	enum MINO_TYPE
	{
		MINO_TYPE_I,
		MINO_TYPE_O,
		MINO_TYPE_S,
		MINO_TYPE_Z,
		MINO_TYPE_J,
		MINO_TYPE_L,
		MINO_TYPE_T,
		MINO_TYPE_MAX,
	};

	enum MINO_ANGLE
	{
		MINO_ANGLE_0,
		MINO_ANGLE_90,
		MINO_ANGLE_180,
		MINO_ANGLE_270,
		MINO_ANGLE_MAX,
	};

	int GetMinoShape(MINO_TYPE type, MINO_ANGLE angle);

private:
	int mMinoShapes[MINO_TYPE_MAX][MINO_ANGLE_MAX][MINO_WIDTH][MINO_HEIGHT];
};