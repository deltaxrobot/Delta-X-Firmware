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
// GCodeExecute.h

#ifndef _GCODEEXECUTE_h
#define _GCODEEXECUTE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <ArduinoSTL.h>
#include <vector>
#include "enum.h"
#include "Motion.h"
#include "Control.h"

#define NULL_NUMBER 98765

using namespace std;

class KeyValue
{
public:
	char Key;
	float Value;
};

class NoArgumentFunction
{
public:
	String Code;
	void(*Function)();
};

class GCodeExecuteClass
{
public:
	void Init(vector<String>*);
	void Run();
	void WhenFinishMove();

	vector<String>* GCodeQueue;
	bool IsRunning;

	float X, Y, Z, E, S, A, I, J, F, P, R, Q, W;
private:
	vector<KeyValue> getKeyValues(String code);
	void checkAndRunFunction(KeyValue keyValue);
	void ResetValue();
	vector <NoArgumentFunction> NoArgumentFunctions;
};


#endif

