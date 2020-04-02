/**
 * Delta X Firmware
 * Copyright (c) 2020 DeltaXFirmware [https://github.com/deltaxrobot/Delta-X-Firmware]
 *
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

	End_Effector = USE_VACUUM;

	MMPerLinearSegment = (float)MM_PER_LINEAR_SEGMENT;

	MMPerArcSegment = (float)MM_PER_ARC_SEGMENT;
}

void Constants::ResetData()
{
	init();
}


Constants Data;

