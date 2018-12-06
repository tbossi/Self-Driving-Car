#include <RTL.h>

typedef struct TaskTracker
{
	OS_TID id;
	volatile int running;
} TaskTracker;

void Log_Driver_Start(void);
void Log_Driver_End(void);
void Log_Position_Start(void);
void Log_Position_End(void);
void Log_Comunication_Start(void);
void Log_Comunication_End(void);
void Log_AperiodicServer_Start(void);
void Log_AperiodicServer_End(void);
void Log_Idle_Start(void);

void CreateTasks(void);
