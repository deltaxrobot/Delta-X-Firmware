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

#include "WifiSettings.h"

void WifiSettingsClass::init()
{


}

void WifiSettingsClass::Save()
{
	char ssidWifi[32] = "";
	char pswdWifi[32] = "";
	SSIDWifi.toCharArray(ssidWifi, 32);
	PSWDWifi.toCharArray(pswdWifi, 32);

	EEPROM.put(133, ssidWifi);
	EEPROM.put(167, pswdWifi);

	delay(1);
}

void WifiSettingsClass::SaveIP()
{
	char ipWifi[32] = "";
	IPWifi.toCharArray(ipWifi, 32);
	EEPROM.put(100, ipWifi);
	delay(1);
}

void WifiSettingsClass::IP()
{
	char ipWifi[32] = "";
	EEPROM.get(100, ipWifi);
	delay(1);
	SERIAL_PORT.println(ipWifi);
}

void WifiSettingsClass::GetSsid()
{
	char ssidWifi[32] = "";
	EEPROM.get(133, ssidWifi);

	SERIAL_PORT.println("SSID:" + SSIDWifi);
}

void WifiSettingsClass::GetPswd()
{
	char pswdWifi[32] = "";
	EEPROM.get(167, pswdWifi);

	SERIAL_PORT.println("PSWD:" + PSWDWifi);
}

WifiSettingsClass WifiSettings;

