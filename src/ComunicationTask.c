#include <RTL.h>
#include "ComunicationTask.h"
#include "TaskPriorities.h"
#include "Tasks.h"
#include "CarInfo.h"
#include "HardwareController.h"

static void BroadcastUsefullInformation(CarData* carData)
{
	NearCarInfo infoToSend;
	infoToSend.CurrentSpeed = (*carData).CurrentCarInfo.Speed;
	infoToSend.CurrentLocation = (*carData).NavigationInfo.CurrentPoint;
	
	Broadcast_CarInfo(infoToSend);
}

static void comunicate(CarData* carData)
{
	U32 startingTime;
	U16 ret_flags;
	void* eventResult;
	startingTime = os_time_get();
	
  ret_flags = Wait_ExternalEvent(E_Ext_StopRequest | E_Ext_RoadSign | E_Ext_NearCarInfo, 0);
	
	if ((eventResult = Get_ExternalEvent(E_Ext_StopRequest, ret_flags)) != NULL)
	{
		(*carData).NavigationInfo.StopRequest = * (int*)eventResult;
	}
	if ((eventResult = Get_ExternalEvent(E_Ext_RoadSign, ret_flags)) != NULL)
	{
		(*carData).NavigationInfo.RoadSign = * (RoadSign*)eventResult;
	}
	if ((eventResult = Get_ExternalEvent(E_Ext_NearCarInfo, ret_flags)) != NULL)
	{
		NearCarInfo receivedInfo = * (NearCarInfo*)eventResult;
		//extract data and store it properly 
	}
	
	BroadcastUsefullInformation(carData);
	
	while (startingTime + ComunicationTaskCost > os_time_get()) {;} //lose time in other comunication operations
}

__task void ComunicationTask(void *argv)
{
	CarData* carData = (CarData*)argv;
	
	os_itv_set(ComunicationTaskPeriod);
	while (1)
	{
		Log_Comunication_Start();
		comunicate(carData);
		Log_Comunication_End();
		os_itv_wait();
	}
}
