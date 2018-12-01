#include <RTL.h>             // RTX kernel functions & defines
#include <stm32f10x.h>       // STM32F103 definitions
#include "stm32f10x_it.h"    // interrupt

//#define SIMULATION
#define DEBUG

#include "TaskPriorities.h"
#include "DriverTask.h"
#include "PositionTask.h"
#include "ComunicationTask.h"
#include "AperiodicServerTask.h"
#include "SimulatorTask.h"

extern volatile int IDLE = 0;

OS_TID DriverTaskId;
OS_TID PositionTaskId;
OS_TID ComunicationTaskId;
OS_TID AperiodicServerTaskId;

__task void TaskInitializer(void)
{
	DriverTaskId = os_tsk_create(DriverTask, DriverTaskDefaultPriority);
	PositionTaskId = os_tsk_create(PositionTask, PositionTaskDefaultPriority);
	ComunicationTaskId = os_tsk_create(ComunicationTask, ComunicationTaskDefaultPriority);
	AperiodicServerTaskId = os_tsk_create(AperiodicServerTask, AperiodicServerTaskDefaultPriority);
	
	#ifdef SIMULATION
	OS_TID SimulatorTaskId = os_tsk_create(SimulatorTask, SimulatorTaskDefaultPriority);
	#endif
  os_tsk_delete_self();
}

int main(void)
{
	os_sys_init(TaskInitializer);
}
