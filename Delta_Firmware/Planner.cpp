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

#include "Planner.h"

void PlannerClass::init(vector<Segment>* SegmentQueue)
{
	StepsPerDeg[0] = (float)THETA1_STEPS_PER_2PI / 360.0;
	StepsPerDeg[1] = (float)THETA2_STEPS_PER_2PI / 360.0;
	StepsPerDeg[2] = (float)THETA3_STEPS_PER_2PI / 360.0;

	this->SegmentQueue = SegmentQueue;

	RecalculateBeginEndIntCycle();
	RecalculateTimeForChangeVelocity();

	LastError[0] = 0;
	LastError[1] = 0;
	LastError[2] = 0;
}

void PlannerClass::AddHomeSegment()
{
	float timeForOneStep = 1 / (Data.MovingHomeSpeed * StepsPerDeg[0]);
	HomingIntCycle = timeForOneStep * TIME_TO_US;

	Segment segbuffer;
	for (uint8_t i = 0; i < 3; i++)
	{
		segbuffer.StepperArray[i].StepsToJump = STEP_NULL;
		segbuffer.StepperArray[i].Direction = DECREASE;
	}
	SegmentQueue->push_back(segbuffer);

	Segment segbuffer2;
	float offset[3];
	offset[0] = 10;
	offset[1] = 10;
	offset[2] = 10;
	for (uint8_t i = 0; i < 3; i++)
	{
		segbuffer2.StepperArray[i] = ChangeToStep(offset, i);
	}
	SegmentQueue->push_back(segbuffer2);

	Segment segbuffer1;
	for (uint8_t i = 0; i < 3; i++)
	{
		segbuffer1.StepperArray[i].StepsToJump = STEP_NULL;
		segbuffer1.StepperArray[i].Direction = DECREASE;
	}
	SegmentQueue->push_back(segbuffer1);

	LastError[0] = 0;
	LastError[1] = 0;
	LastError[2] = 0;
}

void PlannerClass::AddBeginSegment(float* offset, float lengthOfRoad)
{
	Segment segbuffer;
	NumberIntRoad = 0;

	float timeMove = lengthOfRoad / Data.Velocity;
	segbuffer.NumberINT = roundf(timeMove * TIME_TO_NUMINT);

	for (uint8_t i = 0; i < 3; i++)
	{
		segbuffer.StepperArray[i] = ChangeToStep(offset, i);
		if (segbuffer.NumberINT < segbuffer.StepperArray[i].StepsToJump)
		{
			segbuffer.NumberINT = segbuffer.StepperArray[i].StepsToJump;
		}
		//Serial.println(segbuffer.StepperArray[i].StepsToJump);
	}

	NumberIntRoad += segbuffer.NumberINT;

	SegmentQueue->push_back(segbuffer);
}

void PlannerClass::AddEndSegment(float* offset, float lengthOfRoad)
{
	Segment segbuffer;

	float timeMove = lengthOfRoad / Data.Velocity;
	segbuffer.NumberINT = roundf(timeMove * TIME_TO_NUMINT);

	for (uint8_t i = 0; i < 3; i++)
	{
		segbuffer.StepperArray[i] = ChangeToStep(offset, i);
		if (segbuffer.NumberINT < segbuffer.StepperArray[i].StepsToJump)
		{
			segbuffer.NumberINT = segbuffer.StepperArray[i].StepsToJump;
		}
		//Serial.println(segbuffer.StepperArray[i].StepsToJump);
	}

	NumberIntRoad += segbuffer.NumberINT;

	if (NumberIntRoad / 2 < TimeForChangeVelocity)
	{
		AccelerationUntil = NumberIntRoad / 2;
		DecelerateAfter = AccelerationUntil;
	}
	else
	{
		AccelerationUntil = TimeForChangeVelocity;
		DecelerateAfter = NumberIntRoad - AccelerationUntil;
	}

	SegmentQueue->push_back(segbuffer);
}

void PlannerClass::AddChangeSegment(float* offset, float lengthOfRoad)
{
	Segment segbuffer;
	NumberIntRoad = 0;

	float timeMove = lengthOfRoad / Data.Velocity;
	segbuffer.NumberINT = roundf(timeMove * TIME_TO_NUMINT);

	for (uint8_t i = 0; i < 3; i++)
	{
		segbuffer.StepperArray[i] = ChangeToStep(offset, i);
		if (segbuffer.NumberINT < segbuffer.StepperArray[i].StepsToJump)
		{
			segbuffer.NumberINT = segbuffer.StepperArray[i].StepsToJump;
		}
	}

	NumberIntRoad += segbuffer.NumberINT;

	if (NumberIntRoad / 2 < TimeForChangeVelocity)
	{
		AccelerationUntil = NumberIntRoad / 2;
		DecelerateAfter = AccelerationUntil;
	}
	else
	{
		AccelerationUntil = TimeForChangeVelocity;
		DecelerateAfter = NumberIntRoad - AccelerationUntil;
	}

	SegmentQueue->push_back(segbuffer);
}

