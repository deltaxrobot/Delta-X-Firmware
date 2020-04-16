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
 * 
 =============================================================================================================
Greetings! Thank you for choosing DeltaXFirmware as your delta robot firmware.

To configure DeltaX you must edit Config.h and Geometry.h
located in the root 'Delta_Firmware' folder.

==============================================================================================================
Delta X Gcode

-G0, G1 – Linear Move

Description: The G0 and G1 commands add a linear move to the queue to be performed after all previous moves are completed.
A command like G1 F1000 sets the feedrate for all subsequent moves.
Usage: G0 [F<rate>] [X<pos>] [Y<pos>] [Z<pos>] [W<ang>]
Parameters:
[F<rate>]    The maximum movement rate of the move between the start and end point. The feedrate set here applies to subsequent moves that omit this parameter.
[X<pos>]   A coordinate on the X axis.
[Y<pos>]   A coordinate on the Y axis.
[Z<pos>]   A coordinate on the Z axis.
[W<ang>]   A coordinate on the W axis.
Examples:
G0 X12   ; move to 12mm on the X axis 
G0 F1500 ; set the feedrate to 1500mm/minute 
G1 X90.6 Y13.8 ; move to 90.6mm on the X axis and 13.8mm on the Y axis 
--------------------------------------------------------------------------------

-G2, G3 – Controlled Arc Move

Description: G2 adds a clockwise arc move to the planner; G3 adds a counter-clockwise arc. An arc move starts at the current position and ends at the given XYZ, pivoting around a center-point offset given by I and J.
Usage: G2 [F<rate>] I<offset> J<offset> [X<pos>] [Y<pos>] [W<ang>]
Parameters:
[F<rate>]    The maximum movement rate of the move between the start and end point. The feedrate set here applies to subsequent moves that omit this parameter.
I<offset>   An offset from the current X position to use as the arc center.
J<offset>   An offset from the current Y position to use as the arc center.
[X<pos>]   A coordinate on the X axis.
[Y<pos>]   A coordinate on the Y axis.
[W<ang>]   A coordinate on the W axis.
Examples:
G2 I40 J0 X80 Y0
--------------------------------------------------------------------------------

-G4 – Dwell

Description: Dwell pauses the command queue and waits for a period of time.
Usage: G4 [P<time in ms>]. Other firmware version "time in s"
Parameters:
[P<time>]   Amount of time to dwell.
Examples:
G4 P500 ; delay 0.5s, or 500s
--------------------------------------------------------------------------------

-G5 – Bezier cubic spline

Description: G5 creates a cubic B-spline in the XY plane with the X and Y axes only. P and Q parameters are required. I and J are required for the first G5 command in a series. For subsequent G5commands, either both I and J must be specified, or neither. If I and J are unspecified, the starting direction of the cubic will automatically match the ending direction of the previous cubic (as if I and J are the negation of the previous P and Q).
Usage: G5 [F<rate>] I<pos> J<pos> P<pos> Q<pos> X<pos> Y<pos>  [W<ang>]
Parameters:
[F<rate>]    The maximum movement rate of the move between the start and end point. The feedrate set here applies to subsequent moves that omit this parameter.
[I<pos>]   X incremental offset from start point to first control point.
[J<pos>]   Y incremental offset from start point to first control point.
[P<pos>]  X incremental offset from end point to second control point.
[Q<pos>]   Y incremental offset from end point to second control point.
[X<pos>]   A coordinate on the Y axis.
[Y<pos>]   A coordinate on the Y axis.
[W<ang>]   A coordinate on the W axis.
Examples:
G5 F200 I-40 Y20 P-20 Y-20 X20 Y-20.
--------------------------------------------------------------------------------

-G6 – Controlled Angle

Description: Directly control movement angle without endpoint coordinates..
Usage: G6 [F<rate>] X<pos> Y<pos> Z<pos> P<pos>
Parameters:
[F<rate>]    The maximum movement rate of the move between the start and end point. The feedrate set here applies to subsequent moves that omit this parameter.
[X<pos>]   The value of the angle theta 1.
[Y<pos>]   The value of the angle theta 2.
[Z<pos>]   The value of the angle theta 3.
[P<pos>]   Distance traveled.
Examples:
G4 P500 ; delay 0.5s
--------------------------------------------------------------------------------

