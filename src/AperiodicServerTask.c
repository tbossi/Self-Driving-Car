#include <RTL.h>
#include "AperiodicServerTask.h"
#include "TaskPriorities.h"

extern volatile int T4 = 0;

__task void AperiodicServerTask(void)
{
	os_itv_set(AperiodicServerTaskPeriod);
	while (1)
	{
		T4 = 1;
		//todo
		
		T4 = 0;
		os_itv_wait();
	}
}
