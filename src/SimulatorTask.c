#include <RTL.h>
#include "SimulatorTask.h"
#include "Tasks.h"
#include "HardwareController.h"

volatile double SIM_SpaceLeft;
volatile double SIM_SpaceRight;
volatile double SIM_SpaceFront;
volatile double SIM_SpaceRear;
volatile int SIM_Lane;
volatile double SIM_Speed;
volatile double SIM_SteeringAngle;
volatile double SIM_Oil;

__task void SimulatorTask(void)
{
	SIM_SpaceLeft = 0;
  SIM_SpaceRight = 0;
  SIM_SpaceFront = 0;
  SIM_SpaceRear = 0;
  SIM_Lane = 0;
  SIM_Speed = 0;
  SIM_SteeringAngle = 0;
  SIM_Oil = 0;
	
	SIM_Speed = 30.0;
	SIM_Oil = 40.0;
	Notify_AperiodicServer(E_Speed | E_Oil);
	os_dly_wait(20);
	
	os_tsk_delete_self();
}
