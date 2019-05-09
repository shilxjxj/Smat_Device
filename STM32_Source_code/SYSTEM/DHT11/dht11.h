#ifndef  __DHT11_H
#define  __DHT11_H
/*
//IO方向设置
#define DHT11_IO_IN()  {GPIOG->MODER&=~(3<<(9*2));GPIOG->MODER|=0<<9*2;}	//PG9输入模式
#define DHT11_IO_OUT() {GPIOG->MODER&=~(3<<(9*2));GPIOG->MODER|=1<<9*2;} 	//PG9输出模式 
*/

#include "stm32f4xx.h"
#include "sys.h"
#include "delay.h"

#define DHT11_IN  GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_9)

void GPIOG_Out_Init(void);
void GPIOG_In_Init(void);
void DHT11_Rst(void);
u8 DHT11_Read_Bit(void);
u8 DHT11_Read_Byte(void);
u8 DHT11_Read_Data(u8 buffer[5]);


#endif
