#include <RTL.h>
#include "CarInfo.h"
#include "HardwareController.h"

// values are set by simulator task!
extern volatile double SIM_SpaceLeft;
extern volatile double SIM_SpaceRight;
extern volatile double SIM_SpaceFront;
extern volatile double SIM_SpaceRear;
extern volatile int SIM_Lane;
extern volatile double SIM_Speed;
extern volatile double SIM_SteeringAngle;
extern volatile double SIM_Oil;
extern volatile CarLocation SIM_CurrentLocation;
extern volatile CarLocation SIM_EndingPoint;
// !!!

static void busyloop(int time)
{
	int x;
	for (x = 0; x < time; x++)
	{
		x++;
		x--;
	}
}

void Car_SpeedUp(int amount)
{
	busyloop(2500 + 100 * amount);
	if (amount > 0)
	{
		SIM_Speed += 1.33 * amount;
	}
}

void Car_Break(int amount)
{
	busyloop(1500 + 100 * amount);
	if (amount > 0)
	{
		SIM_Speed -= 0.88 * amount;
	}
}

void Car_Steer(int angle)
{
	busyloop(800 + (75 * angle * angle) );
	SIM_SteeringAngle = 3.14 * angle / 180.0;
}

U16 Wait_CarEvent(U16 flags, U16 timeout)
{	
  if (os_evt_wait_or(flags, timeout) == OS_R_EVT)
	{
    return os_evt_get();
  }
	
	return 0;
}

void* Get_CarEvent(U16 event, U16 raisedFlags)
{
	U16 available = event & raisedFlags;
	if (!available) return NULL;
	
	os_evt_clr(event, os_tsk_self());
	switch(event)
	{
		case E_SpaceLeft: return (void*) &SIM_SpaceLeft;
		case E_SpaceRight: return (void*) &SIM_SpaceRight;
		case E_SpaceFront: return (void*) &SIM_SpaceFront;
		case E_SpaceRear: return (void*) &SIM_SpaceRear;
		case E_Lane: return (void*) &SIM_Lane;
		case E_Speed: return (void*) &SIM_Speed;
		case E_SteeringAngle: return (void*) &SIM_SteeringAngle;
		case E_Oil: return (void*) &SIM_Oil;
		case E_GPS: return (void*) &SIM_CurrentLocation;
		case E_EndingPoint: return (void*) &SIM_EndingPoint;
		default: return NULL;
	}
}
