#ifndef SYS_H_
#define SYS_H_

#include "STC15F2K60S2.h"
#include "intrins.h"
#include "Config.h"
#include "Snoic.h"
#include "IIC.h"
#include "Keyboard.h"
#include "SMG.h"
#include "OneWire.h"
#include "infrared.h"
#include "LED.h"
#include "DS1302.h"

typedef struct{
	u8 StartFlag;
	u8 ExcuteFlag;
	u8 EndFlag;
}Task;

typedef struct {
	u8 Year;
	u8 Month;
	u8 Day;
	u8 Week;
	u8 Hour;
	u8 Minu;
	u8 Sec;
}Time;

extern u16 count;
extern bit flag200ms;
extern bit SysBusy;
extern Task _18B20;
extern Task _Dis;
extern Task _AD;
extern Task _Ir;
extern Task _Clock;
extern Time LocalTime;

void TaskStruInit();
void InitSystem();
void InitTimer0();
void StartFlagScan();				//任务开始，可包含任务所需初始化内容
void ExcuteFlagScan();			//任务执行，循环部分
void EndFlagScan();					//任务结束，可关闭任务开始时初始化内容
void TimeStruInit();


#endif