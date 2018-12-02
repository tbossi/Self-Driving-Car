#include <RTL.h>
#include "AperiodicServerTask.h"
#include "TaskPriorities.h"
#include "Tasks.h"

static void work(void)
{
	int x;
	for (x = 0; x < 8000; x++)
	{
		x++;
		x--;
	}
}

__task void AperiodicServerTask(void)
{
	os_itv_set(AperiodicServerTaskPeriod);
	while (1)
	{
		Log_AperiodicServer_Start();
		work();
		Log_AperiodicServer_End();
		os_itv_wait();
	}
}
