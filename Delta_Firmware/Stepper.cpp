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

#include "Stepper.h"

void StepperClass::init(vector<Segment>* SegmentQueue)
{
	this->SegmentQueue = SegmentQueue;

	noInterrupts();
	
	// Reset register relate to Timer 5
	// Reset register relate
	TCCR5A = TCCR5B = TCNT5 = 0;
	// Set CTC mode to Timer 5
	TCCR5B |= (1 << WGM52);
	// Set prescaler 1 to Timer 5
	TCCR5B |= (1 << CS50);
	//Normal port operation, OCxA disconnected
	TCCR5A &= ~((1 << COM5A1) | (1 << COM5A0) | (1 << COM5B1) | (1 << COM5B0));
	

	// Setup for Timer 2
	// Reset register relate
	TCCR2A = TCCR2B = TCNT2 = 0;
	// Set CTC mode
	TCCR2A |= (1 << WGM21);
	// Set prescaler 1
	TCCR2B |= (1 << CS20);
	//Normal port operation, OC2A disconnected
	TCCR2A &= ~((1 << COM2A1) | (1 << COM2A0) | (1 << COM2B1) | (1 << COM2B0));
	COMPARE_VALUE_TIMER2 = 80; //5us

	interrupts();

	CreateMotor();

	IsRunningHome = false;
	IsStoppedMoving = true;
}

void StepperClass::CreateMotor()
{
	ThetaStepMotor[0].Name = THETA_1;
	setPinMode(THETA_1);

	ThetaStepMotor[1].Name = THETA_2;
	setPinMode(THETA_2);

	ThetaStepMotor[2].Name = THETA_3;
	setPinMode(THETA_3);

}

bool StepperClass::GetStateMotor()
{
	return IsStoppedMoving;
}

void StepperClass::UpdateMoveSegment()
{
	if (SegmentQueue->size() == 0)
	{
		IsStoppedMoving = true;
		NumberTnterrupt = 0;
		Planner.NumberIntRoad = 0;
		Timer = 0;
		TurnOffTimer5;
		return;
	}	

	CurrentMoveSegment = SegmentQueue->operator[](0);
	SegmentQueue->erase(SegmentQueue->begin());

	for (uint8_t i = 0; i < 3; i++)
	{
		setMotorDirection(ThetaStepMotor[i].Name, CurrentMoveSegment.StepperArray[i].Direction);
		ThetaStepMotor[i].InterruptNumberNextStep = 0;
		if (CurrentMoveSegment.StepperArray[i].StepsToJump == 0)
		{
			ThetaStepMotor[i].NumberInterrupt2Step = STEP_NULL;
		}
		else
		{
			ThetaStepMotor[i].NumberInterrupt2Step = (float)CurrentMoveSegment.NumberINT / CurrentMoveSegment.StepperArray[i].StepsToJump;
		}
	}

	NumberTnterrupt = 0;
}

void StepperClass::Running()
{	
	if (SegmentQueue->size() == 0)
	{
		return;
	}

	CurrentMoveSegment = SegmentQueue->operator[](0);
	SegmentQueue->erase(SegmentQueue->begin());

	for (uint8_t i = 0; i < 3; i++)
	{
		setMotorDirection(ThetaStepMotor[i].Name, CurrentMoveSegment.StepperArray[i].Direction);
		ThetaStepMotor[i].InterruptNumberNextStep = 0;

		if (CurrentMoveSegment.StepperArray[i].StepsToJump == 0)
		{
			ThetaStepMotor[i].NumberInterrupt2Step = STEP_NULL;
		}
		else
		{
			ThetaStepMotor[i].NumberInterrupt2Step = (float)CurrentMoveSegment.NumberINT / CurrentMoveSegment.StepperArray[i].StepsToJump;
		}
	}

	if (Data.End_Effector == USE_PRINTER)
	{
		WRITE(EXTRUSDER_DIRECTION_PIN, Planner.ExtrustionStepsDirection);
		ExtrustionStepMotor.InterruptNumberNextStep = 0;

		if (Planner.ExtrustionStepsToJump == 0)
		{
			ExtrustionStepMotor.NumberInterrupt2Step = STEP_NULL;
		}
		else
		{
			ExtrustionStepMotor.NumberInterrupt2Step = (float)Planner.NumberIntRoad / Planner.ExtrustionStepsToJump;
		}
	}

	CurrentCycle = Planner.BeginEndIntCycle;
	MaxCycle = Planner.BeginEndIntCycle;
	SetIntCycle(CurrentCycle);
	

	NumberTnterruptAtMinCycle = 0;
	TotalTnterruptNumber = 0;
	IsStoppedMoving = false;
	TurnOnTimer5;
}

