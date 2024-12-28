/**
 * 第46行的變數是用來選擇末端效應器種類
 * 總共有4種，定義再enum.h中
 * typedef enum
 *	{
 *		USE_CLIP,
 *		USE_PEN,
 *		USE_LASER,
 *		USE_CUSTOM
 *	}END_EFFECTOR;
 *
 */

#include "Constants.h"

void Constants::init()
{
	RD_F = (float)DEFAULT_RD_F;
	RD_E = (float)DEFAULT_RD_E;
	RD_RF = (float)DEFAULT_RD_RF;
	RD_RE = (float)DEFAULT_RD_RE;

	RD_W = (float)DEFAULT_RD_W;
	RD_U = (float)DEFAULT_RD_U;
	RD_V = (float)DEFAULT_RD_V;

	MOVING_AREA_X = (float)DEFAULT_MOVING_AREA_X;
	MOVING_AREA_Y = (float)DEFAULT_MOVING_AREA_Y;
	MOVING_AREA_Z = (float)DEFAULT_MOVING_AREA_Z;

	MOVING_AREA_LARGEST_DIAMETER = (float)DEFAULT_MOVING_AREA_LARGEST_DIAMETER;

	Velocity = (float)DEFAULT_VELOCITY;			//mm/s
	Acceleration = (float)DEFAULT_ACCELERATION;
	
	MovingHomeSpeed = (float)DEFAULT_MOVING_HOME_SPEED;

	BeginEndVelocity = (float)DEFAULT_BEGIN_VELOCITY;

	EntryVelocity = (float)DEFAULT_ENTRY_VELOCITY;
	ExitVelocity = (float)DEFAULT_EXIT_VELOCITY;

	IsMoveWithTheAbsoluteCoordinates = true;
	IsExecutedGcode = false;

	End_Effector = USE_PEN; //! 末端效應器的選擇

	MMPerLinearSegment = (float)MM_PER_LINEAR_SEGMENT;

	MMPerArcSegment = (float)MM_PER_ARC_SEGMENT;
}

void Constants::ResetData()
{
	init();
}


Constants Data;

