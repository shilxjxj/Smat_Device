#include "delay.h"

int time_num = 0;

void Delay_Init(void)
{
	 SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); //  选择外部时钟
	 // SysTick_Config(168000); // 1ms产生一次中断
	
}

/*** // 中断形式的延时函数
void Delay_ms(int nms)
{
	while(time_num != nms);
	time_num = 0;
}
****/

int Delay_us(int nus)
{
	u32 temp = 0;
	
	if( (21 * nus - 1) >  SysTick_LOAD_RELOAD_Msk)		return -1;
	
  SysTick->LOAD  = 21 * nus - 1;                                  /* set reload register */
  SysTick->VAL   = 0x00;                                          /* Load the SysTick Counter Value */
	
  SysTick->CTRL  |=  SysTick_CTRL_ENABLE_Msk;                    /* 使能嘀嗒时钟*/
	
	do
	{
		temp = SysTick->CTRL;
	}while( !( temp & (1 << 16) ) );
	
	SysTick->CTRL &=  ~SysTick_CTRL_ENABLE_Msk;                    /* 使能嘀嗒时钟*/
	SysTick->VAL   = 0x00;    
	
	return 0;
}

int Delay_ms(int nms)
{
	u32 temp = 0;
	
	if( (21000 * nms - 1) >  SysTick_LOAD_RELOAD_Msk)		return -1;
	
  SysTick->LOAD  = 21000 * nms - 1;                                  /* set reload register */
  SysTick->VAL   = 0x00;                                          /* Load the SysTick Counter Value */
	
  SysTick->CTRL  |=  SysTick_CTRL_ENABLE_Msk;                    /* 使能嘀嗒时钟*/
	
	do
	{
		temp = SysTick->CTRL;
	}while( !( temp & (1 << 16) ) );
	
	SysTick->CTRL &=  ~SysTick_CTRL_ENABLE_Msk;                    /* 使能嘀嗒时钟*/
	SysTick->VAL   = 0x00;    
	
	return 0;
}

int Delay_s(int ns)
{
		while(ns--)
		{
			Delay_ms(500);
			Delay_ms(500);
		}
			
	return 0;
}

void SysTick_Handler(void)
{
		static int count = 1;
		time_num++;
		if(count++ % 500 == 0)
		{
				PEout(14) = ~PEout(14);
				count = 1;
		}
}

