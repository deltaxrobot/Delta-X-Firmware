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

#include "GCodeExecute.h"

void GCodeExecuteClass::Init(vector<String>* gCodeQueue)
{
	this->GCodeQueue = gCodeQueue;
	ResetValue();
	IsRunning = false;
}

void GCodeExecuteClass::Run()
{
	WhenFinishMove();

	if (GCodeQueue->size() == 0 || IsRunning == true)
		return;

	String GcodeInProcessing = GCodeQueue->operator[](0);
	vector<KeyValue> keyValues = getKeyValues(GcodeInProcessing);

	for (uint8_t i = 1; i < keyValues.size(); i++)
	{
		switch (keyValues[i].Key)
		{
		case 'X':
			X = keyValues[i].Value;
			break;
		case 'Y':
			Y = keyValues[i].Value;
			break;
		case 'Z':
			Z = keyValues[i].Value;
			break;
		case 'E':
			E = keyValues[i].Value;
			break;
		case 'S':
			S = keyValues[i].Value;
			break;
		case 'A':
			A = keyValues[i].Value;
			break;
		case 'I':
			I = keyValues[i].Value;
			break;
		case 'J':
			J = keyValues[i].Value;
			break;
		case 'F':
			F = keyValues[i].Value;
			break;
		case 'P':
			P = keyValues[i].Value;
			break;
		case 'R':
			R = keyValues[i].Value;
			break;
		case 'Q':
			Q = keyValues[i].Value;
			break;
		case 'W':
			W = keyValues[i].Value;
			break;
		default:
			break;
		}
	}

	checkAndRunFunction(keyValues[0]);

	GCodeQueue->erase(GCodeQueue->begin());
	IsRunning = true;
}

void GCodeExecuteClass::WhenFinishMove()
{
	if (Stepper.GetStateMotor() == true)
	{
		if (IsRunning == true)
		{
			if (Data.IsExecutedGcode == true)
			{
				SERIAL_PORT.println("Ok");	
			}
			else
			{
				if (Tool.IsWait == true)
				{
					if (!Tool.Wait())
					{
						return;
					}
					SERIAL_PORT.println("Ok");
					Tool.IsWait = false;
				}
				else
				{
					SERIAL_PORT.println("Unknown");
				}				
			}
			ConnectionState.ResetTimeDisconnect();
			IsRunning = false;
			Data.IsExecutedGcode = false;
		}
	}
}

