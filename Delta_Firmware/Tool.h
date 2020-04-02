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
// Tool.h

#ifndef _TOOL_h
#define _TOOL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Constants.h"
#include "Temperature.h"

class ToolClass
{
 protected:

 public:
	void init();
	Point ConvertToPoint(float xPos, float yPos, float zPos);
	bool CheckingDesiredPoint(Point point);
	bool CheckingDesiredAngle(Angle angle);
	Point GetPointInLine(Point currentP, Point desiredP, float t);
	Point GetPointInCircle(float ox, float oy, float desiredP, float angle);
	bool CheckFuplicatione(Point point1, Point point2);
	float CalDistance2Point(Point point1, Point point2);

	bool Wait();
	void SetTimeDelay(float timeDelay);
	bool IsWait;

private:
	uint32_t TimeDelay;
	uint32_t LastTime;
};

extern ToolClass Tool;

#endif

