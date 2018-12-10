#include <RTL.h>
#include "DriverTask.h"
#include "TaskPriorities.h"
#include "Tasks.h"
#include "CarInfo.h"
#include "HardwareController.h"

static void drive(CarData* carData)
{
	int isSpaceFrontAvailable;
	int isSpaceRearAvailable;
	int isMaxSpeed;
	isSpaceFrontAvailable = (*carData).CurrentCarInfo.Position.SpaceFront > SuggestedDistanceFromCar;
	isSpaceRearAvailable = (*carData).CurrentCarInfo.Position.SpaceRear > SuggestedDistanceFromCar;
	isMaxSpeed = (*carData).NavigationInfo.SuggestedSpeed <= (*carData).CurrentCarInfo.Speed;
	
	if ( !isSpaceFrontAvailable && isSpaceRearAvailable )
	{
		int amount = (*carData).CurrentCarInfo.Position.SpaceRear / SuggestedDistanceFromCar;
		Car_Break(amount);
	}
	else if ( (!isSpaceFrontAvailable && !isSpaceRearAvailable) || isMaxSpeed )
	{
		Car_SpeedUp(0);	
	}
	else
	{
		int amount = (*carData).CurrentCarInfo.Position.SpaceFront / SuggestedDistanceFromCar;
		Car_SpeedUp(amount);
	}
}

__task void DriverTask(void *argv)
{
	CarData* carData = (CarData*)argv;
	
	os_itv_set(DriverTaskPeriod);
	while (1)
	{
		Log_Driver_Start();
		drive(carData);
		Log_Driver_End();
		os_itv_wait();
	}
}