void StepperClass::Homing()
{
	if (SegmentQueue->size() == 0)
	{
		IsStoppedMoving = true;
		IsRunningHome = 0;
		TurnOffTimer5;
		SegmentQueue->clear();
		return;
	}

	IsRunningHome++;

	CurrentMoveSegment = SegmentQueue->operator[](0);
	SegmentQueue->erase(SegmentQueue->begin());

	for (uint8_t i = 0; i < 3; i++)
	{
		setMotorDirection(ThetaStepMotor[i].Name, CurrentMoveSegment.StepperArray[i].Direction);
	}

	if (IsRunningHome == 1 || IsRunningHome == 2)
	{
		CurrentCycle = Planner.HomingIntCycle;
	}
	if (IsRunningHome == 3)
	{
		CurrentCycle = Planner.HomingIntCycle * 8;
	}

	SetIntCycle(CurrentCycle);

	IsStoppedMoving = false;
	TurnOnTimer5;
}

void StepperClass::Isr_Execute_Velocity()
{
	// Movinghome **********
	if (IsRunningHome > 0)
	{
		Isr_Execute_Movinghome();
		return;
	}
	//**********************

	NumberTnterrupt++;
	TotalTnterruptNumber++;

	//Execute accel

	if (TotalTnterruptNumber < Planner.AccelerationUntil)
	{
		Timer += CurrentCycle;
		CurrentCycle = MaxCycle - (Timer * Planner.a);
		if (CurrentCycle < INTERRUPT_CYCLE_MIN)
		{
			CurrentCycle = INTERRUPT_CYCLE_MIN;
		}
		else
		{
			NumberTnterruptAtMinCycle = TotalTnterruptNumber;
		}
	}
	else if (TotalTnterruptNumber > Planner.DecelerateAfter)
	{
		if (TotalTnterruptNumber > Planner.NumberIntRoad - NumberTnterruptAtMinCycle)
		{
			Timer += CurrentCycle;
		}	
		CurrentCycle = MaxCycle + (Timer * Planner.a);
	}
	else
	{
		Timer = 0;
		MaxCycle = CurrentCycle;
	}

	SetIntCycle(CurrentCycle);
	//Serial.println(CurrentCycle);
	//Checking jump step and Accumulated error
	for (uint8_t i = 0; i < 3; i++)
	{
		if (ThetaStepMotor[i].InterruptNumberNextStep >= NumberTnterrupt)
		{
			continue;
		}
		ThetaStepMotor[i].InterruptNumberNextStep += ThetaStepMotor[i].NumberInterrupt2Step;
		if (CurrentMoveSegment.StepperArray[i].StepsToJump != 0)
		{
			CurrentMoveSegment.StepperArray[i].StepsToJump--;
			writePulsePin(ThetaStepMotor[i].Name, 1);
		}
	}

	if (Data.End_Effector == USE_PRINTER)
	{
		if (ExtrustionStepMotor.InterruptNumberNextStep < TotalTnterruptNumber)
		{
			ExtrustionStepMotor.InterruptNumberNextStep += ExtrustionStepMotor.NumberInterrupt2Step;
			if (Planner.ExtrustionStepsToJump != 0)
			{
				Planner.ExtrustionStepsToJump--;
				WRITE(EXTRUSDER_PULSE_PIN, HIGH);
			}
		}
	}

	TurnOnTimer2;
	
	if (CurrentMoveSegment.StepperArray[0].StepsToJump == 0 && CurrentMoveSegment.StepperArray[1].StepsToJump == 0 && CurrentMoveSegment.StepperArray[2].StepsToJump == 0)
	//if (NumberTnterrupt >= CurrentMoveSegment.NumberINT - 1)
	{
		UpdateMoveSegment();
	}
}

