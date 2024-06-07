/**
 * GCodeReceiverClass::Execute()用於處理接受到的G-code
 * 接收到指令Position，則通過串口輸出當前座標 Data.CurrentPoint.X、Data.CurrentPoint.Y 和 Data.CurrentPoint.Z。
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

//@ 執行
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
			receiveString += inChar;
	}

	//* receiveString超過70，將清空後返回
	if (!isStringComplete)
	{
		if (receiveString.length() > 70)
			receiveString = "";
		
		return;
	}
	
	//* 接收到'M'或'G'時，將其添加到GCodeQueue
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
  }
	receiveString = "";
	isStringComplete = false;
}