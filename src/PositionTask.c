#include <RTL.h>
#include "PositionTask.h"
#include "TaskPriorities.h"

extern volatile int T2 = 0;

__task void PositionTask(void)
{
	os_itv_set(PositionTaskPeriod);
	while (1)
	{
		T2 = 1;
		//todo
		
		T2 = 0;
		os_itv_wait();
	}
}
