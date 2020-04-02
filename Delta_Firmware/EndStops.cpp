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

#include "EndStops.h"

void EndStopsClass::init()
{
#if THETA1_ENDSTOP_INVERT != false
	pinMode(THETA1_ENDSTOP_PIN, INPUT);
#else
	pinMode(THETA1_ENDSTOP_PIN, INPUT_PULLUP);
#endif // THETA1_ENDSTOP_INVERT

#if THETA2_ENDSTOP_INVERT != false
	pinMode(THETA2_ENDSTOP_PIN, INPUT);
#else
	pinMode(THETA2_ENDSTOP_PIN, INPUT_PULLUP);
#endif // THETA1_ENDSTOP_INVERT

#if THETA3_ENDSTOP_INVERT != false
	pinMode(THETA3_ENDSTOP_PIN, INPUT);
#else
	pinMode(THETA3_ENDSTOP_PIN, INPUT_PULLUP);
#endif // THETA1_ENDSTOP_INVERT

#ifdef ENDSTOP_FOR_CHECK_Z_AREA
#if ENDSTOP_FOR_CHECK_Z_AREA_INVERT != false
	pinMode(ENDSTOP_FOR_CHECK_Z_AREA_PIN, INPUT);
#else
	pinMode(ENDSTOP_FOR_CHECK_Z_AREA_PIN, INPUT_PULLUP);
#endif // THETA1_ENDSTOP_INVERT
#endif

	//HomePhase = 0;
	ClearEndstopState();
}

void EndStopsClass::UpdateStates()
{
	if (READ(THETA1_ENDSTOP_PIN) == THETA1_ENDSTOP_INVERT)
	{
		Theta1State = true;
	}
	else
	{
		Theta1State = false;
	}

	if (READ(THETA2_ENDSTOP_PIN) == THETA2_ENDSTOP_INVERT)
	{
		Theta2State = true;
	}
	else
	{
		Theta2State = false;
	}

	if (READ(THETA3_ENDSTOP_PIN) == THETA3_ENDSTOP_INVERT)
	{
		Theta3State = true;
	}
	else
	{
		Theta3State = false;
	}

#ifdef ENDSTOP_FOR_CHECK_Z_AREA
	if (READ(ENDSTOP_FOR_CHECK_Z_AREA_PIN) == ENDSTOP_FOR_CHECK_Z_AREA_INVERT)
	{
		ZAreaState = true;
	}
	else
	{
		ZAreaState = false;
	}
#endif
}

bool EndStopsClass::HomingCheck()
{
	if (Theta1State == true && Theta2State == true && Theta3State == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void EndStopsClass::ReportStates()
{
	UpdateStates();
	SERIAL_PORT.print("EndStopStates: ");
	SERIAL_PORT.print(Theta1State);
	SERIAL_PORT.print(", ");
	SERIAL_PORT.print(Theta2State);
	SERIAL_PORT.print(", ");
	SERIAL_PORT.println(Theta3State);
}

bool EndStopsClass::States(AXIS axis)
{
	switch (axis)
	{
	case THETA_1:
		return Theta1State;
		break;
	case THETA_2:
		return Theta2State;
		break;
	case THETA_3:
		return Theta3State;
		break;
	default:
		break;
	}
	return false;
}

void EndStopsClass::ClearEndstopState()
{
	Theta1State = false;
	Theta2State = false;
	Theta3State = false;

#ifdef ENDSTOP_FOR_CHECK_Z_AREA
	ZAreaState = false;
#endif
}

EndStopsClass EndStops;