void PlannerClass::AddFixedSegment(float* offset, float lengthOfRoad)
{
	Segment segbuffer;

	float timeMove = lengthOfRoad / Data.Velocity;
	segbuffer.NumberINT = roundf(timeMove * TIME_TO_NUMINT);

	for (uint8_t i = 0; i < 3; i++)
	{
		segbuffer.StepperArray[i] = ChangeToStep(offset, i);
		if (segbuffer.NumberINT < segbuffer.StepperArray[i].StepsToJump)
		{
			segbuffer.NumberINT = segbuffer.StepperArray[i].StepsToJump;
		}
		//Serial.println(segbuffer.StepperArray[i].StepsToJump);
	}

	NumberIntRoad += segbuffer.NumberINT;

	SegmentQueue->push_back(segbuffer);
}

void PlannerClass::AddExtrustionSegment(float offset)
{
	if (offset == 0)
	{
		return;
	}

	if (offset > 0)
	{
		ExtrustionStepsDirection = INCREASE;
	}
	else
	{
		ExtrustionStepsDirection = DECREASE;
		offset = -offset;
	}

	ExtrustionStepsToJump = roundf(offset * EXTRUSTION_STEPS_PER_MM);

	if (NumberIntRoad == 0)
	{
		float timeMove = offset / Data.Velocity;
		NumberIntRoad = roundf(timeMove * TIME_TO_NUMINT);

		Segment segbuffer;
		segbuffer.NumberINT = NumberIntRoad;

		segbuffer.StepperArray[0].StepsToJump = 0;
		segbuffer.StepperArray[1].StepsToJump = 0;
		segbuffer.StepperArray[2].StepsToJump = 0;

		AccelerationUntil = 0;
		DecelerateAfter = NumberIntRoad;

		SegmentQueue->push_back(segbuffer);
	}
}

Step PlannerClass::ChangeToStep(float* offset, uint8_t index)
{
	Step stepBuffer;

	float realStepsToJump = offset[index] * StepsPerDeg[index];

	realStepsToJump -= LastError[index];

	if (offset[index] >= 0)
	{
		stepBuffer.Direction = INCREASE;
		realStepsToJump = realStepsToJump;
	}
	else
	{
		stepBuffer.Direction = DECREASE;
		realStepsToJump = -realStepsToJump;
	}

	stepBuffer.StepsToJump = roundf(realStepsToJump);

	LastError[index] = stepBuffer.StepsToJump - realStepsToJump;
	
	if (offset[index] < 0)
	{
		LastError[index] = -LastError[index];
	}

	return stepBuffer;
}

void PlannerClass::SetVelocity(float velocity)
{
	if (velocity > DEFAULT_MAX_VELOCITY)
	{
		Data.Velocity = DEFAULT_MAX_VELOCITY;
	}
	else
	{
		Data.Velocity = velocity;
	}

	if (Data.End_Effector == USE_PRINTER)
	{
		Data.Velocity = velocity / 60;
	}

	RecalculateBeginEndIntCycle();
	RecalculateTimeForChangeVelocity();
}

void PlannerClass::SetMaxVelocity(float velocity)
{

}

void PlannerClass::SetAcceleration(float acceleration)
{
	if (acceleration > DEFAULT_MAX_ACCELERATION)
	{
		Data.Acceleration = DEFAULT_MAX_ACCELERATION;
	}
	else
	{
		Data.Acceleration = acceleration;
	}

	RecalculateTimeForChangeVelocity();
}

void PlannerClass::SetHomeSpeed(float velocity)
{
	Data.MovingHomeSpeed = velocity;
	float timeForOneStep = 1 / (Data.MovingHomeSpeed * StepsPerDeg[0]);
	HomingIntCycle = timeForOneStep * TIME_TO_US;
}

void PlannerClass::SetBeginEndVelocity(float velocity)
{
	Data.BeginEndVelocity = velocity;
	RecalculateBeginEndIntCycle();
	RecalculateTimeForChangeVelocity();
}

void PlannerClass::RecalculateTimeForChangeVelocity()
{
	float accelTime = (Data.Velocity - Data.BeginEndVelocity) / Data.Acceleration;
	TimeForChangeVelocity = roundf(accelTime * TIME_TO_NUMINT);
	a = (BeginEndIntCycle - INTERRUPT_CYCLE_MIN) / (accelTime * TIME_TO_US);
	if (a < 0)
	{
		a = 0;
	}
}

void PlannerClass::RecalculateBeginEndIntCycle()
{
	BeginEndIntCycle =  Data.Velocity * INTERRUPT_CYCLE_MIN / Data.BeginEndVelocity;
	if (BeginEndIntCycle < INTERRUPT_CYCLE_MIN)
	{
		BeginEndIntCycle = INTERRUPT_CYCLE_MIN;
	}
}

PlannerClass Planner;