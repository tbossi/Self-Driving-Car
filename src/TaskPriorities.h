#ifndef TASK_PRIORITIES
	#define TASK_PRIORITIES
	
	#ifdef DEBUG
		#define DEMULTIPLIER 0.2
	#else
		#define DEMULTIPLIER 1
	#endif

	#define DriverTaskDefaultPriority 50
	#define DriverTaskPeriod (U16)(10 * DEMULTIPLIER)
	
	#define PositionTaskDefaultPriority 40
	#define PositionTaskPeriod (U16)(50 * DEMULTIPLIER)
	
	#define ComunicationTaskDefaultPriority 30
	#define ComunicationTaskPeriod (U16)(200 * DEMULTIPLIER)
	
	#define AperiodicServerTaskDefaultPriority 10
	#define AperiodicServerTaskPeriod (U16)(1 * DEMULTIPLIER)
	
	#define SimulatorTaskDefaultPriority 130
#endif