void GCodeExecuteClass::checkAndRunFunction(KeyValue keyValue)
{
	switch (keyValue.Key)
	{
	case 'G':
		switch ((int)keyValue.Value)
		{
		case 0:
			if (F != NULL_NUMBER) Planner.SetVelocity(F);
			if (X == NULL_NUMBER) X = Data.CurrentPoint.X;
			if (Y == NULL_NUMBER) Y = Data.CurrentPoint.Y;
			if (Z == NULL_NUMBER) Z = Data.CurrentPoint.Z;
			if (W == NULL_NUMBER) W = Data.WPosition;
			Motion.G0(X, Y, Z, W);		
			break;
		case 1:
			if (F != NULL_NUMBER) Planner.SetVelocity(F);
			if (X == NULL_NUMBER) X = Data.CurrentPoint.X;
			if (Y == NULL_NUMBER) Y = Data.CurrentPoint.Y;
			if (Z == NULL_NUMBER) Z = Data.CurrentPoint.Z;
			if (W == NULL_NUMBER) W = Data.WPosition;
			Motion.G1(X, Y, Z, W);
			if (S >= 0 && S <= 255) Control.M03(S);
			break;
		case 2:
			if (I == NULL_NUMBER) break;
			if (J == NULL_NUMBER) break;
			if (F != NULL_NUMBER) Planner.SetVelocity(F);
			if (X == NULL_NUMBER) X = Data.CurrentPoint.X;
			if (Y == NULL_NUMBER) Y = Data.CurrentPoint.Y;
			if (W == NULL_NUMBER) W = Data.WPosition;
			Motion.G2(I, J, X, Y, W);
			if (S >= 0 && S <= 255) Control.M03(S);
			break;
		case 3:
			if (I == NULL_NUMBER) break;
			if (J == NULL_NUMBER) break;
			if (F != NULL_NUMBER) Planner.SetVelocity(F);
			if (X == NULL_NUMBER) X = Data.CurrentPoint.X;
			if (Y == NULL_NUMBER) Y = Data.CurrentPoint.Y;
			if (W == NULL_NUMBER) W = Data.WPosition;
			Motion.G3(I, J, X, Y, W);
			if (S >= 0 && S <= 255) Control.M03(S);
			break;
		case 4:
			if (P == NULL_NUMBER) break;
			Motion.G4(P);
			break;
		case 5:
			if (I == NULL_NUMBER) break;
			if (J == NULL_NUMBER) break;
			if (P == NULL_NUMBER) break;
			if (Q == NULL_NUMBER) break;
			if (F != NULL_NUMBER) Planner.SetVelocity(F);
			if (X == NULL_NUMBER) X = Data.CurrentPoint.X;
			if (Y == NULL_NUMBER) Y = Data.CurrentPoint.Y;
			if (W == NULL_NUMBER) W = Data.WPosition;
			Motion.G5(I, J, P, Q, X, Y, W);
			if (S >= 0 && S <= 255) Control.M03(S);
			break;
		case 6:
			if (F != NULL_NUMBER) Planner.SetVelocity(F);
			if (X == NULL_NUMBER) X = Data.CurrentPoint.X;
			if (Y == NULL_NUMBER) Y = Data.CurrentPoint.Y;
			if (Z == NULL_NUMBER) Z = Data.CurrentPoint.Z;
			if (W == NULL_NUMBER) W = Data.WPosition;
			if (P == NULL_NUMBER) break;
			Motion.G6(X, Y, Z, P);
			if (S >= 0 && S <= 255) Control.M03(S);
			break;
		case 28:
			Motion.G28();
			break;
		case 90:
			Control.G90();
			break;
		case 91:
			Control.G91();
			break;
		case 93:
			Control.G93();
			break;
		default:
			break;
		}
		break;
	case 'M':
		switch ((int)keyValue.Value)
		{
		case 3:
			if (S == NULL_NUMBER) S = 255;
			Control.M03(S);
			break;
		case 4:
			if (S == NULL_NUMBER) S = 255;
			Control.M04(S);
			break;
		case 5:
			Control.M05();
			break;
		case 84:
			Control.M84();
			break;
		case 104:
			if (S > 240) S = 240;
			Control.M104(S);
			break;
		case  105:
			Control.M105();
			break;
		case 109:
			Control.M109();
			break;
		case 203:
			Control.M203(S);
			break;
		case 204:
			Control.M204(A);
			break;
		case 206:
			Control.M206(Z);
			break;
		case 360:
			if (E > USE_CUSTOM) break;
			Control.M360(E);
			break;
		case 361:
			if (P == NULL_NUMBER) break;
			Control.M361(P);
			break;
		case 362:
			if (P == NULL_NUMBER) break;
			Control.M362(P);
			break;
		case 500:
			Control.M500();
			break;
		case 501:
			Control.M501();
			break;
		case 502:
			Control.M502();
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	ResetValue();
}

vector<KeyValue> GCodeExecuteClass::getKeyValues(String code)
{
	String splitWord = "";
	vector<KeyValue> keyValues;
	code += " ";
	for (uint16_t i = 0; i < code.length(); i++)
	{
		if (code[i] == ' ')
		{
			if (splitWord == "")
				continue;
			KeyValue keyValue;
			keyValue.Key = splitWord[0];
			keyValue.Value = splitWord.substring(1).toFloat();
			keyValues.push_back(keyValue);
			splitWord = "";
			continue;
		}
		splitWord += String(code[i]);
	}
	return keyValues;
}

void GCodeExecuteClass::ResetValue()
{
	X = NULL_NUMBER;
	Y = NULL_NUMBER;
	Z = NULL_NUMBER;
	E = NULL_NUMBER;
	S = NULL_NUMBER;
	A = NULL_NUMBER;
	I = NULL_NUMBER;
	J = NULL_NUMBER;
	F = NULL_NUMBER;
	P = NULL_NUMBER;
	R = NULL_NUMBER;
	Q = NULL_NUMBER;
	W = NULL_NUMBER;
}