-G28 – Auto Home

Description: Auto-home one or more axes, moving them towards their endstops until triggered.
Usage: G28
--------------------------------------------------------------------------------

-G90 – Absolute Positioning

Description: In absolute mode all coordinates given in G-code are interpreted as positions in the logical coordinate space.
Usage: G90
--------------------------------------------------------------------------------

-G91 – Relative Positioning

Description: Set relative position mode. In this mode all coordinates are interpreted as relative to the last position.
Usage: G91
--------------------------------------------------------------------------------

-M3 – Spindle CW/ Laser On/ Set Gripper To Close/ Set Angle of Gripper

Description: Wait for moves to complete, then set the spindle speed (clockwise), laser power, or angle of gripper.
Usage: M3 [S<value>]
Parameters:
[S<value>] Spindle speed (0 - 255), laser power (0 - 255), angle of gripper (0-100), if value is emtpy then gripper close.
--------------------------------------------------------------------------------

-M4 – Spindle CCW/ Laser On/ Set Gripper To Close/ Set Angle of Gripper

Description: Wait for moves to complete, then set the spindle speed (clockwise), laser power, or angle of gripper.
Usage: M4 [S<value>]
Parameters:
[S<value>] Spindle speed (0 - 255), laser power (0 - 255), angle of gripper (0-100), if value is emtpy then gripper close.
--------------------------------------------------------------------------------

-M5 – Spindle / Laser Off/ Gripper Open

Description: Wait for moves to complete, then turn off the spindle / laser power, PWM and set gripper to open.
Usage: M5
--------------------------------------------------------------------------------

-M84 – Disable steppers

Description: This command can be used to disable steppers.
Usage: M84
--------------------------------------------------------------------------------

-M104 – Set Hotend Temperature

Description: Set a new target hot end temperature and continue without waiting. The firmware will continue to try to reach and hold the temperature in the background.
Usage: M104 [S<temp>]
Parameters:
[S<temp>] Target temperature.
--------------------------------------------------------------------------------

-M109 – Wait for Hotend Temperature

Description: This command optionally sets a new target hot end temperature and waits for the target temperature to be reached before proceeding.
Usage: M109 [S<temp>]
Parameters:
[S<temp>] Target temperature.
--------------------------------------------------------------------------------

-M203 – Set Max Feedrate

Description: Set the max feedrate for one or more axes.
Usage: M203 [S<units/s>]
Parameters:
[S<units/s>] Max feedrate.
--------------------------------------------------------------------------------

-M204 – Set Acceleration

Description: Set the preferred acceleration for moves of different types.
Usage: M204 [A<accel>]
Parameters:
[A<accel>] Travel acceleration.
--------------------------------------------------------------------------------

-M206 – Set Z Offsets

Description: Use M206 to apply a persistent Z offset to the native home position and coordinate space. This effectively shifts the coordinate space in the negative direction. Used for 3d printing.
Usage: M206 [Z<offset>]
Parameters:
[Z<offset>] Z offset.
--------------------------------------------------------------------------------

-M500 – Save Settings

Description: Save all configurable settings to EEPROM.
Usage: M500
--------------------------------------------------------------------------------

-M501 – Restore Settings

Description: Load all saved settings from EEPROM.
Usage: M501
--------------------------------------------------------------------------------

-M502 – Restore Settings

Description: Reset all configurable settings to their factory defaults..
Usage: M502
--------------------------------------------------------------------------------

-M360 – Set End effector

Description: Select the end effector for delta robot.
Usage: M360 [E<index>]
Parameters:
 index =
0 : Vacuum.
1 : Gripper.
2 : Pen.
3 : Laser.
4 : Printer.
5 : Custom.
--------------------------------------------------------------------------------

-M361 – Set mm per linear segment

Description: Set segment length when interpolation.
Usage: M361 [P<units>]
Parameters:
[P<units>] Segment length when linear interpolation.
--------------------------------------------------------------------------------

-M362 – Set mm per arc segment

Description: Set segment length when interpolation.
Usage: M361 [P<units>]
Parameters:
[P<units>] segment length when arc interpolation.


 */
