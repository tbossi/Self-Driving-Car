#ifndef TASK_PRIORITIES_H
	#define TASK_PRIORITIES_H
	
	#ifdef DEBUG
		#define DEMULTIPLIER 0.2
	#else
		#define DEMULTIPLIER 1
	#endif

	#define AperiodicServerTaskDefaultPriority 100
	#define AperiodicServerTaskPeriod (U16)(DEMULTIPLIER * 10)

	#define DriverTaskDefaultPriority 80
	#define DriverTaskPeriod (U16)(DEMULTIPLIER * 100)
	
	#define PositionTaskDefaultPriority 40
	#define PositionTaskPeriod (U16)(DEMULTIPLIER * 500)
	
	#define ComunicationTaskDefaultPriority 20
	#define ComunicationTaskPeriod (U16)(DEMULTIPLIER * 2000)
	
	#define SimulatorTaskDefaultPriority 130
#endif
