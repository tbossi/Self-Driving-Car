#include "HardwareController.h"

static void busyloop(int time)
{
	int x;
	for (x = 0; x < time; x++)
	{
		x++;
		x--;
	}
}

void Car_SpeedUp(int amount)
{
	busyloop(250 + 10 * amount);
}

void Car_Break(int amount)
{
	busyloop(150 + 10 * amount);
}

void Car_Steer(int angle)
{
	busyloop(80 + (15 * angle * angle)/2 );
}
