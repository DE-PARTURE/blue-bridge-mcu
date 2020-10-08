#include "Sys.h"

#define DELAY_TIME 11
#define SlaveAddrW 0xA0//24C02写地址
#define SlaveAddrR 0xA1//24C02读地址
#define somenop {_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();}

//总线引脚定义
sbit SDA = P2^1;  /* 数据线 */
sbit SCL = P2^0;  /* 时钟线 */

//void IIC_Delay(unsigned char i)
//{
//    do{_nop_();}
//    while(i--);        
//}
//总线启动条件
void IIC_Start(void)
{
    SDA = 1;
    SCL = 1;
    somenop
    SDA = 0;
    somenop
    SCL = 0;	
}

//总线停止条件
void IIC_Stop(void)
{
    SDA = 0;
    SCL = 1;
    somenop
    SDA = 1;
    somenop
}

//发送应答
void IIC_SendAck(bit ackbit)
{
    SCL = 0;
    SDA = ackbit;  					// 0：应答，1：非应答
    somenop
    SCL = 1;
    somenop
    SCL = 0; 
    SDA = 1;
    somenop
}

//等待应答
bit IIC_WaitAck(void)
{
    bit ackbit;
	
    SCL  = 1;
    somenop
    ackbit = SDA;
    SCL = 0;
    somenop
    return ~ackbit;
}

//通过I2C总线发送数据
void IIC_SendByte(unsigned char byt)
{
    unsigned char i;

    for(i=0; i<8; i++)
    {
        SCL  = 0;
        somenop
        if(byt & 0x80) SDA  = 1;
        else SDA  = 0;
        somenop
        SCL = 1;
        byt <<= 1;
        somenop
    }
    SCL  = 0;  
}

//从I2C总线上接收数据
unsigned char IIC_RecByte(void)
{
    unsigned char i, da;
    for(i=0; i<8; i++)
    {   
    SCL = 1;
		somenop
		da <<= 1;
		if(SDA) da |= 1;
		SCL = 0;
		somenop
		}
    return da;    
}

/**************************************************************************
函数功能：电压获取
入口参数：PCF8591控制器件地址
返回值  ：无
**************************************************************************/
u8 AD_read(u8 add)
{
	u8 dat;
	IIC_Start();
	IIC_SendByte(0x90);	//发送写指令
	IIC_WaitAck();		 	//等待从机应答
	IIC_SendByte(add);	//写入控制器件地址
	IIC_WaitAck();		 	//等待从机应答
	IIC_Stop();
	
	IIC_Start();
	IIC_SendByte(0x91);	//发送读指令
	IIC_WaitAck();		 	//等待从机应答
	dat=IIC_RecByte(); 	//读取数据
	IIC_SendAck(0);	   	//发送非应答信号
	IIC_Stop();
	return dat;
}
/**************************************************************************
函数功能：电压显示
入口参数：无
返回值  ：无
**************************************************************************/
void AD_Get()
{
	u8 temp = 0;
	EA = 0;									//消除闪烁
	temp = AD_read(1);			//3电位器1光敏电阻
	EA = 1;
	//temp =(temp*50) / 255;//使显示电压
	temp /= 2.55;						//使显示百分比
	SMG_Buff[5] = SMG[temp / 100];
	SMG_Buff[6] = SMG[(temp / 10) % 10];
	SMG_Buff[7] = SMG[temp % 10];
}
