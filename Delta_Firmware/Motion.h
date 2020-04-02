
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
// Motion.h

#ifndef _MOTION_h
#define _MOTION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Constants.h"
#include "Tool.h"
#include "DeltaKinematics.h"
#include "Planner.h"
#include "Stepper.h"
#include "MultiServo.h"
//#include "GCodeReceiver.h"

class MotionClass
{
 protected:


 public:
	void init();
	void G0(float xPos, float yPos, float zPos, float ewPos);
	void G1(float xPos, float yPos, float zPos, float ewPos);
	void G2(float i, float j, float xPos, float yPos, float wPos);
	void G3(float i, float j, float xPos, float yPos, float wPos);
	void G4(float p);//Delay ms
	void G5(float i, float j, float p, float q, float x, float y, float wPos);
	void G6(float angle1, float angle2, float angle3, float distance);
	void G28();//Homing
private:
	uint16_t NumberSegment;

	bool LinearInterpolation();

	bool CircleInterpolation(float i, float j, bool clockwise);
	bool CircleInterpolation(float r, bool clockwise);

	bool Bezier4PointInterpolation(Point p1, Point p2);

	void UploadSegment(Angle angle1, Angle angle2, float distance, uint8_t index);
	void SetHomePosition();
};

extern MotionClass Motion;

#endif

