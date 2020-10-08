#ifndef __ONEWIRE_H
#define __ONEWIRE_H

#include "Sys.h"

extern void Delay_OneWire(unsigned int t);
extern void Write_DS18B20(unsigned char dat);
extern unsigned char Read_DS18B20(void);

extern bit Config_DS18B20();
extern bit Start_DS18B20();
extern bit InitDS18B20(void);
extern void Temp_Get();
#endif
