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

#include "GCodeReceiver.h"

void GCodeReceiverClass::Init(vector<String>* gCodeQueue, HardwareSerial* serial, unsigned long baudrate)
{
	ReceiveSerial = serial;
	ReceiveSerial->begin(baudrate);
	receiveString.reserve(100);

	isStringComplete = false;
	receiveString = "";

	this->GCodeQueue = gCodeQueue;
}

void GCodeReceiverClass::Execute()
{
	while (ReceiveSerial->available())
	{
		char inChar = (char)ReceiveSerial->read();

		if (inChar == '\n')
		{
			isStringComplete = true;
			break;
		}

		if (inChar != '\r')
		{
			receiveString += inChar;
		}
	}

	if (!isStringComplete)
	{
		if (receiveString.length() > 70)
		{
			receiveString = "";
		}
		
		return;
	}
		
	if (receiveString[0] == 'M' || receiveString[0] == 'G')
	{
		GCodeQueue->push_back(receiveString);
		receiveString = "";
		isStringComplete = false;
		return;
	}

	int index = receiveString.indexOf(':');

	if (index == -1)
	{
		if (receiveString == "IsDelta") ConnectionState.Connect();
		else if (receiveString == "Disconnect") ConnectionState.Disconnect();
		else if (receiveString == "Position")
		{
			Serial.print(Data.CurrentPoint.X);
			Serial.print(",");
			Serial.print(Data.CurrentPoint.Y);
			Serial.print(",");
			Serial.println(Data.CurrentPoint.Z);
		}
		else if (receiveString == "SAVEWIFI") {
			WifiSettings.Save();
			Serial.println("Ok");	
		}
		else if (receiveString == "SAVEIP") WifiSettings.SaveIP();
		else if (receiveString == "IP") WifiSettings.IP();
		else if (receiveString == "gSsid") WifiSettings.GetSsid();
		else if (receiveString == "gPswd") WifiSettings.GetPswd();
		else if (receiveString == "Temp")
		{
			Temperature.GetTemperature();
			Serial.print("T:");
			Serial.println(Temperature.CurrentTemperature);
		}
	}
	else
	{
		String keyString = receiveString.substring(0, index);
		String valueString = receiveString.substring(index + 1);
		if (keyString == "SSID") {
			WifiSettings.SSIDWifi = valueString;
			Serial.println("Ok");
		}
		else if (keyString == "PSWD") {
			WifiSettings.PSWDWifi = valueString;
			Serial.println("Ok");
		}
		else if (keyString == "ESPIP") 
		{
			WifiSettings.IPWifi = valueString;
			Serial.println(valueString);
		}
	}

	receiveString = "";
	isStringComplete = false;
}