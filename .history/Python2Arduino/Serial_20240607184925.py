import serial
import time
import math

ser = serial.Serial('/dev/MEGA2560', 115200, timeout=1)  # open serial port
time.sleep(2)
print(ser.readline())

Circle_r = 50
Resolution = 1

gcodes.append('G28')
gcodes.append('G01 Z-500')
gcodes.append('G01 Z-500')

for degree in range(0, 360, Resolution):
    x = math.cos(math.radians(degree)) * Circle_r
    y = math.sin(math.radians(degree)) * Circle_r
    gcodes.append(f'G01 X%d Y%d'.format(x, y))

for gcode in gcodes:
    print(gcode)
    ser.write((gcode + '\n').encode())
    while 1:
        response = ser.readline()
        print(response)
        if (response.find('Ok'.encode()) > -1):
            break
        elif (response.find('Unknown'.encode()) > -1):
            break

ser.close()             # close port
