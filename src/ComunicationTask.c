#include <RTL.h>
#include "ComunicationTask.h"
#include "TaskPriorities.h"
#include "Tasks.h"

static void comunicate(void)
{
	U32 startingTime;
	startingTime = os_time_get();
	
	
	while (startingTime + 300 > os_time_get()) {;} //lose time in other comunication operations
}

__task void ComunicationTask(void *argv)
{
	os_itv_set(ComunicationTaskPeriod);
	while (1)
	{
		Log_Comunication_Start();
		comunicate();
		Log_Comunication_End();
		os_itv_wait();
	}
}
