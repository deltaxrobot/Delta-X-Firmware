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
// MultiServo.h

#ifndef _MULTISERVO_h
#define _MULTISERVO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "config.h"
#include "enum.h"

#include "pin.h"
#include "Servo.h"

typedef struct
{
	uint8_t lastPosition;
	uint8_t Desired;

	Servo servo;
	AXIS Name;
}Servo_t;

class MultiServoClass
{
 protected:


 public:
	void init();
	void CreateServo(AXIS axisname, uint8_t pin);
	void AddAngle(AXIS axisname, uint8_t angle);

	void Running();
	Servo_t *ServoArray;
protected:
	
	uint8_t NumberOfServoCreated;
	long LastTimer;
	void AddServo(Servo_t servo);
};

extern MultiServoClass MultiServo;

#endif

