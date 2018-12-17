#include <RTL.h>
#include "SimulatorTask.h"
#include "Tasks.h"
#include "CarInfo.h"
#include "HardwareController.h"

/*** Structs to handle action to simulate ***/
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

static double Speed_1 = 30.0;
static double Speed_2 = 20.0;
static double Speed_3 = 50.0;
static double SteeringAngle_1 = 0;
static double Oil_1 = 40.0;
static double Oil_2 = 10.0;

static double goodSpace_1 = 90;
static double goodSpace_2 = 193;
static double badSpace_1 = 1;

static int Lane_1 = 0;
static CarLocation Current_1 = { 13.5006, 17.6445 };
static CarLocation Current_2 = { 14.1924, 16.5643 };
static CarLocation End_1 = { 19.197, 2.0078 };

static U16 allInternalFlags = E_SpaceLeft | E_SpaceRight | E_SpaceFront | E_SpaceRear | E_Lane | E_Speed | E_SteeringAngle | E_Oil;
static U16 allExternalFlags = E_Ext_StopRequest | E_Ext_RoadSign | E_Ext_NearCarInfo | E_Ext_GPS | E_Ext_EndingPoint;

static void ResetAll(int wait)
{
	// resetting inputs to 0:
	Execute(action(cb(nop, &Speed_1), allInternalFlags, Notify_AperiodicServer, 0));
	Execute(action(cb(nop, &Speed_1), allExternalFlags, Notify_Position, 0));
	Execute(action(cb(nop, &Speed_1), allExternalFlags, Notify_Comunication, wait)); 
}

static void EventSet1(int wait)
{
	Execute(action(cb(oil, &Oil_1), E_Oil, Notify_AperiodicServer, 0));
	Execute(action(cb(spaceRear, &goodSpace_1), E_SpaceRear, Notify_AperiodicServer, 0));
	Execute(action(cb(spaceLeft, &goodSpace_1), E_SpaceLeft, Notify_AperiodicServer, 0));
	Execute(action(cb(spaceFront, &goodSpace_1), E_SpaceFront, Notify_AperiodicServer, 0));
	Execute(action(cb(spaceRight, &goodSpace_1), E_SpaceRight, Notify_AperiodicServer, 0));
	Execute(action(cb(speed, &Speed_2), E_Speed, Notify_AperiodicServer, 0));
	Execute(action(cb(currentLocation, &Current_1), E_Ext_GPS, Notify_Position, 0));
	Execute(action(cb(endingPoint, &End_1), E_Ext_EndingPoint, Notify_Position, 10));
	Execute(action(cb(currentLocation, &Current_2), E_Ext_GPS, Notify_Position, wait));
}

static void EventSet2(int wait)
{
	Execute(action(cb(oil, &Oil_2), E_Oil, Notify_AperiodicServer, 0));
	Execute(action(cb(spaceRear, &goodSpace_2), E_SpaceRear, Notify_AperiodicServer, 0));
	Execute(action(cb(spaceLeft, &goodSpace_2), E_SpaceLeft, Notify_AperiodicServer, 0));
	Execute(action(cb(spaceFront, &goodSpace_2), E_SpaceFront, Notify_AperiodicServer, 0));
	Execute(action(cb(spaceRight, &goodSpace_2), E_SpaceRight, Notify_AperiodicServer, 0));
	Execute(action(cb(speed, &Speed_3), E_Speed, Notify_AperiodicServer, 0));
	Execute(action(cb(currentLocation, &Current_1), E_Ext_GPS, Notify_Position, 0));
	Execute(action(cb(endingPoint, &End_1), E_Ext_EndingPoint, Notify_Position, 10));
	Execute(action(cb(currentLocation, &Current_2), E_Ext_GPS, Notify_Position, wait));
}

static void Emergency1(int wait)
{
	Execute(action(cb(speed, &Speed_1), E_Speed, Notify_AperiodicServer, 0));
	Execute(action(cb(spaceRight, &badSpace_1), E_SpaceRight, Notify_AperiodicServer, wait));
}

static void Emergency2(int wait)
{
	Execute(action(cb(speed, &Speed_2), E_Speed, Notify_AperiodicServer, 0));
	Execute(action(cb(spaceFront, &badSpace_1), E_SpaceFront, Notify_AperiodicServer, wait));
}

__task void SimulatorTask(void)
{
	ResetAll(10);
	
	while(1)
	{
		int x;
		for (x = 0; x < 98; x++)
		{
			if (x % 6) { EventSet1(17); }
			else { EventSet2(15); }
		}
		
		Emergency1(233);
	}
}
