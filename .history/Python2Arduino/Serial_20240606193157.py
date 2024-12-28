import serial
from time import sleep

ser = serial.Serial('/dev/MEGA2560', 115200)
time.

try:
    while True:
        sleep(0.5)
        while ser.in_waiting:
            DeltaResponse = ser.readline()
            print(f"{DeltaResponse}")
            # if (KeyboardInterrupt):
            #     Serial.close()

        command = input("Input Delta command：")
        if command == "down":
            GCode = "G0Z-400"

        elif command == "home":
            GCode = "G28"
        ser.write(bytes(GCode.encode()))

except UnicodeDecodeError as e:
    print("UnicodeDecodeError:", e)

except KeyboardInterrupt:
    ser.close()

    # GCode = ["G0 Z-400",
    #          "G0 X100",
    #          "G0 Y100",
    #          "G0 X-100",
    #          "G0 Y-100",
    #          "G0 X0 Y0"]
