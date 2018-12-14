#include <RTL.h>
#include "SimulatorTask.h"
#include "Tasks.h"
#include "CarInfo.h"
#include "HardwareController.h"

/*** Structs for handle action to simulate ***/
typedef void (*setter_pointer)(void*);
typedef struct Callback
{
  setter_pointer function;
  void* argument;
} Callback;

typedef struct Action
{
	Callback callback;
	U16 flags;
  U16 wait;
} Action;

static Callback cb(setter_pointer function, void* argument)
{
	Callback c;
	c.function = function;
  c.argument = argument;
	return c;
}

static Action action(Callback callback, U16 flags, U16 wait)
{
	Action a;
	a.callback = callback;
	a.flags = flags;
	a.wait =  wait;
	return a;
}

/*** Shared variables ***/

volatile double SIM_SpaceLeft = 0;
volatile double SIM_SpaceRight = 0;
volatile double SIM_SpaceFront = 0;
volatile double SIM_SpaceRear = 0;
volatile int SIM_Lane = 0;
volatile double SIM_Speed = 0;
volatile double SIM_SteeringAngle = 0;
volatile double SIM_Oil = 0;
volatile CarLocation SIM_CurrentLocation = { 0, 0 };
volatile CarLocation SIM_EndingPoint = { 0, 0 };

#ifdef __callback
#undef __callback
#endif
#define __callback(_name_,_variable_,_type_) static void _name_(void* value) { _variable_ = * (_type_*) value; }
static void nop(void* value) {}
__callback(spaceLeft,SIM_SpaceLeft,double)
__callback(spaceRight,SIM_SpaceRight,double)
__callback(spaceFront,SIM_SpaceFront,double)
__callback(spaceRear,SIM_SpaceRear,double)
__callback(lane,SIM_Lane,int)
__callback(speed,SIM_Speed,double)
__callback(steeringAngle,SIM_SteeringAngle,double)
__callback(oil,SIM_Oil,double)
__callback(currentLocation,SIM_CurrentLocation,CarLocation)
__callback(endingPoint,SIM_EndingPoint,CarLocation)
#undef __callback

static void Execute(Action a)
{
	if (a.callback.function != NULL) { a.callback.function(a.callback.argument); }
	Notify_AperiodicServer(a.flags);
	if (a.wait > 0) { os_dly_wait(a.wait); }
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

double Speed_1 = 30.0;
double Speed_2 = 20.0;
double SteeringAngle_1 = 0;
double Oil_1 = 40.0;
double Left_1 = 80;
double Right_1 = 20;
double Front_1 = 90.0;
double Rear_1 = 50.0;
int Lane_1 = 0;
CarLocation Current_1 = { 13.5006, 17.6445 };
CarLocation Current_2 = { 14.1924, 16.5643 };
CarLocation End_1 = { 19.197, 2.0078 };

U16 allFlags = E_SpaceLeft | E_SpaceRight | E_SpaceFront | E_SpaceRear | E_Lane | E_Speed | E_SteeringAngle | E_Oil | E_GPS | E_EndingPoint;

__task void SimulatorTask(void)
{
	int x;
	Action actions[50];
	x = 0;
	actions[x++] = action(cb(nop, &Speed_1), allFlags, 10);
	actions[x++] = action(cb(oil, &Oil_1), E_Oil, 0);
	actions[x++] = action(cb(spaceRear, &Rear_1), E_SpaceRear, 0);
	actions[x++] = action(cb(spaceLeft, &Left_1), E_SpaceLeft, 0);
	actions[x++] = action(cb(spaceFront, &Front_1), E_SpaceFront, 0);
	actions[x++] = action(cb(spaceRight, &Right_1), E_SpaceRight, 0);
	actions[x++] = action(cb(currentLocation, &Current_1), E_GPS, 0);
	actions[x++] = action(cb(endingPoint, &End_1), E_EndingPoint, 10);
	actions[x++] = action(cb(currentLocation, &Current_2), E_GPS, 15);

	Simulate(x, actions, 1);
}
