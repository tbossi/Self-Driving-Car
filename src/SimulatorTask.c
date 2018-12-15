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
	void (*notify_function)(U16);
  U16 wait;
} Action;

static Callback cb(setter_pointer function, void* argument)
{
	Callback c;
	c.function = function;
  c.argument = argument;
	return c;
}

static Action action(Callback callback, U16 flags, void (*notify_function)(U16), U16 wait)
{
	Action a;
	a.callback = callback;
	a.flags = flags;
	a.notify_function = notify_function;
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

volatile int SIM_Ext_StopRequest = 0;
volatile RoadSign SIM_Ext_RoadSign = 0;
volatile NearCarInfo SIM_Ext_NearCarInfo = { 0, { 0, 0 } };
volatile CarLocation SIM_Ext_CurrentLocation = { 0, 0 };
volatile CarLocation SIM_Ext_EndingPoint = { 0, 0 };

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

__callback(stopRequest,SIM_Ext_StopRequest,int)
__callback(roadSign,SIM_Ext_RoadSign,RoadSign)
__callback(nearCarInfo,SIM_Ext_NearCarInfo,NearCarInfo)
__callback(currentLocation,SIM_Ext_CurrentLocation,CarLocation)
__callback(endingPoint,SIM_Ext_EndingPoint,CarLocation)
#undef __callback

static void Execute(Action a)
{
	if (a.callback.function != NULL) { a.callback.function(a.callback.argument); }
	a.notify_function(a.flags);
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

U16 allInternalFlags = E_SpaceLeft | E_SpaceRight | E_SpaceFront | E_SpaceRear | E_Lane | E_Speed | E_SteeringAngle | E_Oil;
U16 allExternalFlags = E_Ext_StopRequest | E_Ext_RoadSign | E_Ext_NearCarInfo | E_Ext_GPS | E_Ext_EndingPoint;

__task void SimulatorTask(void)
{
	int x;
	Action actions[50];
	x = 0;
	// resetting inputs:
	actions[x++] = action(cb(nop, &Speed_1), allInternalFlags, Notify_AperiodicServer, 0);
	actions[x++] = action(cb(nop, &Speed_1), allExternalFlags, Notify_Position, 0);
	actions[x++] = action(cb(nop, &Speed_1), allExternalFlags, Notify_Comunication, 10); 
	
	actions[x++] = action(cb(oil, &Oil_1), E_Oil, Notify_AperiodicServer, 0);
	actions[x++] = action(cb(spaceRear, &Rear_1), E_SpaceRear, Notify_AperiodicServer, 0);
	actions[x++] = action(cb(spaceLeft, &Left_1), E_SpaceLeft, Notify_AperiodicServer, 0);
	actions[x++] = action(cb(spaceFront, &Front_1), E_SpaceFront, Notify_AperiodicServer, 0);
	actions[x++] = action(cb(spaceRight, &Right_1), E_SpaceRight, Notify_AperiodicServer, 0);
	actions[x++] = action(cb(currentLocation, &Current_1), E_Ext_GPS, Notify_Position, 0);
	actions[x++] = action(cb(endingPoint, &End_1), E_Ext_EndingPoint, Notify_Position, 10);
	actions[x++] = action(cb(currentLocation, &Current_2), E_Ext_GPS, Notify_Position, 15);

	Simulate(x, actions, 1);
}
