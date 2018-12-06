#include "CarInfo.h"

CarInfo CarInfo_GetClearInstance(void)
{
	CarInfo carInfo;
	CarPosition pos;
	CarLocation loc;
	
	loc.Latitude = 0;
	loc.Longitude = 0;
	
	pos.SpaceLeft = 0;
	pos.SpaceRight = 0;
	pos.SpaceFront = 0;
	pos.SpaceRear = 0;
	pos.Lane = 0;
	pos.Location = loc;
	
	carInfo.Speed = 0;
	carInfo.Acceleration = 0;
	carInfo.SteeringAngle = 0;
	carInfo.Position = pos;
	
	return carInfo;
}
