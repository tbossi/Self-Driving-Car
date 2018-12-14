#include <RTL.h>
#include "DriverTask.h"
#include "TaskPriorities.h"
#include "Tasks.h"
#include "CarInfo.h"
#include "HardwareController.h"

static void drive(CarData* carData)
{
	U32 startingTime;
	int isSpaceFrontAvailable;
	int isSpaceRearAvailable;
	int isMaxSpeed;
	double direction;
	double currentSteeringAngle;
	
	startingTime = os_time_get();
	
	isSpaceFrontAvailable = (*carData).CurrentCarInfo.Position.SpaceFront > SuggestedDistanceFromCar;
	isSpaceRearAvailable = (*carData).CurrentCarInfo.Position.SpaceRear > SuggestedDistanceFromCar;
	isMaxSpeed = (*carData).NavigationInfo.SuggestedSpeed <= (*carData).CurrentCarInfo.Speed;
	
	direction = (*carData).CurrentCarInfo.DirectionAngle;
	currentSteeringAngle = (*carData).CurrentCarInfo.SteeringAngle;
	
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
	
	if (direction > 0.01 || direction < -0.01) { //0.01 rad = 0.57°
		double newSteeringAngle = (0.3 * direction + 0.7 * currentSteeringAngle) * 180 / 3.14;
		Car_Steer((int)newSteeringAngle);
	} else {
		Car_Steer(0);
	}
	
	while (startingTime + 10 > os_time_get()) {;} //lose time in other driving operations
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
