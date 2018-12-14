#ifndef CAR_INFO_H
#define CAR_INFO_H

#define SuggestedDistanceFromCar 60;
#define SuggestedLateralDistance 10;

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
	
	double SuggestedSpeed;
	
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
	double Speed;
	double DirectionAngle; 
	double SteeringAngle;
	double Oil;
	
	CarPosition Position;
} CarInfo;

typedef struct CarData
{
	CarInfo CurrentCarInfo;
	NavigationInfo NavigationInfo;
} CarData;

CarData CarData_GetClearInstance(void);

#endif
