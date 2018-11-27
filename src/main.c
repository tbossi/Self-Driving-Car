#include <RTL.h>             // RTX kernel functions & defines

#include <stm32f10x.h>       // STM32F103 definitions
#include "stm32f10x_it.h"    // interrupt

extern volatile int T1=0;
extern volatile int IDLE=0;

volatile int Eid = 0x01; 
OS_TID Tid;         // Task1 (phase manager) id

int main(void)
{
	T1 = 1;
	IDLE = 0;
}
