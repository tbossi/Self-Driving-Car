#include <RTL.h>
#include "PositionTask.h"
#include "TaskPriorities.h"
#include "Tasks.h"

static void locate(void)
{
	int x;
	for (x = 0; x < 1200000; x++)
	{
		x++;
		x--;
	}
}

__task void PositionTask(void)
{
	os_itv_set(PositionTaskPeriod);
	while (1)
	{
		Log_Position_Start();
		locate();
		Log_Position_End();
		os_itv_wait();
	}
}
