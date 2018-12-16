#include <RTL.h>
#include "CarInfo.h"

#ifndef HARDWARE_CONTROLLER_H
#define HARDWARE_CONTROLLER_H

// Internal events
#define E_SpaceLeft			1
#define E_SpaceRight 		2
#define E_SpaceFront 		4
#define E_SpaceRear 		8
#define E_Lane 					16
#define E_Speed 				32
#define E_SteeringAngle 64
#define E_Oil 					128

// External events
#define E_Ext_StopRequest		1
#define E_Ext_RoadSign			2
#define E_Ext_NearCarInfo		4
#define E_Ext_GPS 					8
#define E_Ext_EndingPoint		16

void Car_SpeedUp(int amount);
void Car_Break(int amount);
void Car_Steer(int angle);
void Broadcast_CarInfo(NearCarInfo info);

int SpaceAvailable(double space, double speed_cm_ms, int millis);
int IsEmergency(CarData* carData);

U16 Wait_CarEvent(U16 flags, U16 timeout);
void* Get_CarEvent(U16 event, U16 raisedFlags);

U16 Wait_ExternalEvent(U16 flags, U16 timeout);
void* Get_ExternalEvent(U16 event, U16 raisedFlags);

#endif
