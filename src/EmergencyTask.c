#include <rtl.h>
#include "EmergencyTask.h"

#include "Tasks.h"
#include "CarInfo.h"

static void HandleEmergency(CarData* carData)
{
	int emergencyEnd = 0;
	while (!emergencyEnd)
	{
		emergencyEnd = 1;
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
