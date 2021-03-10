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

#include "Tool.h"

void ToolClass::init()
{
}

Point ToolClass::ConvertToPoint(float xPos, float yPos, float zPos)
{
	if (Data.IsMoveWithTheAbsoluteCoordinates == false)
	{
		xPos = xPos + Data.CurrentPoint.X;
		yPos = yPos + Data.CurrentPoint.Y;
		zPos = zPos + Data.CurrentPoint.Z;
	}
	else
	{
		if (Data.ZOffset < 0 && zPos != Data.CurrentPoint.Z)
		{
			zPos = zPos + Data.ZOffset;
		}
	}

	Point pointBuffer;
	pointBuffer.X = xPos;
	pointBuffer.Y = yPos;
	pointBuffer.Z = zPos;

	return pointBuffer;
}

bool ToolClass::CheckingDesiredPoint(Point point)
{
	if (point.Z < Data.RD_W - Data.MOVING_AREA_Z)
		return false;

	if (sqrt(pow(point.X, 2) + pow(point.Y, 2)) > Data.MOVING_AREA_LARGEST_DIAMETER)
		return false;

	Data.DesiredPoint = point;

	return true;
}

bool ToolClass::CheckingDesiredAngle(Angle angle)
{
	if (angle.Theta1 < THETA1_HOME_POSITION)
		return false;
	if (angle.Theta2 < THETA2_HOME_POSITION)
		return false;
	if (angle.Theta3 < THETA3_HOME_POSITION)
		return false;
	return true;
}

Point ToolClass::GetPointInLine(Point currentP, Point desiredP, float t)
{
	Point buffer;

	buffer.X = currentP.X - ((currentP.X - desiredP.X) * t);
	buffer.Y = currentP.Y - ((currentP.Y - desiredP.Y) * t);
	buffer.Z = currentP.Z - ((currentP.Z - desiredP.Z) * t);

	return buffer;
}

Point ToolClass::GetPointInCircle(float ox, float oy, float radius, float angle)
{
	Point buffer;
	buffer.X = ox + radius * cosf(angle);
	buffer.Y = oy + radius * sinf(angle);
	buffer.Z = Data.CurrentPoint.Z;
	return buffer;
}

bool ToolClass::CheckFuplicatione(Point point1, Point point2)
{
	float x_Offset = point1.X - point2.X;
	float y_Offset = point1.Y - point2.Y;
	float z_Offset = point1.Z - point2.Z;

	if (x_Offset == 0 && y_Offset == 0 && z_Offset == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float ToolClass::CalDistance2Point(Point point1, Point point2)
{
	float x_Offset = point1.X - point2.X;
	float y_Offset = point1.Y - point2.Y;
	float z_Offset = point1.Z - point2.Z;

	float distance = sqrt(pow(x_Offset, 2) + pow(y_Offset, 2) + pow(z_Offset, 2));

	if (distance < 0.2 && distance > -0.2)
		distance = 0;

	return distance;
}

bool ToolClass::Wait()
{
	if (Temperature.IsWait == true)
	{
		if (Temperature.WaitForHotendTemperature() == true)
		{
			Temperature.IsWait = false;
			Data.IsExecutedGcode = true;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (millis() - LastTime < TimeDelay)
		{
			return false;
		}
		else
		{
			Data.IsExecutedGcode = true;
			return true;
		}
	}
}

void ToolClass::SetTimeDelay(float timeDelay)
{
	TimeDelay = timeDelay;
	LastTime = millis();
	IsWait = true;
}

ToolClass Tool;
