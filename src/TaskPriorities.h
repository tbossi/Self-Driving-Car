#ifndef TASK_PRIORITIES_H
	#define TASK_PRIORITIES_H
	
	#ifdef DEBUG
		#define DEMULTIPLIER 0.2
	#else
		#define DEMULTIPLIER 1
	#endif

	#define DriverTaskDefaultPriority 50
	#define DriverTaskPeriod (U16)(DEMULTIPLIER * 10)
	
	#define PositionTaskDefaultPriority 40
	#define PositionTaskPeriod (U16)(DEMULTIPLIER * 50)
	
	#define ComunicationTaskDefaultPriority 30
	#define ComunicationTaskPeriod (U16)(DEMULTIPLIER * 200)
	
	#define AperiodicServerTaskDefaultPriority 100
	#define AperiodicServerTaskPeriod (U16)(DEMULTIPLIER * 1)
	
	#define SimulatorTaskDefaultPriority 130
#endif
