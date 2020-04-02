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
// EndStops.h

#ifndef _ENDSTOPS_h
#define _ENDSTOPS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "config.h"
#include "enum.h"

#include "pin.h"
#include "fastio.h"

class EndStopsClass
{
 protected:


 public:
	void init();
	void UpdateStates();
	bool HomingCheck();
	void ReportStates();
	bool States(AXIS axis);
	void ClearEndstopState();

private:
	bool Theta1State;
	bool Theta2State;
	bool Theta3State;

#ifdef ENDSTOP_FOR_CHECK_Z_AREA
	bool ZAreaState;
#endif
	//uint8_t HomePhase;
};

extern EndStopsClass EndStops;

#endif

