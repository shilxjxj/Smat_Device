#ifndef __TIM_H__
#define __TIM_H__

#include "stm32f4xx.h"
#include "sys.h"

void TIM_Init(TIM_TypeDef *TIMx, uint32_t arr, uint16_t psc);
	
#endif
