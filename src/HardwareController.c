#include <RTL.h>
#include "HardwareController.h"

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
	busyloop(250 + 10 * amount);
}

void Car_Break(int amount)
{
	busyloop(150 + 10 * amount);
}

void Car_Steer(int angle)
{
	busyloop(80 + (15 * angle * angle)/2 );
}

// values are set by simulator task!
extern volatile double SIM_SpaceLeft;
extern volatile double SIM_SpaceRight;
extern volatile double SIM_SpaceFront;
extern volatile double SIM_SpaceRear;
extern volatile int SIM_Lane;
extern volatile double SIM_Speed;
extern volatile double SIM_SteeringAngle;
extern volatile double SIM_Oil;
// !!!

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
		case E_SpaceLeft: return &SIM_SpaceLeft;
		case E_SpaceRight: return &SIM_SpaceRight;
		case E_SpaceFront: return &SIM_SpaceFront;
		case E_SpaceRear: return &SIM_SpaceRear;
		case E_Lane: return &SIM_Lane;
		case E_Speed: return &SIM_Speed;
		case E_SteeringAngle: return &SIM_SteeringAngle;
		case E_Oil: return &SIM_Oil;
		default: return NULL;
	}
}
