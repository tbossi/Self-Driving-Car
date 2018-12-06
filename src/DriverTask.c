#include <RTL.h>
#include "DriverTask.h"
#include "TaskPriorities.h"
#include "Tasks.h"
#include "CarInfo.h"

static void drive(CarInfo* carInfo)
{
	int isSpaceFrontAvailable = (*carinfo).Position.SpaceFront > SuggestedDistanceFromCar;
	int isSpaceRearAvailable = (*carinfo).Position.SpaceRear > SuggestedDistanceFromCar;
	
	if ( !isSpaceFrontAvailable && isSpaceRearAvailable )
	{
		// rallenta
	}
	else if (!isSpaceFrontAvailable && !isSpaceRearAvailable)
	{
		// mantieni la velocità		
	}
	else
	{
		// accelera
	}
	
	//int x;
	//for (x = 0; x < 80000; x++)
	//{
	//	x++;
	//	x--;
	//}
}

__task void DriverTask(void *argv)
{
	CarInfo* carInfo = (CarInfo*)argv;
	
	os_itv_set(DriverTaskPeriod);
	while (1)
	{
		Log_Driver_Start();
		drive(carInfo);
		Log_Driver_End();
		os_itv_wait();
	}
}
