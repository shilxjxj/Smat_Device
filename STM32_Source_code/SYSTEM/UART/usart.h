#ifndef __USART_H_
#define __USART_H_
#include "stm32f4xx.h"
#include "stdio.h"
#include "sys.h"


void Send_Str(u8 *str);
void Uart1_Init(void);

void ESP_CMD_Send(u8 *str);
void Uart3_Init(void);


#endif
