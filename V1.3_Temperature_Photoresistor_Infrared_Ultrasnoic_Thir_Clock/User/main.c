/*******************************************************************************
* 文件名：example
* 描  述：实时时钟、温度显示、超声波测距、光敏D/A显示、红外接收数据显示
* 作  者：JosephCooper
* 日  期: 2019年4月19日
* 备  注：CT107单片机综合实训平台 IAP15F2K61S2单片机@11.0592MHZ
*******************************************************************************
*/
#include "Sys.h"

//定义任务状态位结构体
Task _18B20;								
Task _Dis;									
Task _AD;
Task _Ir;
Task _Clock;
Time LocalTime;

void main()
{
	u8 count_AD  = 0;
	u8 count_Dis = 0;
	
	TaskStruInit();							//任务状态位结构体初始化
	TimeStruInit();							//本地时间结构体初始化
	InitSystem();								//外设初始化
	InitTimer0();								//定时器0初始化
	InitSonic();								//超声波初始化
	PT0 = 1;										//定时器0中断优先
	IR_INPUT = 1;						
	InitInfrared();							//红外初始化
	//Config_DS18B20();
	DS1302Init();								//DS1302初始化
	while(1)										//任务主循环
	{
		KeyDrive();
		KeyScan();
		
		StartFlagScan();					//任务开始，可包含任务所需初始化内容
		ExcuteFlagScan();					//任务执行，循环部分
		EndFlagScan();						//任务结束，可关闭任务开始时初始化内容
		
	}
}

/*
原中断顺序：
外部中断0；
定时中断0
外部中断1
定时中断1
串口中断*/
