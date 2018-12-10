#include <RTL.h>             // RTX kernel functions & defines
#include <stm32f10x.h>       // STM32F103 definitions
#include "stm32f10x_it.h"    // interrupt

#define SIMULATION
//#define DEBUG

#include "Tasks.h"
#include "TaskPriorities.h"
#include "SimulatorTask.h"

__task void TaskInitializer(void)
{
	CreateTasks();
	
	#ifdef SIMULATION
	os_tsk_create(SimulatorTask, SimulatorTaskDefaultPriority);
	#endif
  os_tsk_delete_self();
}

int main(void)
{
	os_sys_init_prio(TaskInitializer, 254);
}
