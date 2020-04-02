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

#pragma once

#define BOARD_RAMPS_14

//Delta Model Use
#define DELTA_X_PULY_S
//#define DELTA_X_V2

#define SERIAL_PORT Serial
#define BAUDRATE 115200

#define DELTA_AXIS_4
#ifdef DELTA_AXIS_4

#ifndef NUMBER_DEGREES_OF_FREEDOM
 #define NUMBER_DEGREES_OF_FREEDOM 4
#endif

#define USING_SERVO_FOR_AXIS4
#ifdef USING_SERVO_FOR_AXIS4
 #define AXIS_4_HOME_POSITION 0
 #define AXIS_4_MAX_POSITION	170
 #define AXIS_4_DEG_PER_SECONDS	300		//for RC Servo 9G
 //#define AXIS_4_DEG_PER_SECONDS	300 //for RC Servo MG996
#endif // USING_SERVO_FOR_AXIS4

#endif // DELTA_AXIS_4

#ifndef NUMBER_DEGREES_OF_FREEDOM
 #define NUMBER_DEGREES_OF_FREEDOM 3
#endif


#define VACUUM
#ifdef VACUUM
 #define TIME_DELAY_TO_DROP	400 //ms
#endif // VACUUM


#define CLIP
#ifdef CLIP
 #define CLIP_OPEN_ANGLE_SERVO 110
 #define CLIP_CLOSE_ANGLE_SERVO 55
 #define CLIP_DEG_PER_SECONDS	400 //for RC Servo 9G
#endif // CLIP

//Adaptive Multi - Axis Step - Smoothing(AMASS)
#define SMOOTHSTEP 0

//Bresenham line drawing algorithm
#define MM_PER_LINEAR_SEGMENT	12			//mm
#define MM_PER_ARC_SEGMENT	8			//mm
#define NUMBER_PER_BEZIER_SEGMENT 30	//segment

#define DEFAULT_ACCELERATION 2000.0				//mm^2/s
#define DEFAULT_VELOCITY 300.0					//mm/s

#define DEFAULT_MAX_VELOCITY 850.0			//mm/s
#define DEFAULT_MAX_ACCELERATION 30000.0			//mm/s

#define INTERRUPT_CYCLE_MIN	170.0f  //165

#define DEFAULT_BEGIN_VELOCITY 12			//mm/s 
#define DEFAULT_END_VELOCITY 12		//mm/s

#define DEFAULT_ENTRY_VELOCITY 12			//mm/s
#define DEFAULT_EXIT_VELOCITY 12			//mm/s

#define DEFAULT_MOVING_HOME_SPEED 50			//deg/s

#define THETA1_MAX_POSITION	90					//deg
#define THETA2_MAX_POSITION	90
#define THETA3_MAX_POSITION	90

#define REVERSE_DIRECTION

#define THETA1_ENDSTOP_INVERT false
#define THETA2_ENDSTOP_INVERT false
#define THETA3_ENDSTOP_INVERT false

#ifdef ENDSTOP_FOR_CHECK_Z_AREA
#define ENDSTOP_FOR_CHECK_Z_AREA_INVERT fasle
#endif

