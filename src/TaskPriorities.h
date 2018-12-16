#ifndef TASK_PRIORITIES_H
	#define TASK_PRIORITIES_H
	
	#ifdef DEBUG
		#define DEMULTIPLIER 0.2
	#else
		#define DEMULTIPLIER 1
	#endif

	#define AperiodicServerTaskDefaultPriority 100
	#define AperiodicServerTaskPeriod (U16)(DEMULTIPLIER * 10)
	#define AperiodicServerTaskCost (U16)(DEMULTIPLIER * 1)

	#define DriverTaskDefaultPriority 80
	#define DriverTaskPeriod (U16)(DEMULTIPLIER * 100)
	#define DriverTaskCost (U16)(DEMULTIPLIER * 10)
	
	#define PositionTaskDefaultPriority 40
	#define PositionTaskPeriod (U16)(DEMULTIPLIER * 500)
	#define PositionTaskCost (U16)(DEMULTIPLIER * 150)
	
	#define ComunicationTaskDefaultPriority 20
	#define ComunicationTaskPeriod (U16)(DEMULTIPLIER * 2000)
	#define ComunicationTaskCost (U16)(DEMULTIPLIER * 300)
	
	#define BaseTaskDefaultPriority 10
	
	#define EmergencyTaskHighPriority 90
	#define EmergencyTaskDefaultPriority 1
	
	#define SimulatorTaskDefaultPriority 130
#endif
