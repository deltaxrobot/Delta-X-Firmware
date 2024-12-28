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
// WifiSettings.h

#ifndef _WIFISETTINGS_h
#define _WIFISETTINGS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <EEPROM.h>
#include "config.h"

class WifiSettingsClass
{
protected:
public:
	void init();
	void Save();
	void SaveIP();
	void IP();
	void GetSsid();
	void GetPswd();

	String SSIDWifi;
	String PSWDWifi;
	String IPWifi;
};

extern WifiSettingsClass WifiSettings;

#endif
