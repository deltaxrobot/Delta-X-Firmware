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

#include "EndEffector.h"

void EndEffectorClass::init()
{
	pinMode(VACCUM_PIN, OUTPUT);

	pinMode(SPINDLE_LASER_ENABLE_PIN, OUTPUT);
	pinMode(SPINDLE_LASER_PWM_PIN, OUTPUT);

	pinMode(CUSTOM_PWM_PIN, OUTPUT);
	pinMode(CUSTOM_DIR_PIN, OUTPUT);

	pinMode(EXTRUSDER_PULSE_PIN, OUTPUT);
	pinMode(EXTRUSDER_DIRECTION_PIN, OUTPUT);
	pinMode(EXTRUSDER_ENABLE_PIN, OUTPUT);

}

void EndEffectorClass::ResetEndEffectorOutput()
{
	analogWrite(VACCUM_PIN, 0);

	analogWrite(SPINDLE_LASER_ENABLE_PIN, 0);
	analogWrite(SPINDLE_LASER_PWM_PIN, 0);
	WRITE(CUSTOM_PWM_PIN, 0);
	analogWrite(CUSTOM_DIR_PIN, 0);

	WRITE(EXTRUSDER_ENABLE_PIN, 0);

	Data.ExtrustionPosition = 0;

	if (Data.End_Effector == USE_LASER)
	{
		analogWrite(SPINDLE_LASER_ENABLE_PIN, 255);
	}

	if (Data.End_Effector == USE_PRINTER)
	{
		analogWrite(SPINDLE_LASER_ENABLE_PIN, 255);
		Temperature.init();
	}

	if (Data.End_Effector != USE_PRINTER && Data.End_Effector != USE_LASER)
	{
		MultiServo.ServoArray[1].servo.attach(CLIP_SERVO_PIN);
	}

	MultiServo.AddAngle(CLAMP, CLIP_OPEN_ANGLE_SERVO);
	MultiServo.Running();
}

void EndEffectorClass::TurnOffEndEffector()
{
	switch (Data.End_Effector)
	{
	case USE_VACUUM:
		analogWrite(VACCUM_PIN, 0);
		break;
	case USE_LASER:
		analogWrite(SPINDLE_LASER_PWM_PIN, 0);
		break;
	case USE_CLIP:
		MultiServo.AddAngle(CLAMP, CLIP_OPEN_ANGLE_SERVO);
		MultiServo.Running();
		break;
	case USE_PEN:
		break;
	case USE_CUSTOM:
		digitalWrite(CUSTOM_DIR_PIN, 0);
		analogWrite(CUSTOM_PWM_PIN, 0);
		break;
	case USE_PRINTER:
		digitalWrite(EXTRUSDER_ENABLE_PIN, 1);
		break;
	default:
		break;
	}
}

void EndEffectorClass::TurnOnEndEffector(byte eValue, bool iSw)
{
	switch (Data.End_Effector)
	{
	case USE_VACUUM:
		analogWrite(VACCUM_PIN, 255);
		break;
	case USE_LASER:		
		analogWrite(SPINDLE_LASER_PWM_PIN, eValue);
		break;
	case USE_CLIP:
		if (eValue > 100)
		{
			MultiServo.AddAngle(CLAMP, CLIP_CLOSE_ANGLE_SERVO);
		}
		else
		{
			byte clipValue = eValue * (CLIP_OPEN_ANGLE_SERVO - CLIP_CLOSE_ANGLE_SERVO) / 100;
			MultiServo.AddAngle(CLAMP, CLIP_OPEN_ANGLE_SERVO - clipValue);
		}

		MultiServo.Running();
		break;
	case USE_PEN:
		break;
	case USE_CUSTOM:
		digitalWrite(CUSTOM_DIR_PIN, iSw);
		analogWrite(CUSTOM_PWM_PIN, eValue);
		break;
	case USE_PRINTER:
		digitalWrite(EXTRUSDER_ENABLE_PIN, 0);
		break;
	default:
		break;
	}
}

EndEffectorClass EndEffector;

