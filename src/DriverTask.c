#include <RTL.h>
#include "DriverTask.h"
#include "TaskPriorities.h"
#include "Tasks.h"
#include "CarInfo.h"
#include "HardwareController.h"

static void drive(CarData* carData)
{
	U32 startingTime;
	double speed_cm_ms;
	int isSpaceFrontAvailable;
	int isSpaceRearAvailable;
	int isMaxSpeed;
	double direction;
	double currentSteeringAngle;
	
	startingTime = os_time_get();
	
	speed_cm_ms = (*carData).CurrentCarInfo.Speed / 36.0;
	
	isSpaceFrontAvailable = SpaceAvailable((*carData).CurrentCarInfo.Position.SpaceFront, speed_cm_ms, 120);
	isSpaceRearAvailable = SpaceAvailable((*carData).CurrentCarInfo.Position.SpaceRear, speed_cm_ms, 120);
	isMaxSpeed = (*carData).NavigationInfo.SuggestedSpeed <= (*carData).CurrentCarInfo.Speed;
	
	if ( (!isSpaceFrontAvailable && !isSpaceRearAvailable) || isMaxSpeed )
	{
		Car_SpeedUp(0);
	}
	else if ( !isSpaceFrontAvailable && isSpaceRearAvailable )
	{
		int amount = (int)(speed_cm_ms * 80 / (*carData).CurrentCarInfo.Position.SpaceRear);
		Car_Break(amount);
	}
	else
	{
		int amount = (int)(speed_cm_ms * 80 / (*carData).CurrentCarInfo.Position.SpaceFront * (!isSpaceRearAvailable + 1));
		Car_SpeedUp(amount);
	}
	
	direction = (*carData).CurrentCarInfo.DirectionAngle;
	currentSteeringAngle = (*carData).CurrentCarInfo.SteeringAngle;
	
	if (direction > 0.01 || direction < -0.01)  //0.01 rad = 0.57°
	{
		double newSteeringAngle = (0.3 * direction + 0.7 * currentSteeringAngle) * 180 / 3.14;
		Car_Steer((int)newSteeringAngle);
	}
	else
	{
		Car_Steer(0);
	}
	
	while (startingTime + DriverTaskCost > os_time_get()) {;} //lose time in other driving operations
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
