#include <RTL.h>
#include "DriverTask.h"
#include "TaskPriorities.h"
#include "Tasks.h"

static void drive(void)
{
	int x;
	for (x = 0; x < 80000; x++)
	{
		x++;
		x--;
	}
}

__task void DriverTask(void)
{
	os_itv_set(DriverTaskPeriod);
	while (1)
	{
		Log_Driver_Start();
		drive();
		Log_Driver_End();
		os_itv_wait();
	}
}
