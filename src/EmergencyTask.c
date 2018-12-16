#include <rtl.h>
#include "EmergencyTask.h"

#include "Tasks.h"
#include "CarInfo.h"
#include "HardwareController.h"

static void HandleEmergency(CarData* carData)
{
	while (IsEmergency(carData))
	{
		// do something to handle the emergency
		int x;
		Car_Break(5);
		Car_Steer(30);
		
		x = (os_time_get() % 131) * 10 + 83;
		while (x > 1)
		{
			if (x % 1000)
			{
				Car_Break(5);
				Car_Steer(-30);
			}
			x--;
		}
	}
}

__task void EmergencyTask(void *argv)
{
	CarData* carData = (CarData*)argv;
	
	while(1)
	{
		Log_Emergency_Start();
		HandleEmergency(carData);
		Log_Emergency_End();
		Emergency_Sleep();
	}
}
