#include "Sys.h"

u8 Key_Sta[4][4] = {
{1 , 1 , 1 , 1},{1 , 1 , 1 , 1},
{1 , 1 , 1 , 1},{1 , 1 , 1 , 1}
};//按键当前状态

u8 Key_CodeMap[4][4] = {
	{'A', 'B', 'C', 'D'},
	{'E', 'F', 'G', 'H'},
	{'I', 'J', 'K', 'L'},
	{'M', 'N', 'O', 'P'}

};//键码表
/**************************************************************************
函数功能：键盘功能函数
入口参数：键码
返回值  ：无
**************************************************************************/
void KeyAction(char cmd)			//按键功能函数
{
	if(cmd == 'A')
	{
		if(!_18B20.ExcuteFlag & !SysBusy){
			_18B20.StartFlag = 1;
		}
		else if(_18B20.ExcuteFlag){
			_18B20.EndFlag = 1;
		}
	}
	else if(cmd == 'B')
	{
		if(!_Dis.ExcuteFlag & !SysBusy){
			_Dis.StartFlag = 1;
		}
		else if(_Dis.ExcuteFlag){
			_Dis.EndFlag = 1;
		}
	}
	else if(cmd == 'C')
	{
		if(!_AD.ExcuteFlag & !SysBusy){
			_AD.StartFlag = 1;
		}
		else if(_AD.ExcuteFlag){
			_AD.EndFlag = 1;
		}
	}
	else if(cmd == 'D')
	{
		if(!_Ir.ExcuteFlag & !SysBusy){
			_Ir.StartFlag = 1;
		}
		else if(_Ir.ExcuteFlag){
			_Ir.EndFlag = 1;
		}
	}
	else if(cmd == 'E')
	{
		if(!_Clock.ExcuteFlag & !SysBusy){
			_Clock.StartFlag = 1;
		}
		else if(_Clock.ExcuteFlag){
			_Clock.EndFlag = 1;
		}
	}else{
		_nop_();
	}
}
/**************************************************************************
函数功能：键盘功能函数执行函数
入口参数：无
返回值  ：无
**************************************************************************/
void KeyDrive()
{
	u8 i, j;
	static u8 backup[4][4] = {
	{1 , 1 , 1 , 1},{1 , 1 , 1 , 1},
	{1 , 1 , 1 , 1},{1 , 1 , 1 , 1}
	};//按键状态对照码
	
	for(i = 0; i < 4; i ++)
	{
		for(j = 0; j < 4; j ++)
		{
			if(Key_Sta[i][j] != backup[i][j])
			{
				if(backup[i][j] != 0)	//检测是否已经缓存按下指令
				{
					KeyAction(Key_CodeMap[i][j]);
				}
				backup[i][j] = Key_Sta[i][j];
			}
		}
	}
}
/**************************************************************************
函数功能：键盘扫描函数
入口参数：无
返回值  ：无
**************************************************************************/
void KeyScan()
{
	u8 i;
	static u8 Key_OUT = 2;
	static u8 Key_Buff[4][4] = {
    {0xFF, 0xFF, 0xFF, 0xFF},  {0xFF, 0xFF, 0xFF, 0xFF},
    {0xFF, 0xFF, 0xFF, 0xFF},  {0xFF, 0xFF, 0xFF, 0xFF}
	};//缓冲区

	Key_Buff[Key_OUT][0] = (Key_Buff[Key_OUT][0] << 1) | Key_IN1;	//一则变零则不变
	Key_Buff[Key_OUT][1] = (Key_Buff[Key_OUT][1] << 1) | Key_IN2;
	Key_Buff[Key_OUT][2] = (Key_Buff[Key_OUT][2] << 1) | Key_IN3;
	Key_Buff[Key_OUT][3] = (Key_Buff[Key_OUT][3] << 1) | Key_IN4;	
		
	for(i = 0; i < 4; i ++)
	{
		if((Key_Buff[Key_OUT][i] & 0x0F) == 0x0F)
		{
			Key_Sta[Key_OUT][i] = 1;
		}
		else if((Key_Buff[Key_OUT][i] & 0x0F) == 0x00)
		{
			Key_Sta[Key_OUT][i] = 0;
		}
	}
	
	Key_OUT ++;
	Key_OUT &= 0x03;
	
	switch(Key_OUT)//逐行扫描
	{
	 	case 0: Key_OUT1 = 0; Key_OUT4 = 1;Key_OUT3 = 1; Key_OUT2 = 1; break;
		case 1: Key_OUT2 = 0; Key_OUT4 = 1;Key_OUT3 = 1; Key_OUT1 = 1; break;
		case 2: Key_OUT3 = 0; Key_OUT4 = 1;Key_OUT2 = 1; Key_OUT1 = 1; break;
		case 3: Key_OUT4 = 0; Key_OUT3 = 1;Key_OUT2 = 1; Key_OUT1 = 1; break;
		default: break;
	}

}
