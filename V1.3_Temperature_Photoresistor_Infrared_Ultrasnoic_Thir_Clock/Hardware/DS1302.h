#ifndef __DS1302_H
#define __DS1302_H

sbit SCK = P1^7;		
sbit SDA_D = P2^3;		
sbit RST = P1^3;   // DS1302¸´Î»	

void Write_Ds1302(unsigned char temp);
u8 Read_Ds1302();
void Write_Ds1302_Byte( unsigned char address,unsigned char dat );
unsigned char Read_Ds1302_Byte( unsigned char address );
void DS1302BurstWrite(u8 *Dat);
void DS1302BurstRead(u8 *Dat);
void DS1302Init();
void TimeTranslate();
void TimeDisplay();
u8 HexToBCD(u8 Hex);
u8 BCDToHex(u8 BCD);

#endif
