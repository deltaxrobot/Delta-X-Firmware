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

#include "DeltaKinematics.h"

void DeltaKinematicsClass::init()
{
	_y0_ = 0.5 * tan30 * Data.RD_E;
	_y1_ = -0.5 * tan30 * Data.RD_F;
	RD_RF_Pow2 = Data.RD_RF*Data.RD_RF;
	RD_RE_Pow2 = Data.RD_RE*Data.RD_RE;
}

bool DeltaKinematicsClass::ForwardKinematicsCalculations(Angle angleposition, Point &point)
{
	float theta1 = DEG_TO_RAD * angleposition.Theta1;
	float theta2 = DEG_TO_RAD * angleposition.Theta2;
	float theta3 = DEG_TO_RAD * angleposition.Theta3;

	float t = (Data.RD_F - Data.RD_E) * tan30 / 2.0;

	float y1 = -(t + Data.RD_RF * cos(theta1));
	float z1 = -Data.RD_RF * sin(theta1);

	float y2 = (t + Data.RD_RF * cos(theta2))*sin30;
	float x2 = y2 * tan60;
	float z2 = -Data.RD_RF * sin(theta2);

	float y3 = (t + Data.RD_RF * cos(theta3))*sin30;
	float x3 = -y3 * tan60;
	float z3 = -Data.RD_RF * sin(theta3);

	float dnm = (y2 - y1)*x3 - (y3 - y1)*x2;

	float w1 = y1 * y1 + z1 * z1;
	float w2 = x2 * x2 + y2 * y2 + z2 * z2;
	float w3 = x3 * x3 + y3 * y3 + z3 * z3;

	// x = (a1*z + b1)/dnm
	float a1 = (z2 - z1)*(y3 - y1) - (z3 - z1)*(y2 - y1);
	float b1 = -((w2 - w1)*(y3 - y1) - (w3 - w1)*(y2 - y1)) / 2.0;

	// y = (a2*z + b2)/dnm;
	float a2 = -(z2 - z1)*x3 + (z3 - z1)*x2;
	float b2 = ((w2 - w1)*x3 - (w3 - w1)*x2) / 2.0;

	// a*z^2 + b*z + c = 0
	float a = a1 * a1 + a2 * a2 + dnm * dnm;
	float b = 2 * (a1*b1 + a2 * (b2 - y1 * dnm) - z1 * dnm*dnm);
	float c = (b2 - y1 * dnm)*(b2 - y1 * dnm) + b1 * b1 + dnm * dnm*(z1*z1 - Data.RD_RE * Data.RD_RE);

	// discriminant
	float d = b * b - (float)4.0*a*c;
	if (d < 0) return false;

	point.Z = -(float)0.5*(b + sqrt(d)) / a;
	point.X = (a1*point.Z + b1) / dnm;
	point.Y = (a2*point.Z + b2) / dnm;

	return true;
}

bool DeltaKinematicsClass::AngleThetaCalculations(float x0, float y0, float z0, float &theta)
{
	//float y1 = -0.5 * tan30 * Data.RD_F;
	//y0 -= 0.5 * tan30 * Data.RD_E;
	float y1 = _y1_;
	y0 -= _y0_;

	// z = a + b*y
	//float a = (x0*x0 + y0 * y0 + z0 * z0 + Data.RD_RF*Data.RD_RF - Data.RD_RE*Data.RD_RE - y1 * y1) / (2.0*z0);
	float a = (x0*x0 + y0 * y0 + z0 * z0 + RD_RF_Pow2 - RD_RE_Pow2 - y1 * y1) / (2.0*z0);
	float b = (y1 - y0) / z0;

	// discriminant
	//float d = -(a + b * y1)*(a + b * y1) + Data.RD_RF* (b*b*Data.RD_RF + Data.RD_RF);
	float d = -(a + b * y1)*(a + b * y1) + b*b*RD_RF_Pow2 + RD_RF_Pow2;

	if (d < 0) return false;

	float yj = (y1 - a * b - sqrt(d)) / (b*b + 1.0);
	float zj = a + b * yj;

	theta = atan(-zj / (y1 - yj)) * RAD_TO_DEG + ((yj > y1) ? 180.0 : 0.0);

	return true;
}

bool DeltaKinematicsClass::InverseKinematicsCalculations(Point point, Angle &angleposition)
{	
	if (!AngleThetaCalculations(point.X, point.Y, point.Z, angleposition.Theta1))
	{
		return false;
	}
	if (!AngleThetaCalculations(point.X * cos120 + point.Y * sin120, point.Y * cos120 - point.X * sin120, point.Z, angleposition.Theta2))
	{
		return false;
	}
	if (!AngleThetaCalculations(point.X * cos120 - point.Y * sin120, point.Y * cos120 + point.X * sin120, point.Z, angleposition.Theta3))
	{
		return false;
	}
	return true;
}

DeltaKinematicsClass DeltaKinematics;

