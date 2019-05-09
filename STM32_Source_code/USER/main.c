#include "stm32f4xx.h"
#include <stdio.h>
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "led.h"

char buffer[20] 	= {0};
char rx_buffer[20] 	= {0};
char rx_count = 0;
u8   rx_i;
u8   rx_flag = 0;

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	Led_Init();
	Key_Init();
	Delay_Init();
	Uart1_Init();
	

	printf("系统初始化\r\n");
		
	while(1);
}
	
	
//串口接收函数
void USART1_IRQHandler(void)
{

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);

		buffer[rx_count++] = USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据

		//数据是否接收结束
		if(buffer[rx_count-2] == 0x0D && buffer[rx_count-1] == 0x0A)
		{
			
				for(rx_i=0; rx_i<rx_count; rx_i++)
				{
					//将buffer数据赋值给rx_buffer
					rx_buffer[rx_i] = buffer[rx_i];
					//清空buffer
					buffer[rx_i] = 0;
				}
				//printf(rx_buffer);
				//已经接完到完整数据
				rx_flag  = 1;
				rx_count = 0;
			
		}
	
  } 

}