void StepperClass::Isr_Execute_Movinghome()
{
	EndStops.UpdateStates();
	for (uint8_t i = 0; i < 3; i++)
	{
		if (CurrentMoveSegment.StepperArray[i].StepsToJump > 1000)
		{
			if (EndStops.States(ThetaStepMotor[i].Name) == false)
			{
				writePulsePin(ThetaStepMotor[i].Name, 1);
			}
		}
		else
		{
			if (CurrentMoveSegment.StepperArray[i].StepsToJump > 0)
			{
				writePulsePin(ThetaStepMotor[i].Name, 1);
				CurrentMoveSegment.StepperArray[i].StepsToJump--;
			}
					
		}	
	}

	SetIntCycle(CurrentCycle);
	TurnOnTimer2;
	if (IsRunningHome == 2)
	{
		for (uint8_t i = 0; i < 3; i++)
		{
			if (CurrentMoveSegment.StepperArray[i].StepsToJump > 0)
			{
				return;
			}		
		}
	}
	else if(IsRunningHome == 1 || IsRunningHome == 3)
	{
		if (EndStops.HomingCheck() == false)
		{
			return;
		}
	}
	Homing();
}

//turning pulse pin low
void StepperClass::Isr_Turn_Pulse_Pin()
{
	for (uint8_t i = 0; i < 3; i++)
	{
		writePulsePin(ThetaStepMotor[i].Name, 0);
	}

	if (Data.End_Effector == USE_PRINTER)
	{
		WRITE(EXTRUSDER_PULSE_PIN, LOW);
	}
	TurnOffTimer2;
}

void StepperClass::SetIntCycle(float intCycle)
{
	int prescaler;

	if (intCycle > 4000)
	{
		TCCR5B |= (1 << CS51);
		TCCR5B &= ~(1 << CS50);
		prescaler = 8;
	}
	else
	{
		TCCR5B &= ~(1 << CS51);
		TCCR5B |= (1 << CS50);
		prescaler = 1;
	}

	COMPARE_VALUE_TIMER5 = roundf(intCycle * F_CPU / (1000000.0 * prescaler)) - 1;
}

void StepperClass::ClearMotorArray()
{
	for (int8_t i = 0; i < 3; i++)
	{
		//MotorArray[i].StepCounter = 0;
		ThetaStepMotor[i].InterruptNumberNextStep = 0;
	}
}

void StepperClass::setPinMode(AXIS axisname)
{
	switch (axisname)
	{
	case THETA_1:
		pinMode(THETA1_ENABLE_PIN, OUTPUT);
		pinMode(THETA1_PULSE_PIN, OUTPUT);
		pinMode(THETA1_DIRECTION_PIN, OUTPUT);

		WRITE(THETA1_ENABLE_PIN, LOW);
		WRITE(THETA1_PULSE_PIN, LOW);
		WRITE(THETA1_DIRECTION_PIN, DECREASE);
		break;
	case THETA_2:
		pinMode(THETA2_ENABLE_PIN, OUTPUT);
		pinMode(THETA2_PULSE_PIN, OUTPUT);
		pinMode(THETA2_DIRECTION_PIN, OUTPUT);

		WRITE(THETA2_ENABLE_PIN, LOW);
		WRITE(THETA2_PULSE_PIN, LOW);
		WRITE(THETA2_DIRECTION_PIN, DECREASE);
		break;
	case THETA_3:
		pinMode(THETA3_ENABLE_PIN, OUTPUT);
		pinMode(THETA3_PULSE_PIN, OUTPUT);
		pinMode(THETA3_DIRECTION_PIN, OUTPUT);

		WRITE(THETA3_ENABLE_PIN, LOW);
		WRITE(THETA3_PULSE_PIN, LOW);
		WRITE(THETA3_DIRECTION_PIN, DECREASE);
		break;

#ifdef USING_STEPER_FOR_AXIS4
	case AXIS_4:
		pinMode(AXIS_4_ENABLE_PIN, OUTPUT);
		pinMode(AXIS_4_PULSE_PIN, OUTPUT);
		pinMode(AXIS_4_DIRECTION_PIN, OUTPUT);

		WRITE(AXIS_4_ENABLE_PIN, LOW);
		WRITE(AXIS_4_PULSE_PIN, LOW);
		WRITE(AXIS_4_DIRECTION_PIN, DECREASE);
		break;
#endif // USING_STEPER_FOR_AXIS4

#ifdef USING_STEPER_FOR_AXIS5
	case AXIS_5:
		pinMode(AXIS_5_ENABLE_PIN, OUTPUT);
		pinMode(AXIS_5_PULSE_PIN, OUTPUT);
		pinMode(AXIS_5_DIRECTION_PIN, OUTPUT);

		WRITE(AXIS_5_ENABLE_PIN, LOW);
		WRITE(AXIS_5_PULSE_PIN, LOW);
		WRITE(AXIS_5_DIRECTION_PIN, DECREASE);
		break;
#endif // USING_STEPER_FOR_AXIS5

	default:
		break;
	}
}

