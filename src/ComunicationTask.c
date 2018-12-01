#include <RTL.h>
#include "ComunicationTask.h"
#include "TaskPriorities.h"

extern volatile int T3 = 0;

__task void ComunicationTask(void)
{
	os_itv_set(ComunicationTaskPeriod);
	while (1)
	{
		T3 = 1;
		//todo
		
		T3 = 0;
		os_itv_wait();
	}
}
