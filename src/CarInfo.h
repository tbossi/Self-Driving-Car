#ifndef CAR_INFO_H
#define CAR_INFO_H

#define SuggestedDistanceFromCar 60;

typedef struct CarLocation
{
	double Latitude;
	double Longitude;
} CarLocation;

typedef struct CarPosition
{
	double SpaceLeft;  // distance in cm
	double SpaceRight; // distance in cm
	double SpaceFront; // distance in cm
	double SpaceRear;  // distance in cm
	
	int Lane;
	
	CarLocation Location;
} CarPosition;

typedef struct CarInfo
{
	double Speed;
	double Acceleration;
	double SteeringAngle;
	CarPosition Position;
} CarInfo;


CarInfo CarInfo_GetClearInstance(void);

#endif
