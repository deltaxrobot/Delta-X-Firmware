/**
//robot geometry
//                                          / \             RD_RF
//                                         /   \             /
//                                        /     \ Theta2    /                                   ^ Y   ^ Z
//                                       /       \ ________/____                                |    /
//                           Theta3     /         \            /                                |   /
//                                     /     *O    \          /                                 |  /
//                        RD_F_______ /             \        /                                  | /
//            ^                      /               \      /                                 __|/_____________>
//            |                      -----------------     /                                    |O             X
//            |                           Theta1          /
//            |                                          /_______RD_RE
//            |                                         /
//            |                                        /
//            |                                       /
//            |                                 / \  /
//            |                      RD_E_____ /   \/
//     RD_B   |                               /  *  \     RD_U
//            |                               -------    /
//            |                                  |      /
//            |                     RD_W________ |_____/_
//            |                                  |
//            |                                  | _______RD_V
//            |                                  ^
//____________|__________________________________________________________________________________________________________ */
#pragma once

#ifdef DELTA_X_PULY_S
#define DEFAULT_RD_F	259.04      //* 上臂長
#define DEFAULT_RD_E	120.0       //*
#define DEFAULT_RD_RF 130.0         //* 上臂長
#define DEFAULT_RD_RE	315.0

#define DEFAULT_RD_W	0.0
#define DEFAULT_RD_U	0.0
#define DEFAULT_RD_V	0.0

#define DEFAULT_MOVING_AREA_X		170
#define DEFAULT_MOVING_AREA_Y		170
#define DEFAULT_MOVING_AREA_Z	    402

#define DEFAULT_MOVING_AREA_LARGEST_DIAMETER	170			//mm

#define THETA1_HOME_POSITION -38.5				//deg -41.2	
#define THETA2_HOME_POSITION -38.5
#define THETA3_HOME_POSITION -38.5

#define THETA1_STEPS_PER_2PI  9600				//200*16*3
#define THETA2_STEPS_PER_2PI  9600
#define THETA3_STEPS_PER_2PI  9600
#endif // DELTA_X_PULY_S

#ifdef DELTA_X_V2
#define DEFAULT_RD_F	260.0   // SB			//size S  258.64 + 0.4
#define DEFAULT_RD_E	120.0	// SP = RD_E / 2
#define DEFAULT_RD_RF	120.0	// L
#define DEFAULT_RD_RE	305.0   // l

#define DEFAULT_RD_W	0.0
#define DEFAULT_RD_U	0.0
#define DEFAULT_RD_V	0.0

#define DEFAULT_MOVING_AREA_X		170
#define DEFAULT_MOVING_AREA_Y		170
#define DEFAULT_MOVING_AREA_Z	    402

#define DEFAULT_MOVING_AREA_LARGEST_DIAMETER	170			//mm

#define THETA1_HOME_POSITION -34.25				//deg -41.2	
#define THETA2_HOME_POSITION -34.25
#define THETA3_HOME_POSITION -34.25

#define THETA1_STEPS_PER_2PI  9600				//200*16*3
#define THETA2_STEPS_PER_2PI  9600
#define THETA3_STEPS_PER_2PI  9600

#endif
