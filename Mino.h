#pragma once

static const int MINO_WIDTH = 4;
static const int MINO_HEIGHT = 4;

struct Mino
{
	 int mMino[MINO_WIDTH][MINO_HEIGHT];
};

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

static const Mino mMinoShapes[MINO_TYPE_MAX][MINO_ANGLE_MAX] =
{
	// MINO_TYPE_I
	{	
		// MINO_ANGLE_0
		{
			0, 1, 0, 0,
			0, 1, 0, 0,
			0, 1, 0, 0,
			0, 1, 0, 0,
		},
		// MINO_ANGLE_90
		{		
			0, 0, 0, 0,
			0, 0, 0, 0,
			1, 1, 1, 1,
			0, 0, 0, 0,
		},
		// MINO_ANGLE_180
		{
			0, 0, 1, 0,
			0, 0, 1, 0,
			0, 0, 1, 0,
			0, 0, 1, 0,
		},
		// MINO_ANGLE_270
		{
			0, 0, 0, 0,
			1, 1, 1, 1,
			0, 0, 0, 0,
			0, 0, 0, 0,
		}
	},

	// MINO_TYPE_O
	{
		// MINO_ANGLE_0
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
		},
		// MINO_ANGLE_90
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
		},
		// MINO_ANGLE_180
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
		},
		// MINO_ANGLE_270
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
		}
	},

	// MINO_TYPE_S
	{
		// MINO_ANGLE_0
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			1, 1, 0, 0,
			0, 0, 0, 0,
		},
		// MINO_ANGLE_90
		{
			0, 0, 0, 0,
			0, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 1, 0,
		},
		// MINO_ANGLE_180
		{
			0, 0, 0, 0,
			0, 0, 1, 1,
			0, 1, 1, 0,
			0, 0, 0, 0,
		},
		// MINO_ANGLE_270
		{
			0, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 1, 0,
			0, 0, 0, 0,
		}
	},

	// MINO_TYPE_Z
	{
		// MINO_ANGLE_0
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 0, 1, 1,
			0, 0, 0, 0,
		},
		// MINO_ANGLE_90
		{
			0, 0, 1, 0,
			0, 1, 1, 0,
			0, 1, 0, 0,
			0, 0, 0, 0,
		},
		// MINO_ANGLE_180
		{
			0, 0, 0, 0,
			1, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
		},
		// MINO_ANGLE_270
		{
			0, 0, 0, 0,
			0, 0, 1, 0,
			0, 1, 1, 0,
			0, 1, 0, 0,
		}
	},

	// MINO_TYPE_J
	{
		// MINO_ANGLE_0
		{
			0, 0, 1, 0,
			0, 0, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
		},
		// MINO_ANGLE_90
		{
			0, 0, 0, 0,
			1, 1, 1, 0,
			0, 0, 1, 0,
			0, 0, 0, 0,
		},
		// MINO_ANGLE_180
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 0, 0,
			0, 1, 0, 0,
		},
		// MINO_ANGLE_270
		{
			0, 0, 0, 0,
			0, 1, 0, 0,
			0, 1, 1, 1,
			0, 0, 0, 0,
		}
	},

	// MINO_TYPE_L
	{
		// MINO_ANGLE_0
		{
			0, 1, 0, 0,
			0, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
		},
		// MINO_ANGLE_90
		{
			0, 0, 0, 0,
			0, 0, 1, 0,
			1, 1, 1, 0,
			0, 0, 0, 0,
		},
		// MINO_ANGLE_180
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 0, 1, 0,
			0, 0, 1, 0,
		},
		// MINO_ANGLE_270
		{
			0, 0, 0, 0,
			0, 1, 1, 1,
			0, 1, 0, 0,
			0, 0, 0, 0,
		}
	},

	// MINO_TYPE_T
	{
		// MINO_ANGLE_0
		{
			0, 0, 0, 0,
			1, 1, 1, 0,
			0, 1, 0, 0,
			0, 0, 0, 0,
		},
		// MINO_ANGLE_90
		{
			0, 0, 0, 0,
			0, 1, 0, 0,
			0, 1, 1, 0,
			0, 1, 0, 0,
		},
		// MINO_ANGLE_180
		{
			0, 0, 0, 0,
			0, 0, 1, 0,
			0, 1, 1, 1,
			0, 0, 0, 0,
		},
		// MINO_ANGLE_270
		{
			0, 0, 1, 0,
			0, 1, 1, 0,
			0, 0, 1, 0,
			0, 0, 0, 0,
		}
	}
};