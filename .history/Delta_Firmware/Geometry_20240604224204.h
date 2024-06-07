/**
//robot geometry
//                                   / \             RD_RF
//                                  /   \             /
//                                 /     \ Theta2    /                 ^ Y   ^ Z
//                                /       \ ________/____              |    /
//                    Theta3     /         \            /              |   /
//                              /     *O    \          /               |  /
//                 RD_F_______ /             \        /                | /
//            ^               /               \      /               __|/_____________>
//            |               -----------------     /                  |O             X
//            |                    Theta1          /
//            |                                   /_______RD_RE
//            |                                  /
//            |                                 /
//            |                                /
//            |                          / \  /
//            |               RD_E_____ /   \/
//     RD_B   |                        /  *  \     RD_U
//            |                        -------    /
//            |                           |      /
//            |              RD_W________ |_____/_
//            |                           |
//            |                           | _______RD_V
//            |                           ^
//____________|__________________________________________________________________________________________________________ */
#pragma once

#define DEFAULT_RD_F	350.0       //* 固定座邊長
#define DEFAULT_RD_E	120.0       //* 效應器邊長
#define DEFAULT_RD_RF 250.0       //* 上臂長
#define DEFAULT_RD_RE	550.0       //* 下臂長

#define DEFAULT_RD_W	40.0         //* 執行器高度
#define DEFAULT_RD_U	0.0         //* 無用
#define DEFAULT_RD_V	0.0         //* 無用

#define DEFAULT_MOVING_AREA_X 300
#define DEFAULT_MOVING_AREA_Y 300
#define DEFAULT_MOVING_AREA_Z 700

//@ 預設移動區域最大直徑
#define DEFAULT_MOVING_AREA_LARGEST_DIAMETER	600			//mm

//@ 極限開關角度
#define THETA1_HOME_POSITION -41.2				//deg -41.2	
#define THETA2_HOME_POSITION -41.2
#define THETA3_HOME_POSITION -41.2

//@ 步進數/圈
#define THETA1_STEPS_PER_2PI 19200				// 200 * 細分數(32) * 皮帶比(3)
#define THETA2_STEPS_PER_2PI 19200
#define THETA3_STEPS_PER_2PI 19200