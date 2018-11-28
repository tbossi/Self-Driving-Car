#include <RTL.h>
#include "SimulatorTask.h"

extern volatile int T1;
extern volatile int IDLE;

__task void SimulatorTask(void)
{
	//TODO: simulation
	T1 = 1;
	IDLE = 1;
}
