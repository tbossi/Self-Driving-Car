#include <RTL.h>
#include "SimulatorTask.h"
#include "Tasks.h"
#include "CarInfo.h"
#include "HardwareController.h"

volatile double SIM_SpaceLeft = 0;
volatile double SIM_SpaceRight = 0;
volatile double SIM_SpaceFront = 0;
volatile double SIM_SpaceRear = 0;
volatile int SIM_Lane = 0;
volatile double SIM_Speed = 0;
volatile double SIM_SteeringAngle = 0;
volatile double SIM_Oil = 0;
volatile CarLocation SIM_CurrentLocation = { 0, 0 };

typedef struct Action {
  void (*func)(void);
  U16 wait;
} Action;

static void Execute(Action a)
{
	a.func();
	os_dly_wait(a.wait);
}

static void Simulate(int size, Action actions[], int loop)
{
	int counter = 0;
	do
	{
		Execute(actions[counter]);
		counter = (counter + 1) % size;
	} while (loop);
}

static void speedOil()
{
	SIM_Speed = 30.0;
	SIM_Oil = 40.0;
	Notify_AperiodicServer(E_Speed | E_Oil);
}

__task void SimulatorTask(void)
{
	Action actions[3] = {{speedOil, 200}, {speedOil, 200}, {speedOil, 200} };
	Simulate(3, actions, 1);
}
