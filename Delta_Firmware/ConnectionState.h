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
// LedConnect.h

#ifndef _CONNECTIONSTATE_h
#define _CONNECTIONSTATE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "config.h"
#include "enum.h"

#include "pin.h"
#include "fastio.h"

#define TIME_DISCONNECT 60000

class ConnectionStateClass
{
 protected:

private:

	uint32_t LastTimeBlink;
	uint32_t LastTimeDisconnect;
	uint16_t TimeBlink;
	COLOR Color;
	void SetColor(COLOR color);
	void SetBlink(uint16_t ms);

 public:
	void Init();
	void Connect();
	void Disconnect();
	void Execute();
	void ResetTimeDisconnect();

};

extern ConnectionStateClass ConnectionState;

#endif

