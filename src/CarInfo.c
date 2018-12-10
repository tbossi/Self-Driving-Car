#include "CarInfo.h"

static NavigationInfo NavigationInfo_GetClearInstance(void)
{
	NavigationInfo info;
	CarLocation start;
	CarLocation end;
	CarLocation next;
	CarLocation current;
	
	start.Latitude = 0;
	start.Longitude = 0;
	end.Latitude = 0;
	end.Longitude = 0;
	next.Latitude = 0;
	next.Longitude = 0;
	current.Latitude = 0;
	current.Longitude = 0;
	
	info.StartingPoint = start;
	info.EndingPoint = end;
	info.NextCheckpoint = next;
	info.CurrentPoint = current;
	info.SuggestedSpeed = 0;
	
	return info;
}

static CarInfo CarInfo_GetClearInstance(void)
{
	CarInfo carInfo;
	CarPosition pos;
	
	pos.SpaceLeft = 0;
	pos.SpaceRight = 0;
	pos.SpaceFront = 0;
	pos.SpaceRear = 0;
	pos.Lane = 0;
	
	carInfo.Speed = 0;
	carInfo.DirectionAngle = 0;
	carInfo.SteeringAngle = 0;
	carInfo.Position = pos;
	
	return carInfo;
}

CarData CarData_GetClearInstance(void)
{
	CarData data;	
	data.CurrentCarInfo = CarInfo_GetClearInstance();
	data.NavigationInfo = NavigationInfo_GetClearInstance();
	
	return data;
}