#include <RTL.h>

#include "TaskPriorities.h"
#include "DriverTask.h"
#include "PositionTask.h"
#include "ComunicationTask.h"
#include "AperiodicServerTask.h"

#include "Tasks.h"
#include "CarInfo.h"

extern volatile int IDLE = 0;

TaskTracker Driver;
TaskTracker Position;
TaskTracker Comunication;
TaskTracker AperiodicServer;

void Log_Driver_Start(void)
{
	Driver.running = 1;
	IDLE = 0;
}

void Log_Driver_End(void)
{
	Driver.running = 0;
}

void Log_Position_Start(void)
{
	Position.running = 1;
	IDLE = 0;
}

void Log_Position_End(void)
{
	Position.running = 0;
}

void Log_Comunication_Start(void)
{
	Comunication.running = 1;
	IDLE = 0;
}

void Log_Comunication_End(void)
{
	Comunication.running = 0;
}

void Log_AperiodicServer_Start(void)
{
	AperiodicServer.running = 1;
	IDLE = 0;
}

void Log_AperiodicServer_End(void)
{
	AperiodicServer.running = 0;
}

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
	
	Driver = createTask(DriverTask, DriverTaskDefaultPriority, &carData);
	Position = createTask(PositionTask, PositionTaskDefaultPriority, &carData);
	Comunication = createTask(ComunicationTask, ComunicationTaskDefaultPriority, &carData);
	AperiodicServer = createTask(AperiodicServerTask, AperiodicServerTaskDefaultPriority, &carData);
}