void StepperClass::setMotorDirection(AXIS axisname, bool variation)
{
	switch (axisname)
	{
	case THETA_1:
		WRITE(THETA1_DIRECTION_PIN, variation);
		break;
	case THETA_2:
		WRITE(THETA2_DIRECTION_PIN, variation);
		break;
	case THETA_3:
		WRITE(THETA3_DIRECTION_PIN, variation);
		break;

#ifdef USING_STEPER_FOR_AXIS4
	case AXIS_4:
		WRITE(AXIS_4_DIRECTION_PIN, variation);
		break;
#endif // USING_STEPER_FOR_AXIS4

#ifdef USING_STEPER_FOR_AXIS5
	case AXIS_5:
		WRITE(AXIS_5_DIRECTION_PIN, variation);
		break;
#endif // USING_STEPER_FOR_AXIS5

	default:
		break;
	}
}

void StepperClass::writePulsePin(AXIS axisname, bool ison)
{
	switch (axisname)
	{
	case THETA_1:
		WRITE(THETA1_PULSE_PIN, ison);
		break;
	case THETA_2:
		WRITE(THETA2_PULSE_PIN, ison);
		break;
	case THETA_3:
		WRITE(THETA3_PULSE_PIN, ison);
		break;

#ifdef USING_STEPER_FOR_AXIS4
	case AXIS_4:
		WRITE(AXIS_4_PULSE_PIN, ison);
		break;
#endif // USING_STEPER_FOR_AXIS4

#ifdef USING_STEPER_FOR_AXIS5
	case AXIS_5:
		WRITE(AXIS_5_PULSE_PIN, ison);
		break;
#endif // USING_STEPER_FOR_AXIS5

	default:
		break;
	}
}

void StepperClass::DisanableStepper()
{
	WRITE(THETA1_ENABLE_PIN, HIGH);
	WRITE(THETA2_ENABLE_PIN, HIGH);
	WRITE(THETA3_ENABLE_PIN, HIGH);
	if (Data.End_Effector == USE_PRINTER)
	{
		WRITE(EXTRUSDER_ENABLE_PIN, HIGH);
	}	
}

void StepperClass::EnableStepper()
{
	WRITE(THETA1_ENABLE_PIN, LOW);
	WRITE(THETA2_ENABLE_PIN, LOW);
	WRITE(THETA3_ENABLE_PIN, LOW);
	if (Data.End_Effector == USE_PRINTER)
	{
		WRITE(EXTRUSDER_ENABLE_PIN, LOW);
	}
}


ISR(TIMER5_COMPA_vect)
{
	Stepper.Isr_Execute_Velocity();
}

ISR(TIMER2_COMPA_vect)
{
	Stepper.Isr_Turn_Pulse_Pin();
}


StepperClass Stepper;
