#ifndef SNOIC_H_
#define SNOIC_H_

#include "Sys.h"

sbit Snoic_Txd = P1^0;
sbit Snoic_Rxd = P1^1;

void Delay13us();	
void InitSonic();
void SendWave();
void Dis_Get();

#endif