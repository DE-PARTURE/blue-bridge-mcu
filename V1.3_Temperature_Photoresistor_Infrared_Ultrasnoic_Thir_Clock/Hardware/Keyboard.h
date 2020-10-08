#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "Sys.h"


sbit Key_IN1 = P4^4;
sbit Key_IN2 = P4^2;
sbit Key_IN3 = P3^5;
sbit Key_IN4 = P3^4;

sbit Key_OUT1 = P3^0;
sbit Key_OUT2 = P3^1;
sbit Key_OUT3 = P3^2;
sbit Key_OUT4 = P3^3;

void KeyDrive();
void KeyScan();
void KeyAction(u8 cmd);

extern u8 Key_Sta[4][4];
extern u8 Key_CodeMap[4][4];

#endif