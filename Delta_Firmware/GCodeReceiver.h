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
// GCodeReceiver.h

#ifndef _GCODERECEIVER_h
#define _GCODERECEIVER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <ArduinoSTL.h>
#include <vector>
#include "ConnectionState.h"
#include "WifiSettings.h"
#include "Constants.h"
#include "Temperature.h"

using namespace std;

class GCodeReceiverClass
{
public:
	void Init(vector<String>* gCodeQueue, HardwareSerial* serial, unsigned long baudrate);

	void Execute();

	HardwareSerial* ReceiveSerial;
	unsigned long Baudrate;

	vector<String>* GCodeQueue;

private:
	
	String receiveString;
	bool isStringComplete;
};

#endif

