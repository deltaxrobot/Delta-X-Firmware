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
// Constants.h

#ifndef _CONSTANTS_h
#define _CONSTANTS_h

#include "config.h"
#include "enum.h"
#include "Geometry.h"

typedef struct
{
	float X;
	float Y;
	float Z;
}Point;

typedef struct
{
	float Theta1;
	float Theta2;
	float Theta3;
}Angle;

class Constants
{
public:
	void	init();
	void ResetData();

	//

	float	RD_F;
	float	RD_E;
	float	RD_RF;
	float	RD_RE;

	float	RD_W;
	float	RD_U;
	float	RD_V;

	float	MOVING_AREA_X;
	float	MOVING_AREA_Y;
	float	MOVING_AREA_Z;

	float	MOVING_AREA_LARGEST_DIAMETER;
	//

	float	Velocity;			//mm/s
	float	Acceleration;		//mm/s^2

	float MovingHomeSpeed;

	float BeginEndVelocity;

	float EntryVelocity;
	float ExitVelocity;

	bool IsMoveWithTheAbsoluteCoordinates;

	bool IsExecutedGcode;

	END_EFFECTOR End_Effector;

	float MMPerLinearSegment;
	float MMPerArcSegment;

	Point CurrentPoint;
	Point DesiredPoint;
	Point HomePosition;

	Angle CurrentAngle;

	float ZOffset;

	float ExtrustionPosition;

	int WPosition;
private:

};

extern Constants Data;

#endif

