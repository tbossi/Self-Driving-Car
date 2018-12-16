#include <rtl.h>
#include "BaseTask.h"

#include "Tasks.h"
#include "CarInfo.h"

__task void BaseTask(void *argv)
{
	//CarData* carData = (CarData*)argv;
	
	Log_Base_Start();
	while(1)
	{
		//do something
	}
}
