#include <rtl.h>
#include "stm32f10x_it.h"

//extern int Eid;
//extern OS_TID Tid;

void TIM2_IRQHandler(void)
{
//	unsigned int i = 1<<8;
	
  /* Clear TIM2 update interrupt */
  //TIM_ClearFlag(TIM2, TIM_FLAG_CC2);
//
	//isr_evt_set( Eid, Tid );
}
