#include <RTL.h>
#include "DriverTask.h"
#include "TaskPriorities.h"

extern volatile int T1 = 0;

void drive(void)
{
	int x;
	for (x = 0; x < 100000; x++)
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
		T1 = 1;
		drive();
		
		T1 = 0;
		os_itv_wait();
	}
}
