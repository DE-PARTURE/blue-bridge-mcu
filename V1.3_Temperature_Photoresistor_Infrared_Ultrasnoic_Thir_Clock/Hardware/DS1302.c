#include "Sys.h"											

void Write_Ds1302(unsigned  char temp) 
{
	unsigned char i;
	for (i=0;i<8;i++)     	
	{ 
		SCK=0;
		SDA_D=temp&0x01;
		temp>>=1; 
		SCK=1;
	}
	SCK = 0;//记得加上
}   
/*******************************/
u8 Read_Ds1302(){
	u8 i = 0, temp = 0x00;
	for (i=0;i<8;i++) 											//这段来自于第47行
 	{		
		SCK=0;
		temp>>=1;	
 		if(SDA_D)
 		temp|=0x80;	
 		SCK=1;
	} 
	SCK = 0;//记得加上
	return (temp);		
}
/*******************************/
void Write_Ds1302_Byte( unsigned char address,unsigned char dat )     
{
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1; 	_nop_(); 
 	Write_Ds1302(address);	
 	Write_Ds1302(dat);		
 	RST=0; 
}

unsigned char Read_Ds1302_Byte ( unsigned char address )//未使用
{
 	unsigned char i,temp=0x00;
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1;	_nop_();
 	Write_Ds1302(address);
 	for (i=0;i<8;i++) 	
 	{		
		SCK=0;
		temp>>=1;	
 		if(SDA_D)
 		temp|=0x80;	
 		SCK=1;
	} 
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
	SCK=1;	_nop_();
	SDA_D=0;	_nop_();
	SDA_D=1;	_nop_();
	return (temp);			
}/*******************************/

/**************************************************************************
函数功能：DS1302Burst写
入口参数：待写入数组地址
返回值  ：无
**************************************************************************/
void DS1302BurstWrite(u8 *Dat){
	u8 index = 0;
	RST = 1;
	Write_Ds1302(0xBE);											//写Burst写指令
	for(index = 0 ; index < 8; index ++){
																					//读数据
		Write_Ds1302(Dat[index]);
	}
	RST = 0;
}
/**************************************************************************
函数功能：DS1302Burst读
入口参数：时间存储数组地址
返回值  ：无
**************************************************************************/
void DS1302BurstRead(u8 *Dat){
	u8 index = 0;
	RST = 1;
	Write_Ds1302(0xBF);											//写Burst读指令
	for(index = 0 ; index < 8; index ++){
																					//读数据
		Dat[index] = Read_Ds1302();
	}
	RST = 0;
}
/**************************************************************************
函数功能：DS1302时间初始化
入口参数：无
返回值  ：无
**************************************************************************/
void DS1302Init(){
	u8 InitTime[] = {  											//2019年12月12日 星期四 10:00:00
        0x00,0x00,0x10, 0x12, 0x12, 0x04, 0x19
    };//秒   分   时    日    月    周    年
	RST = 0;
	SDA_D = 0;
	Write_Ds1302_Byte(0x8E,0x00);						//撤销写保护
	DS1302BurstWrite(InitTime);
}
/**************************************************************************
函数功能：时间读取
入口参数：无
返回值  ：无
**************************************************************************/
void TimeTranslate(){
	u8 Time[7] = {
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	};
	DS1302BurstRead(Time);
	
	LocalTime.Sec   = Time[0];
	LocalTime.Minu  = Time[1];
	LocalTime.Hour  = Time[2];
	LocalTime.Day   = Time[3];
	LocalTime.Month = Time[4];
	LocalTime.Week  = Time[5];
	LocalTime.Year  = Time[6];
}
/**************************************************************************
函数功能：将实时时间加载到数码管缓冲区
入口参数：无
返回值  ：无
**************************************************************************/
void TimeDisplay(){
	
	TimeTranslate();
	
	SMG_Buff[0] = SMG[LocalTime.Hour >> 4];
	SMG_Buff[1] = SMG[LocalTime.Hour & 0x0F];
	SMG_Buff[2] = 0xBF;//-
	SMG_Buff[3] = SMG[LocalTime.Minu >> 4];
	SMG_Buff[4] = SMG[LocalTime.Minu & 0x0F];
	SMG_Buff[5] = 0xBF;
	SMG_Buff[6] = SMG[LocalTime.Sec >> 4];
	SMG_Buff[7] = SMG[LocalTime.Sec & 0x0F];
}
/**************************************************************************
函数功能：十六进制数转BCD码
入口参数：十六进制数
返回值  ：BCD码
**************************************************************************/
//u8 HexToBCD(u8 Hex){
//	u8 BCD;
//	BCD = Hex/10;
//	BCD <<= 4;
//	BCD |= Hex % 10;
//	
//	return BCD;
//}
/**************************************************************************
函数功能：BCD码转十六进制数
入口参数：BCD码
返回值  ：十六进制数
**************************************************************************/
//u8 BCDToHex(u8 BCD){
//	u8 Hex;
//	Hex = (BCD >> 4)*10 + (BCD & 0x0F);
//	
//	return Hex;
//}
/*******************************/