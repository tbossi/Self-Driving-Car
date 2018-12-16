#include <RTL.h>

typedef struct TaskTracker
{
	OS_TID id;
	volatile int running;
	struct TaskTracker* preempted;
} TaskTracker;

void Log_AperiodicServer_Start(void);
void Log_AperiodicServer_End(void);
void Log_Driver_Start(void);
void Log_Driver_End(void);
void Log_Position_Start(void);
void Log_Position_End(void);
void Log_Comunication_Start(void);
void Log_Comunication_End(void);
void Log_Emergency_Start(void);
void Log_Emergency_End(void);
void Log_Base_Start(void);

void Notify_AperiodicServer(U16 flags);
void Notify_Driver(U16 flags);
void Notify_Position(U16 flags);
void Notify_Comunication(U16 flags);
void Notify_Emergency(U16 flags);

void Emergency_Wake(void);
void Emergency_Sleep(void);

void CreateTasks(void);
