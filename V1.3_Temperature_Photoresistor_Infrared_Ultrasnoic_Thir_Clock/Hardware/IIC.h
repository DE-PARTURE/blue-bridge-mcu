#ifndef _IIC_H
#define _IIC_H

#include "Sys.h"

void IIC_Start(void); 
void IIC_Stop(void);  
bit IIC_WaitAck(void);  
void IIC_SendAck(bit ackbit); 
void IIC_SendByte(unsigned char byt); 
unsigned char IIC_RecByte(void); 

//unsigned char IIC_readbyte(unsigned char addr,u8 len);
//bit IIC_writebyte(unsigned char addr,unsigned char dat);
//void EE_Write(u8 *buf, u8 addr, u8 len);
//void EE_Read(u8 *buf, u8 addr, u8 len);
u8 AD_read(u8 add);
void AD_Get();

#endif
