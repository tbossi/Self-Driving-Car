#ifndef CAR_INFO_H
#define CAR_INFO_H

typedef unsigned int RoadSign;

typedef struct CarLocation
{
	double Latitude;
	double Longitude;
} CarLocation;

typedef struct NavigationInfo
{
	CarLocation EndingPoint;
	CarLocation NextCheckpoint;
	CarLocation CurrentPoint;
	
	double SuggestedSpeed; // km/h
	
	RoadSign RoadSign;
	int StopRequest;
	// other info from maps/cars/signals
	
} NavigationInfo;

typedef struct CarPosition
{
	double SpaceLeft;  // distance in cm
	double SpaceRight; // distance in cm
	double SpaceFront; // distance in cm
	double SpaceRear;  // distance in cm
	
	int Lane;
} CarPosition;

typedef struct CarInfo
{
	double Speed; // km/h
	double DirectionAngle; // radians 
	double SteeringAngle; // radians
	double Oil; // liters
	
	CarPosition Position;
} CarInfo;

typedef struct CarData
{
	CarInfo CurrentCarInfo;
	NavigationInfo NavigationInfo;
} CarData;

typedef struct NearCarInfo
{
	double CurrentSpeed;
	CarLocation CurrentLocation;
} NearCarInfo;

CarData CarData_GetClearInstance(void);

#endif
