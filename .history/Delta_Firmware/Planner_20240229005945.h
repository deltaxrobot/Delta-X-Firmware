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
// Planner.h

#ifndef _PLANNER_h
#define _PLANNER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <ArduinoSTL.h>
#include <vector>

#include "config.h"
#include "enum.h"
#include "Constants.h"

using namespace std;

#define US_TO_NUMINT (1.0 / INTERRUPT_CYCLE_MIN)
#define TIME_TO_US 1000000.0
#define TIME_TO_NUMINT (1000000.0 / INTERRUPT_CYCLE_MIN)
#define STEP_NULL 65530
//#define STEP_NULL 60000
#define EXTRUSTION_STEPS_PER_MM		92.6

typedef struct
{
	uint16_t StepsToJump;
	bool Direction;
}Step;

class Segment
{
public:
	Step StepperArray[3];
	uint32_t NumberINT;
};

class PlannerClass
{
 protected:

 public:
	void init(vector<Segment>* SegmentQueue);
	void AddHomeSegment();
	void AddBeginSegment(float* offset, float lengthOfRoad);
	void AddEndSegment(float* offset, float lengthOfRoad);
	void AddChangeSegment(float* offset, float lengthOfRoad);
	void AddFixedSegment(float* offset, float lengthOfRoad);
	void AddExtrustionSegment(float offset);

	vector<Segment>* SegmentQueue;

	void SetVelocity(float velocity);
	void SetMaxVelocity(float velocity);
	void SetAcceleration(float acceleration);
	void SetHomeSpeed(float velocity);
	void SetBeginEndVelocity(float velocity);

	uint16_t GetExtrustionStepsToJump();
	uint16_t ExtrustionStepsToJump;
	bool ExtrustionStepsDirection;

	float LastError[3];

	uint32_t AccelerationUntil;
	uint32_t DecelerateAfter;
	uint32_t NumberIntRoad;

	float a;
	float BeginEndIntCycle;
	float HomingIntCycle;

 private:
	Step ChangeToStep(float* offset, uint8_t index);

	uint32_t TimeForChangeVelocity;

	float StepsPerDeg[3]; 

	void RecalculateTimeForChangeVelocity();
	void RecalculateBeginEndIntCycle();
};

extern PlannerClass Planner;

#endif

