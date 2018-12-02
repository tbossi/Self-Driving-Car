#include <RTL.h>
#include "ComunicationTask.h"
#include "TaskPriorities.h"
#include "Tasks.h"

static void comunicate(void)
{
	int x;
	for (x = 0; x < 2400000; x++)
	{
		x++;
		x--;
	}
}

__task void ComunicationTask(void)
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
