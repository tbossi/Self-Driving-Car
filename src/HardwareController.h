#include <RTL.h>

#ifndef HARDWARE_CONTROLLER_H
#define HARDWARE_CONTROLLER_H

#define E_SpaceLeft			1
#define E_SpaceRight 		2
#define E_SpaceFront 		4
#define E_SpaceRear 		8
#define E_Lane 					16
#define E_Speed 				32
#define E_SteeringAngle 64
#define E_Oil 					128

void Car_SpeedUp(int amount);
void Car_Break(int amount);
void Car_Steer(int angle);

U16 Wait_CarEvent(U16 flags, U16 timeout);
void* Get_CarEvent(U16 event, U16 raisedFlags);

#endif
