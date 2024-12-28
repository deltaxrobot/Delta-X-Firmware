import serial
from time import sleep

Serial = serial.Serial('/dev/', 115200)

try:
    while True:
        sleep(0.5)
        while Serial.in_waiting:
            DeltaResponse = Serial.readline()
            print(f"{DeltaResponse}")
            # if (KeyboardInterrupt):
            #     Serial.close()

        command = input("Input Delta command：")
        if command == "down":
            GCode = "G0 Z-400"

        elif command == "home":
            GCode = "G28"
        Serial.write(bytes(GCode.encode()))

except UnicodeDecodeError as e:
    print("UnicodeDecodeError:", e)

except KeyboardInterrupt:
    Serial.close()

    # GCode = ["G0 Z-400",
    #          "G0 X100",
    #          "G0 Y100",
    #          "G0 X-100",
    #          "G0 Y-100",
    #          "G0 X0 Y0"]
