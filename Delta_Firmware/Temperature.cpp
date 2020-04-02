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

#include "Temperature.h"

void TemperatureClass::init()
{
	pinMode(THERMISTOR_PIN, INPUT);
	pinMode(HEATER_PIN, OUTPUT);
	analogWrite(HEATER_PIN, 0);

	noInterrupts();
	// Reset register relate to Timer 3
	// Reset register relate
	TCCR4A = TCCR4B = TCNT4 = 0;
	// Set CTC mode to Timer 3
	TCCR4B |= (1 << WGM42);
	// Set prescaler 8 to Timer 3
	TCCR4B |= (1 << CS41);
	//Normal port operation, OCxA disconnected
	TCCR4A &= ~((1 << COM4A1) | (1 << COM4A0) | (1 << COM4B1) | (1 << COM4B0));

	COMPARE_VALUE_TIMER4 = roundf(INTERRUPT_CYCLE_TIMER4 * F_CPU / (1000.0 * 8)) - 1;
	interrupts();
	TurnOffTimer4;
}

void TemperatureClass::GetTemperature()
{
	int raw = 0;
	for (int j = 1; j <= OVERSAMPLENR; j++)
	{
		raw += analogRead(THERMISTOR_PIN);
	}
	float celsius = 0;
	uint8_t i;
	short(*tt)[][2] = (short(*)[][2])(temptable_60);
	for (i = 1; i < 72; i++)
	{
		if (PGM_RD_W((*tt)[i][0]) > raw)
		{
			celsius = PGM_RD_W((*tt)[i - 1][1]) +
				(raw - PGM_RD_W((*tt)[i - 1][0])) *
				(float)(PGM_RD_W((*tt)[i][1]) - PGM_RD_W((*tt)[i - 1][1])) /
				(float)(PGM_RD_W((*tt)[i][0]) - PGM_RD_W((*tt)[i - 1][0]));
			break;
		}
	}

	// Overflow: Set to last value in the table
	if (i == 72) { celsius = PGM_RD_W((*tt)[i - 1][1]); }

	CurrentTemperature = celsius;
	
}

void TemperatureClass::SetHotendTemperature(float temperature)
{
	if (Data.End_Effector != USE_PRINTER)
		return;

	DesiredTemperature = temperature;
	if (DesiredTemperature == 0)
	{
		Cooldown();
		TurnOffTimer4;
	}
	else
	{
		TurnOnTimer4;
	}
}

bool TemperatureClass::WaitForHotendTemperature()
{
	if (DesiredTemperature == 0)
	{
		return true;
	}

	if (CurrentTemperature < (DesiredTemperature - TEMP_HYSTERESIS) || CurrentTemperature > (DesiredTemperature + TEMP_HYSTERESIS))
	{
		LastTime = millis();
	}

	if (millis() - LastTime > (TEMP_RESIDENCY_TIME * 1000))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void TemperatureClass::Cooldown()
{
	analogWrite(HEATER_PIN, 0);
}

void TemperatureClass::ISR_EXECUTE()
{
	if (Data.End_Effector != USE_PRINTER)
	{
		Cooldown();
		return;
	}

	GetTemperature();

	float error = DesiredTemperature - CurrentTemperature;
	if (error < 0)
	{
		analogWrite(HEATER_PIN, 0);
		return;
	}

	float dError = error - LastError;
	LastError = error;

	float P = error * DEFAULT_KP;
	I += error * DEFAULT_KI * ((float)INTERRUPT_CYCLE_TIMER4 / 1000);
	float D = (dError * DEFAULT_KD) / ((float)INTERRUPT_CYCLE_TIMER4 / 1000);

	float pwmValue = P + I + D;

	pwmValue = constrain(pwmValue, 0, 255);

	analogWrite(HEATER_PIN, pwmValue);
}

ISR(TIMER4_COMPA_vect)
{
	Temperature.ISR_EXECUTE();
}

TemperatureClass Temperature;

