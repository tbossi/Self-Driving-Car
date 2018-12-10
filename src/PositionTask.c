#include <RTL.h>
#include <math.h>
#include "PositionTask.h"
#include "TaskPriorities.h"
#include "Tasks.h"
#include "CarInfo.h"
#include "HardwareController.h"

static double distance(CarLocation a, CarLocation b)
{
	double lat;
	double lon;
	
	lat = (a.Latitude - b.Latitude) * (a.Latitude - b.Latitude);
	lon = (a.Longitude - b.Longitude) * (a.Longitude - b.Longitude);
	
	return sqrt(lat + lon);
}

static double lerp(double a, double b, double amount)
{
	return amount * a + (1.0 - amount) * b;
}

static double pseudorandomSpeed(double distance, U32 currentTick)
{
	int x = currentTick % 1009;
	if (x < 336)
		return distance / (x * 4);
	else if (x < 673)
		return distance / (x * 2);
	else
		return distance / x;	
}

static void UpdatePosition(CarData* carData) {
	U16 ret_flags;
	void* eventResult;
	
  ret_flags = Wait_CarEvent(E_GPS, 10);
	
	if ((eventResult = Get_CarEvent(E_GPS, ret_flags)) != NULL)
	{
		(*carData).NavigationInfo.CurrentPoint = * (CarLocation*)eventResult;
	}
}

static void locate(CarData* carData)
{
	CarLocation end;
	CarLocation start;
	CarLocation currentCheckPoint;	
	CarLocation nextCheckPoint;
	
	int x;
	
	UpdatePosition(carData);
	
	end = (*carData).NavigationInfo.EndingPoint;
	start = (*carData).NavigationInfo.CurrentPoint;
	
	nextCheckPoint.Latitude = lerp(end.Latitude, start.Latitude, 0.1);
	nextCheckPoint.Longitude = lerp(end.Longitude, start.Longitude, 0.1);
	currentCheckPoint = (*carData).NavigationInfo.NextCheckpoint;
	
	(*carData).NavigationInfo.NextCheckpoint = nextCheckPoint;
	(*carData).NavigationInfo.SuggestedSpeed = pseudorandomSpeed(distance(currentCheckPoint, nextCheckPoint), os_time_get());
	(*carData).CurrentCarInfo.DirectionAngle = atan2(nextCheckPoint.Longitude - currentCheckPoint.Longitude, nextCheckPoint.Latitude - currentCheckPoint.Latitude);
	
	for (x = 0; x < 800000; x++)
	{
		; //lose time
	}
}

__task void PositionTask(void *argv)
{
	CarData* carData = (CarData*)argv;
	
	os_itv_set(PositionTaskPeriod);
	while (1)
	{
		Log_Position_Start();
		locate(carData);
		Log_Position_End();
		os_itv_wait();
	}
}
