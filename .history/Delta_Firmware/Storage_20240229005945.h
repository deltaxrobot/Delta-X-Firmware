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
// Storage.h

#ifndef _STORAGE_h
#define _STORAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "config.h"
#include "EEPROM.h"
#include "Constants.h"

#define VELICITY_ADDRESS 0
#define ACCELERATION_ADDRESS 4

#define RD_F_ADDRESS 8
#define RD_E_ADDRESS 12

#define RD_RF_ADDRESS 16
#define RD_RE_ADDRESS 20

#define RD_W_ADDRESS 24
#define RD_U_ADDRESS 28
#define RD_V_ADDRESS 32

#define MOVE_AREA_X_ADDRESS 36
#define MOVE_AREA_Y_ADDRESS 40
#define MOVE_AREA_Z_ADDRESS 44

#define MOVE_AREA_LARGEST_DIAMETER_ADDRESS 48

#define MOVING_HOME_SPEED_ADDRESS 52

#define BEGIN_END_VELOCITY_ADDRESS 56

#define ENTRY_VELOCITY_ADDRESS 64
#define EXIT_VELOCITY_ADDRESS 68

#define MM_PER_LINEAR_SEGMENT_ADDRESS 72
#define MM_PER_ARC_SEGMENT_ADDRESS 76

class StorageClass
{
 protected:

 public:
	void init();
	void StorageSettings();
	void LoadSettings();
	void RestoreSettings();
 private:
};

extern StorageClass Storage;

#endif

