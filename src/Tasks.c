#include <RTL.h>

#include "TaskPriorities.h"
#include "AperiodicServerTask.h"
#include "DriverTask.h"
#include "PositionTask.h"
#include "ComunicationTask.h"
#include "BaseTask.h"
#include "EmergencyTask.h"

#include "Tasks.h"
#include "CarInfo.h"

TaskTracker AperiodicServer;
TaskTracker Driver;
TaskTracker Position;
TaskTracker Comunication;
TaskTracker Base;
TaskTracker Emergency;

static TaskTracker* runningTask; 

#define __log_start(taskName) void Log_##taskName##_Start(void)\
																{\
																	(*runningTask).running = 0;\
																	taskName.running = 1;\
																	taskName.preempted = runningTask;\
																	runningTask = &taskName;\
																}

#define __log_end(taskName) void Log_##taskName##_End(void)\
															{\
																taskName.running = 0;\
																runningTask = taskName.preempted;\
																(*runningTask).running = 1;\
															}

__log_start(AperiodicServer)
__log_end(AperiodicServer)
__log_start(Driver)
__log_end(Driver)
__log_start(Position)
__log_end(Position)
__log_start(Comunication)
__log_end(Comunication)
__log_start(Emergency)
__log_end(Emergency)
__log_start(Base)

#undef __log_start
#undef __log_end

#define __notify(taskName) void Notify_##taskName##(U16 flags) { os_evt_set(flags, taskName.id); }
__notify(AperiodicServer)
__notify(Driver)
__notify(Position)
__notify(Comunication)
__notify(Emergency)
#undef __notify

void Emergency_Wake(void) { os_tsk_prio(Emergency.id, EmergencyTaskHighPriority); }
void Emergency_Sleep(void) { os_tsk_prio(Emergency.id, EmergencyTaskDefaultPriority); }

TaskTracker createTask(void (*task)(void *), U8 priority, void* argv)
{
	TaskTracker t;
	t.running = 0;
	t.id = os_tsk_create_ex(task, priority, argv);
	return t;
}

void CreateTasks(void)
{
	static int alreadyCreated = 0;
	CarData carData;
	
	if (alreadyCreated) return;
	alreadyCreated = 1;
	
	carData = CarData_GetClearInstance();
	
	AperiodicServer = createTask(AperiodicServerTask, AperiodicServerTaskDefaultPriority, &carData);
	Driver = createTask(DriverTask, DriverTaskDefaultPriority, &carData);
	Position = createTask(PositionTask, PositionTaskDefaultPriority, &carData);
	Comunication = createTask(ComunicationTask, ComunicationTaskDefaultPriority, &carData);
	Base = createTask(BaseTask, BaseTaskDefaultPriority, &carData);
	Emergency = createTask(EmergencyTask, EmergencyTaskDefaultPriority, &carData);
	
	runningTask = &Base;
}
