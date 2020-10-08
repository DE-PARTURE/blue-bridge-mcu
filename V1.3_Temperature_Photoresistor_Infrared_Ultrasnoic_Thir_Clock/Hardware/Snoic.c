#include "Sys.h"


void Delay13us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 33;
	while (--i);
}

void InitSonic()//初始化定时器1，暂时不启动
{
	TMOD = (TMOD & 0x0F) | 0x10;
	
	TF1 = 0;
	TR1 = 0;
}

void SendWave()//发送八段脉冲波(40Khz)
{
	u8 i = 8;
	
	while(i --)
	{
		Snoic_Txd = 1;
		Delay13us();
		Snoic_Txd = 0;
		Delay13us();
	}
}

void Dis_Get()
{
	u16 time, distance;
	
	EA = 0;
	SendWave();
	EA = 1;
	TH1 = 0;
	TL1 = 0;
	TR1 = 1;
	while((Snoic_Rxd) && (TF1 == 0));
	TR1 = 0;
	
	if(TF1 == 1)
	{
		TF1 = 0;
		SMG_Buff[4] = 0xBF;
		SMG_Buff[5] = 0xBF;
		SMG_Buff[6] = 0xBF;
		SMG_Buff[7] = 0xBF;
	}	
	else
	{
		time = (TH1 * 256) + TL1;
		distance = (u16)((time * 0.17 * 12) / 11.0592);//本身数值乘以0.17公式是官方给的对于12MHZ的晶振的由于实际使用的是11.05926MHZ所以这么算
		SMG_Buff[4] = SMG[(distance / 1000) % 10];
		SMG_Buff[5] = SMG[(distance / 100) % 10];
		SMG_Buff[6] = (SMG[(distance / 10) % 10]) & 0x7F;
		SMG_Buff[7] = SMG[(distance % 10)];
	}
}

