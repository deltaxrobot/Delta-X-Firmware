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
// DeltaKinematics.h

#ifndef _DELTAKINEMATICS_h
#define _DELTAKINEMATICS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Constants.h"

using namespace std;

//trigonometric constants
const double tan30 = 1 / sqrt(3);
const double tan30x05 = 0.5 / sqrt(3);
const double tan60 = sqrt(3);
const double sin30 = 0.5;
const double cos30 = sqrt(3) / 2;
const double cos120 = -0.5;
const double sin120 = sqrt(3) / 2;

class DeltaKinematicsClass
{
 protected:


 public:
	void init();
	bool ForwardKinematicsCalculations(Angle angleposition, Point &point);
	bool InverseKinematicsCalculations(Point point, Angle &angleposition);

private:
	bool AngleThetaCalculations(float x0, float y0, float z0, float &theta);
	float _y0_;
	float _y1_;
	float RD_RF_Pow2;
	float RD_RE_Pow2;
};

extern DeltaKinematicsClass DeltaKinematics;

#endif

