#include <rtl.h>
#include "EmergencyTask.h"

#include "Tasks.h"
#include "CarInfo.h"
#include "HardwareController.h"

static void HandleEmergency(CarData* carData)
{
	int emergencyEnd = 0;
	while (!emergencyEnd)
	{
		Car_Break(5);
		Car_Steer(30);
		
		emergencyEnd = (os_time_get() % 131) * 100 + 893;
		while (emergencyEnd > 1) {emergencyEnd--;}
		
		emergencyEnd = !IsEmergency(carData);
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
