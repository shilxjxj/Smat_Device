#ifndef __DELAY_H__
#define __DELAY_H__

#include "stm32f4xx.h"
#include "sys.h"

void Delay_Init(void);
int Delay_ms(int nms);
int Delay_us(int nus);
int Delay_s(int ns);

#endif
