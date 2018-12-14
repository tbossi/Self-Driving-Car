#include <RTL.h>
#include "AperiodicServerTask.h"
#include "TaskPriorities.h"
#include "Tasks.h"
#include "HardwareController.h"
#include "CarInfo.h"

static void GetSensorData(CarData* carData)
{
	U32 startingTime;
	U16 flags;
	U16 ret_flags;
	void* eventResult;
	
	startingTime = os_time_get();
	
	flags = E_SpaceLeft | E_SpaceRight | E_SpaceFront | E_SpaceRear | E_Lane | E_Speed | E_SteeringAngle | E_Oil;
  ret_flags = Wait_CarEvent(flags, 1);
	
	if ((eventResult = Get_CarEvent(E_SpaceLeft, ret_flags)) != NULL)
	{
		(*carData).CurrentCarInfo.Position.SpaceLeft = * (double*)eventResult;
	}
	
	if ((eventResult = Get_CarEvent(E_SpaceRight, ret_flags)) != NULL)
	{
		(*carData).CurrentCarInfo.Position.SpaceRight = * (double*)eventResult;
	}
	
	if ((eventResult = Get_CarEvent(E_SpaceFront, ret_flags)) != NULL)
	{
		(*carData).CurrentCarInfo.Position.SpaceFront = * (double*)eventResult;
	}
	
	if ((eventResult = Get_CarEvent(E_SpaceRear, ret_flags)) != NULL)
	{
		(*carData).CurrentCarInfo.Position.SpaceRear = * (double*)eventResult;
	}
	
	if ((eventResult = Get_CarEvent(E_Lane, ret_flags)) != NULL)
	{
		(*carData).CurrentCarInfo.Position.Lane = * (int*)eventResult;
	}
	
	if ((eventResult = Get_CarEvent(E_Speed, ret_flags)) != NULL)
	{
		(*carData).CurrentCarInfo.Speed = * (double*)eventResult;
	}
	
	if ((eventResult = Get_CarEvent(E_SteeringAngle, ret_flags)) != NULL)
	{
		(*carData).CurrentCarInfo.SteeringAngle = * (double*)eventResult;
	}
	
	if ((eventResult = Get_CarEvent(E_Oil, ret_flags)) != NULL)
	{
		(*carData).CurrentCarInfo.Oil = * (double*)eventResult;
	}
	
	//TODO far partire emergency task se c'è emergenza
	
	while (startingTime + 1 > os_time_get()) {;} //lose time in other driving operations
}

__task void AperiodicServerTask(void *argv)
{
	CarData* carData = (CarData*)argv;
	
	os_itv_set(AperiodicServerTaskPeriod);
	while (1)
	{
		Log_AperiodicServer_Start();
		GetSensorData(carData);
		Log_AperiodicServer_End();
		os_itv_wait();
	}
}
