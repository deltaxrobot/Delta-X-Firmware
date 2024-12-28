/**

 *
 *
 */
// Temperature.h

#ifndef _TEMPERATURE_h
#define _TEMPERATURE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <avr/interrupt.h>
#include "config.h"
#include "pin.h"

#include "Constants.h"

#define OVERSAMPLENR 16
#define OV(N) int16_t((N) * (OVERSAMPLENR))

const short temptable_60[][2] PROGMEM = {
    {OV(51), 272},
    {OV(61), 258},
    {OV(71), 247},
    {OV(81), 237},
    {OV(91), 229},
    {OV(101), 221},
    {OV(131), 204},
    {OV(161), 190},
    {OV(191), 179},
    {OV(231), 167},
    {OV(271), 157},
    {OV(311), 148},
    {OV(351), 140},
    {OV(381), 135},
    {OV(411), 130},
    {OV(441), 125},
    {OV(451), 123},
    {OV(461), 122},
    {OV(471), 120},
    {OV(481), 119},
    {OV(491), 117},
    {OV(501), 116},
    {OV(511), 114},
    {OV(521), 113},
    {OV(531), 111},
    {OV(541), 110},
    {OV(551), 108},
    {OV(561), 107},
    {OV(571), 105},
    {OV(581), 104},
    {OV(591), 102},
    {OV(601), 101},
    {OV(611), 100},
    {OV(621), 98},
    {OV(631), 97},
    {OV(641), 95},
    {OV(651), 94},
    {OV(661), 92},
    {OV(671), 91},
    {OV(681), 90},
    {OV(691), 88},
    {OV(701), 87},
    {OV(711), 85},
    {OV(721), 84},
    {OV(731), 82},
    {OV(741), 81},
    {OV(751), 79},
    {OV(761), 77},
    {OV(771), 76},
    {OV(781), 74},
    {OV(791), 72},
    {OV(801), 71},
    {OV(811), 69},
    {OV(821), 67},
    {OV(831), 65},
    {OV(841), 63},
    {OV(851), 62},
    {OV(861), 60},
    {OV(871), 57},
    {OV(881), 55},
    {OV(891), 53},
    {OV(901), 51},
    {OV(911), 48},
    {OV(921), 45},
    {OV(931), 42},
    {OV(941), 39},
    {OV(951), 36},
    {OV(961), 32},
    {OV(981), 23},
    {OV(991), 17},
    {OV(1001), 9},
    {OV(1008), 0}};

#define TurnOnTimer4 (TIMSK4 |= (1 << OCIE4A))
#define TurnOffTimer4 (TIMSK4 &= ~(1 << OCIE4A))
#define COMPARE_VALUE_TIMER4 OCR4A

#define INTERRUPT_CYCLE_TIMER4 30 // ms

#define DEFAULT_KP 22.2
#define DEFAULT_KI 0.2
#define DEFAULT_KD 65

#define TEMP_RESIDENCY_TIME 2 // (seconds)
#define TEMP_HYSTERESIS 10    // (degC) range of +/- temperatures considered "close" to the target one

#define PGM_RD_W(x) (short)pgm_read_word(&x)

#define INTERRUPT_CYCLE_TEMP 30

class TemperatureClass
{
protected:
public:
  void init();
  void SetHotendTemperature(float temperature);
  bool WaitForHotendTemperature();
  void Cooldown();
  void GetTemperature();

  void ISR_EXECUTE();
  bool IsWait;

  float CurrentTemperature;

private:
  float DesiredTemperature;

  uint32_t LastTimeInt;
  float I;
  float LastError;
  uint32_t LastTime;
};

extern TemperatureClass Temperature;

#endif
