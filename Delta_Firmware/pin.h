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
#pragma once

#ifdef BOARD_RAMPS_14
//pin theta
#define THETA1_PULSE_PIN 54
#define THETA2_PULSE_PIN 60
#define THETA3_PULSE_PIN 46

#define THETA1_DIRECTION_PIN 55
#define THETA2_DIRECTION_PIN 61
#define THETA3_DIRECTION_PIN 48

#define THETA1_ENABLE_PIN 38
#define THETA2_ENABLE_PIN 56
#define THETA3_ENABLE_PIN 62

#define THETA1_ENDSTOP_PIN 3
#define THETA2_ENDSTOP_PIN 14
#define THETA3_ENDSTOP_PIN 18

#define ENDSTOP_FOR_CHECK_Z_AREA_PIN 18


//pin axis
#ifdef USING_SERVO_FOR_AXIS4
 #define AXIS_4_SERVO_PIN 11
#else
#ifdef USING_STEPER_FOR_AXIS4
 #define AXIS_4_PULSE_PIN 26
 #define AXIS_4_DIRECTION_PIN 28
 #define AXIS_4_ENABLE_PIN 24
 #define AXIS_4_ENDSTOP_PIN 2
#endif // USING_STEPER_FOR_AXIS4
#endif // USING_SERVO_FOR_AXIS4


#ifdef USING_SERVO_FOR_AXIS5
 #define AXIS_5_SERVO_PIN 11
#else
#ifdef USING_STEPER_FOR_AXIS5
 #define AXIS_5_PULSE_PIN 26
 #define AXIS_5_DIRECTION_PIN 28
 #define AXIS_5_ENABLE_PIN 24
 #define AXIS_5_ENDSTOP_PIN 2
#endif // USING_STEPER_FOR_AXIS5
#endif // USING_SERVO_FOR_AXIS5


#define CHANNEL_A_ENCODER_PIN	20
#define CHANNEL_B_ENCODER_PIN	21

#define VACCUM_PIN 10

#define CLIP_SERVO_PIN 6

#define SPINDLE_LASER_ENABLE_PIN  10   // Pin should have a pullup/pulldown!
#define SPINDLE_LASER_PWM_PIN     5   // MUST BE HARDWARE PWM

#define CUSTOM_PWM_PIN	4
#define CUSTOM_DIR_PIN	16

#define LED_R_PIN	25
#define LED_G_PIN	23
#define LED_B_PIN	17

#define EXTRUSDER_PULSE_PIN 26
#define EXTRUSDER_DIRECTION_PIN 28
#define EXTRUSDER_ENABLE_PIN 24

//thermistor
#define THERMISTOR_PIN	PIN_A13
#define HEATER_PIN	8

#endif // BOARD_RAMPS_14


