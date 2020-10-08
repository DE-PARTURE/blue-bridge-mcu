#include "Sys.h"

u16 count = 0;					//200ms辅助计数
bit flag200ms = 0;			//200ms标志位
bit SysBusy = 0;				//系统忙标志位
/*********************************Setup*************************************/

/**************************************************************************
函数功能：任务状态标志位初始化函数
入口参数：无
返回值  ：无
**************************************************************************/
void TaskStruInit(){
	_18B20.StartFlag = 0;
	_18B20.ExcuteFlag = 0;
	_18B20.EndFlag = 0;
	
	_Dis.StartFlag = 0;
	_Dis.ExcuteFlag = 0;
	_Dis.EndFlag = 0;
	
	_AD.StartFlag = 0;
	_AD.ExcuteFlag = 0;
	_AD.EndFlag = 0;
	
	_Ir.StartFlag = 0;
	_Ir.ExcuteFlag = 0;
	_Ir.EndFlag = 0;
	
	_Clock.StartFlag = 0;
	_Clock.ExcuteFlag = 0;
	_Clock.EndFlag = 0;
}
/**************************************************************************
函数功能：本地时间结构体初始化函数
入口参数：无
返回值  ：无
**************************************************************************/
void TimeStruInit(){
	LocalTime.Year  = 19;
	LocalTime.Month = 12;
	LocalTime.Day   = 12;
	LocalTime.Week  = 4 ;
	LocalTime.Hour  = 10;
	LocalTime.Minu  = 00;
	LocalTime.Sec   = 00;
}
/**************************************************************************
函数功能：关闭继电器和蜂鸣器无关外设
入口参数：无
返回值  ：无
**************************************************************************/
void InitSystem()
{
	P2 = (P2 & 0x1F) | 0x80;
	P0 = 0xFF;
	P2 &= 0x1F;
	P2 = (P2 & 0x1F) | 0xA0;
	P0 = 0x00;
	P2 &= 0x1F;
}
/**************************************************************************
函数功能：初始化定时器0（5ms）
入口参数：无
返回值  ：无
**************************************************************************/
void InitTimer0()
{
	AUXR |= 0x80;		
	TMOD= (TMOD & 0xF0) | 0x01;
	TL0 = (65535 - 5000) % 256;		
	TH0 = (65535 - 5000) / 256;			
	TF0 = 0;		
	TR0 = 1;
	EA = 1;
	ET0 = 1;
}
/**************************************************************************
函数功能：定时器0中断服务函数
入口参数：无
返回值  ：无
**************************************************************************/
void ServiceTimer0() interrupt 1
{
	TL0 = (65535 - 5000) % 256;		
	TH0 = (65535 - 5000) / 256;
	
	count ++;
	SMG_Display();
	
	if(count == 40)
	{
		count = 0;
		flag200ms = 1;
	}
}
/*********************************Loop*************************************/

/**************************************************************************
函数功能：任务开始时要进行的初始化
入口参数：无
返回值  ：无
**************************************************************************/
void StartFlagScan(){
	if(!SysBusy){
		//当前无任务在执行
		if(_18B20.StartFlag){
			_18B20.StartFlag = 0;
			_18B20.ExcuteFlag = 1;
			LEDSingleRun(1);
			SysBusy = 1;
		}else if(_Dis.StartFlag){
			_Dis.StartFlag = 0;
			_Dis.ExcuteFlag = 1;
			LEDSingleRun(2);
			SysBusy = 1;
		}else if(_AD.StartFlag){
			_AD.StartFlag = 0;
			_AD.ExcuteFlag = 1;
			LEDSingleRun(3);
			SysBusy = 1;
		}else if(_Ir.StartFlag){
			_Ir.StartFlag = 0;
			_Ir.ExcuteFlag = 1;
			LEDSingleRun(4);
			EX1 = 1;							//使能外部中断
			SysBusy = 1;
		}else if(_Clock.StartFlag){
			_Clock.StartFlag = 0;
			_Clock.ExcuteFlag = 1;
			LEDSingleRun(5);
			SysBusy = 1;
		}
	}
}
/**************************************************************************
函数功能：任务执行
入口参数：无
返回值  ：无
**************************************************************************/
void ExcuteFlagScan(){
	static u8 count_Dis   = 0;
	static u8 count_AD    = 0;
	static u8 count_Clock = 0;
	
	if(_18B20.ExcuteFlag){
		Temp_Get();
	}else if(_Dis.ExcuteFlag){
		if(flag200ms)
		{
			count_Dis ++;
			flag200ms = 0;
			if(count_Dis == 4)		//计数4次刷新超声波数据
			{
				Dis_Get();
				KeyDrive();					//超声波占用时间过长，防止按键不灵敏
				KeyScan();
				flag200ms = 0;
				count_Dis = 0;
			}
		}
	}else if(_AD.ExcuteFlag){
		if(flag200ms)
		{
			count_AD ++;
			flag200ms = 0;
			if(count_AD == 10)//计数10次刷新AD数据
			{
				AD_Get();
				count_AD = 0;
				flag200ms = 0;
			}								
		}
	}else if(_Ir.ExcuteFlag){
		IrInfoDisplay();
	}else if(_Clock.ExcuteFlag){
		if(flag200ms)
		{
			count_Clock ++;
			flag200ms = 0;
			if(count_Clock == 5)//计数5次刷新Clock数据
			{
				TimeDisplay();
				count_Clock = 0;
				flag200ms = 0;
			}								
		}
	}
}
/**************************************************************************
函数功能：任务结束时要进行的设置
入口参数：无
返回值  ：无
**************************************************************************/
void EndFlagScan(){
	
	if(_18B20.EndFlag){
		_18B20.EndFlag = 0;
		_18B20.ExcuteFlag = 0;
		Refresh();
		LEDSingleRun(0);
		SysBusy = 0;
	}else if(_Dis.EndFlag){
		_Dis.EndFlag = 0;
		_Dis.ExcuteFlag = 0;
		Refresh();
		LEDSingleRun(0);
		TR1 = 0;
		SysBusy = 0;
	}else if(_AD.EndFlag){
		_AD.EndFlag = 0;
		_AD.ExcuteFlag = 0;
		Refresh();
		LEDSingleRun(0);
		SysBusy = 0;
	}else if(_Ir.EndFlag){
		_Ir.EndFlag = 0;
		_Ir.ExcuteFlag = 0;
		Refresh();
		LEDSingleRun(0);
		EX1 = 0;						//失能外部中断
		SysBusy = 0;
	}else if(_Clock.EndFlag){
		_Clock.EndFlag = 0;
		_Clock.ExcuteFlag = 0;
		Refresh();
		LEDSingleRun(0);
		SysBusy = 0;
	}
}

/*
	interrupt 0		INT0
	interrupt 1		Timer0
	interrupt 2		INT1
	interrupt 3		Timer1
	interrupt 4		UART
	interrupt 12	Timer2	
*/