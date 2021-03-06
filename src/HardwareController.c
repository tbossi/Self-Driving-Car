#include <RTL.h>
#include <stm32f10x.h>
#include "CarInfo.h"
#include "HardwareController.h"

// values are set by simulator task!
extern volatile double SIM_SpaceLeft;
extern volatile double SIM_SpaceRight;
extern volatile double SIM_SpaceFront;
extern volatile double SIM_SpaceRear;
extern volatile int SIM_Lane;
extern volatile double SIM_Speed;
extern volatile double SIM_SteeringAngle;
extern volatile double SIM_Oil;

extern volatile int SIM_Ext_StopRequest;
extern volatile RoadSign SIM_Ext_RoadSign;
extern volatile NearCarInfo SIM_Ext_NearCarInfo;
extern volatile CarLocation SIM_Ext_CurrentLocation;
extern volatile CarLocation SIM_Ext_EndingPoint;
// !!!

static void busyloop(int time)
{
	int x;
	for (x = 0; x < time; x++)
	{
		x++;
		x--;
	}
}

void Init_GPIO(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // Enable GPIOA
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // Enable GPIOB
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // Enable GPIOC
	GPIOA->CRL = 0x33333333; // PA 0..7 defined as Outputs
	GPIOB->CRL = 0x33333333; // PB 0..7 defined as Outputs
	GPIOC->CRL = 0x33333333; // PC 0..7 defined as Outputs
}

void Car_SpeedUp(int amount)
{
	if (amount > 0)
	{
		SIM_Speed += 1.33 * amount;
	}
	
	if (amount > 10) { amount = 10; }
	GPIOA->BSRR = amount;
	busyloop(250 + 10 * amount);
	GPIOA->BRR = amount;
}

void Car_Break(int amount)
{
	if (amount > 0)
	{
		SIM_Speed -= 0.88 * amount;
	}
	
	if (amount > 10) { amount = 10; }
	GPIOB->BSRR = amount;
	busyloop(150 + 10 * amount);
	GPIOB->BRR = amount;
}

void Car_Steer(int angle)
{
	SIM_SteeringAngle = 3.14 * angle / 180.0;
	
	GPIOC->BSRR = angle;
	busyloop(80 + (3 * angle * angle) / 100);
	GPIOC->BRR = angle;
}

void Broadcast_CarInfo(NearCarInfo info)
{
	busyloop(1200 * ((os_time_get() % 4) + 1));
}

int SpaceAvailable(double space, double speed_cm_ms, int millis)
{
	return space / (double)millis < speed_cm_ms;
}

int IsEmergency(CarData* carData)
{
	double speed_cm_ms = (*carData).CurrentCarInfo.Speed / 36.0;
	
	int emergency = SpaceAvailable((*carData).CurrentCarInfo.Position.SpaceFront, speed_cm_ms, 80);
	emergency = emergency || SpaceAvailable((*carData).CurrentCarInfo.Position.SpaceRear, speed_cm_ms, 80);
	emergency = emergency || ((*carData).CurrentCarInfo.Speed > 15 && (*carData).CurrentCarInfo.Position.SpaceLeft < 20 );
	emergency = emergency || ((*carData).CurrentCarInfo.Speed > 15 && (*carData).CurrentCarInfo.Position.SpaceRight < 20 );

	return emergency;
}

U16 Wait_CarEvent(U16 flags, U16 timeout)
{	
  if (os_evt_wait_or(flags, timeout) == OS_R_EVT)
	{
    return os_evt_get();
  }
	
	return 0;
}

void* Get_CarEvent(U16 event, U16 raisedFlags)
{
	U16 available = event & raisedFlags;
	if (!available) return NULL;
	
	os_evt_clr(event, os_tsk_self());
	switch(event)
	{
		case E_SpaceLeft: return (void*) &SIM_SpaceLeft;
		case E_SpaceRight: return (void*) &SIM_SpaceRight;
		case E_SpaceFront: return (void*) &SIM_SpaceFront;
		case E_SpaceRear: return (void*) &SIM_SpaceRear;
		case E_Lane: return (void*) &SIM_Lane;
		case E_Speed: return (void*) &SIM_Speed;
		case E_SteeringAngle: return (void*) &SIM_SteeringAngle;
		case E_Oil: return (void*) &SIM_Oil;
		default: return NULL;
	}
}

U16 Wait_ExternalEvent(U16 flags, U16 timeout)
{	
  if (os_evt_wait_or(flags, timeout) == OS_R_EVT)
	{
    return os_evt_get();
  }
	
	return 0;
}

void* Get_ExternalEvent(U16 event, U16 raisedFlags)
{
	U16 available = event & raisedFlags;
	if (!available) return NULL;
	
	os_evt_clr(event, os_tsk_self());
	switch(event)
	{
		case E_Ext_StopRequest: return (void*) &SIM_Ext_StopRequest;
		case E_Ext_RoadSign: return (void*) &SIM_Ext_RoadSign;
		case E_Ext_NearCarInfo: return (void*) &SIM_Ext_NearCarInfo;
		case E_Ext_GPS: return (void*) &SIM_Ext_CurrentLocation;
		case E_Ext_EndingPoint: return (void*) &SIM_Ext_EndingPoint;
		default: return NULL;
	}
}
