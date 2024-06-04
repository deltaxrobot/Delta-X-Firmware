/**
 * Delta 運動學 頭檔
 */

#ifndef _DELTAKINEMATICS_h
#define _DELTAKINEMATICS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Constants.h"

using namespace std;

//trigonometric constants
const double tan30 = 1 / sqrt(3);
const double tan30x05 = 0.5 / sqrt(3);
const double tan60 = sqrt(3);
const double sin30 = 0.5;
const double cos30 = sqrt(3) / 2;
const double cos120 = -0.5;
const double sin120 = sqrt(3) / 2;

class DeltaKinematicsClass
{
 protected:


 public:
	void init();
	bool ForwardKinematicsCalculations(Angle angleposition, Point &point);
	bool InverseKinematicsCalculations(Point point, Angle &angleposition);

private:
	bool AngleThetaCalculations(float x0, float y0, float z0, float &theta);
	float _y0_;
	float _y1_;
	float RD_RF_Pow2;
	float RD_RE_Pow2;
};

extern DeltaKinematicsClass DeltaKinematics;

#endif

