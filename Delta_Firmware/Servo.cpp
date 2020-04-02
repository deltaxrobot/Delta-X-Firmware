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

#include "Servo.h"

Servo::Servo()
{

}

void Servo::attach(int pin)
{
	if (pin == 11)
	{
		TCCR1A = 0x0;
		TCCR1B = 0x0;
		TCNT1 = 0x0;

		//setting the prescaler to 8 (2MHz):
		TCCR1B |= (1 << CS11);

		//setting the waveform generation mode to 15:
		TCCR1A |= (1 << WGM11);
		TCCR1B |= (1 << WGM12) | (1 << WGM13);

		//setting the the TOP value:
		ICR1 = MAX_TIMER_COUNT; //results in 50Hz at 2MHz Clock

		//setting the output to non inverted:
		TCCR1A |= (1 << COM1A1);

		OCR1A = DEFAULT_PULSE_WIDTH; //setting the pulse width

		//OC1A, Port B, Bit 5; setting pin 11 as output:
		DDRB |= (1 << 5); //bit 5 (pin 11) as output  

		this->servoPin = 11;
	}
	else if (pin == 6)
	{
		TCCR4A = 0x0;
		TCCR4B = 0x0;
		TCNT4 = 0x0;

		//setting the prescaler to 8 (2MHz):
		TCCR4B |= (1 << CS41);

		//setting the waveform generation mode to 15:
		TCCR4A |= (1 << WGM41);
		TCCR4B |= (1 << WGM42) | (1 << WGM43);

		//setting the the TOP value:
		ICR4 = MAX_TIMER_COUNT; //results in 50Hz at 2MHz Clock

		//setting the output to non inverted:
		TCCR4A |= (1 << COM4A1);

		OCR4A = DEFAULT_PULSE_WIDTH; //setting the pulse width

		//OC4A, Port H, Bit 3; setting pin 6 as output:
		DDRH |= (1 << 3); //bit 3 (pin 6) as output  

		this->servoPin = 6;
	}
}

void Servo::detach()
{
	if (servoPin == 11) {
		//resetting the control register A and B:
		TCCR1A = 0x0;
		TCCR1B = 0x0;

		//resetting the TOP value:
		ICR1 = 0x0;
		OCR1A = 0x0;

		DDRB ^= (1 << 5); //bit 5 (pin 11) stop output
		this->servoPin = 0;
	}
	else if (servoPin == 6) {
		//resetting the control register A and B:
		TCCR4A = 0x0;
		TCCR4B = 0x0;

		//resetting the TOP value:
		ICR4 = 0x0;
		OCR4A = 0x0;

		DDRH ^= (1 << 3); //bit 3 (pin 6) stop output
		this->servoPin = 0;
	}
}

void Servo::writeMicroseconds(int value)
{
	if (value < MIN_PULSE_WIDTH)
	{
		value = MIN_PULSE_WIDTH;
	}
	else if (value > MAX_PULSE_WIDTH)
	{
		value = MAX_PULSE_WIDTH;
	}
	if (this->servoPin == 11)
	{
		OCR1A = 0x0;
		OCR1A = value * 2;
	}
	else if (this->servoPin == 6)
	{
		OCR4A = 0x0;
		OCR4A = value * 2;
	}
}

void Servo::write(int value)
{
	value = map(constrain(value, 0, 180), 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
    this->writeMicroseconds(value);
}