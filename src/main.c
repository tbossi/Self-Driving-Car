#include <RTL.h>             // RTX kernel functions & defines
#include <stm32f10x.h>       // STM32F103 definitions
#include "stm32f10x_it.h"    // interrupt

#include "TaskPriorities.h"
#include "SimulatorTask.h"

extern volatile int T1 = 0;
extern volatile int IDLE = 0;

OS_TID SimulatorTaskId;

__task void TaskInitializer(void)
{
	SimulatorTaskId = os_tsk_create(SimulatorTask, SimulatorTaskDefaultPriority);
  os_tsk_delete_self();
}

int main(void)
{
	os_sys_init(TaskInitializer);
}
