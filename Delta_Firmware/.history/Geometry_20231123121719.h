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

#ifdef DELTA_X_PULY_S
#define DEFAULT_RD_F	259.04   // SB			//size S  258.64 + 0.4
#define DEFAULT_RD_E	120.0	// SP = RD_E / 2
#define DEFAULT_RD_RF	130.0	// L
#define DEFAULT_RD_RE	315.0   // l

#define DEFAULT_RD_W	0.0
#define DEFAULT_RD_U	0.0
#define DEFAULT_RD_V	0.0

#define DEFAULT_MOVING_AREA_X		170
#define DEFAULT_MOVING_AREA_Y		170
#define DEFAULT_MOVING_AREA_Z	    402

#define DEFAULT_MOVING_AREA_LARGEST_DIAMETER	170			//mm

#define THETA1_HOME_POSITION -38.5				//deg -41.2	
#define THETA2_HOME_POSITION -38.5
#define THETA3_HOME_POSITION -38.5

#define THETA1_STEPS_PER_2PI  9600				//200*16*3
#define THETA2_STEPS_PER_2PI  9600
#define THETA3_STEPS_PER_2PI  9600
#endif // DELTA_X_PULY_S

#ifdef DELTA_X_V2
#define DEFAULT_RD_F	260.0   // SB			//size S  258.64 + 0.4
#define DEFAULT_RD_E	120.0	// SP = RD_E / 2
#define DEFAULT_RD_RF	120.0	// L
#define DEFAULT_RD_RE	305.0   // l

#define DEFAULT_RD_W	0.0
#define DEFAULT_RD_U	0.0
#define DEFAULT_RD_V	0.0

#define DEFAULT_MOVING_AREA_X		170
#define DEFAULT_MOVING_AREA_Y		170
#define DEFAULT_MOVING_AREA_Z	    402

#define DEFAULT_MOVING_AREA_LARGEST_DIAMETER	170			//mm

#define THETA1_HOME_POSITION -34.25				//deg -41.2	
#define THETA2_HOME_POSITION -34.25
#define THETA3_HOME_POSITION -34.25

#define THETA1_STEPS_PER_2PI  9600				//200*16*3
#define THETA2_STEPS_PER_2PI  9600
#define THETA3_STEPS_PER_2PI  9600

#endif
