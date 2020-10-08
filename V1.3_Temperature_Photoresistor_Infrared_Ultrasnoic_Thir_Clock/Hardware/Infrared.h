#ifndef _INFRARED_H
#define _INFRARED_H

#include "Sys.h"

sbit IR_INPUT = P1^1;

void InitInfrared();
u16 GetHighTime();
u16 GetLowRime();
void IrInfoDisplay();

#endif