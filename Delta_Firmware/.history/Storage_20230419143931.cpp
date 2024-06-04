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

#include "Storage.h"

void StorageClass::init()
{
	
}

void StorageClass::StorageSettings()
{
	EEPROM.put(VELICITY_ADDRESS, Data.Velocity);
	EEPROM.put(ACCELERATION_ADDRESS, Data.Acceleration);

	EEPROM.put(RD_F_ADDRESS, Data.RD_F);
	EEPROM.put(RD_E_ADDRESS, Data.RD_E);

	EEPROM.put(RD_RF_ADDRESS, Data.RD_RF);
	EEPROM.put(RD_RE_ADDRESS, Data.RD_RE);

	EEPROM.put(RD_W_ADDRESS, Data.RD_W);
	EEPROM.put(RD_U_ADDRESS, Data.RD_U);
	EEPROM.put(RD_V_ADDRESS, Data.RD_V);

	EEPROM.put(MOVE_AREA_X_ADDRESS, Data.MOVING_AREA_X);
	EEPROM.put(MOVE_AREA_Y_ADDRESS, Data.MOVING_AREA_Y);
	EEPROM.put(MOVE_AREA_Z_ADDRESS, Data.MOVING_AREA_Z);

	EEPROM.put(MOVE_AREA_LARGEST_DIAMETER_ADDRESS, Data.MOVING_AREA_LARGEST_DIAMETER);

	EEPROM.put(MOVING_HOME_SPEED_ADDRESS, Data.MovingHomeSpeed);
	EEPROM.put(BEGIN_END_VELOCITY_ADDRESS, Data.BeginEndVelocity);

	EEPROM.put(ENTRY_VELOCITY_ADDRESS, Data.EntryVelocity);
	EEPROM.put(EXIT_VELOCITY_ADDRESS, Data.ExitVelocity);

	EEPROM.put(MM_PER_LINEAR_SEGMENT_ADDRESS, Data.MMPerLinearSegment);
	EEPROM.put(MM_PER_ARC_SEGMENT_ADDRESS, Data.MMPerArcSegment);

	delay(10);
}

void StorageClass::LoadSettings()
{
	EEPROM.get(VELICITY_ADDRESS, Data.Velocity);
	EEPROM.get(ACCELERATION_ADDRESS, Data.Acceleration);

	EEPROM.get(RD_F_ADDRESS, Data.RD_F);
	EEPROM.get(RD_E_ADDRESS, Data.RD_E);

	EEPROM.get(RD_RF_ADDRESS, Data.RD_RF);
	EEPROM.get(RD_RE_ADDRESS, Data.RD_RE);

	EEPROM.get(RD_W_ADDRESS, Data.RD_W);
	EEPROM.get(RD_U_ADDRESS, Data.RD_U);
	EEPROM.get(RD_V_ADDRESS, Data.RD_V);

	EEPROM.get(MOVE_AREA_X_ADDRESS, Data.MOVING_AREA_X);
	EEPROM.get(MOVE_AREA_Y_ADDRESS, Data.MOVING_AREA_Y);
	EEPROM.get(MOVE_AREA_Z_ADDRESS, Data.MOVING_AREA_Z);

	EEPROM.get(MOVE_AREA_LARGEST_DIAMETER_ADDRESS, Data.MOVING_AREA_LARGEST_DIAMETER);

	EEPROM.get(MOVING_HOME_SPEED_ADDRESS, Data.MovingHomeSpeed);

	EEPROM.get(BEGIN_END_VELOCITY_ADDRESS, Data.BeginEndVelocity);

	EEPROM.get(ENTRY_VELOCITY_ADDRESS, Data.EntryVelocity);
	EEPROM.get(EXIT_VELOCITY_ADDRESS, Data.ExitVelocity);

	EEPROM.get(MM_PER_LINEAR_SEGMENT_ADDRESS, Data.MMPerLinearSegment);
	EEPROM.get(MM_PER_ARC_SEGMENT_ADDRESS, Data.MMPerArcSegment);

	delay(10);
}

void StorageClass::RestoreSettings()
{
	Data.ResetData();
	StorageSettings();
}

StorageClass Storage;

