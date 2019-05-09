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
	

	printf("ϵͳ��ʼ��\r\n");
		
	while(1);
}
	
	
//���ڽ��պ���
void USART1_IRQHandler(void)
{

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);

		buffer[rx_count++] = USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������

		//�����Ƿ���ս���
		if(buffer[rx_count-2] == 0x0D && buffer[rx_count-1] == 0x0A)
		{
			
				for(rx_i=0; rx_i<rx_count; rx_i++)
				{
					//��buffer���ݸ�ֵ��rx_buffer
					rx_buffer[rx_i] = buffer[rx_i];
					//���buffer
					buffer[rx_i] = 0;
				}
				//printf(rx_buffer);
				//�Ѿ����굽��������
				rx_flag  = 1;
				rx_count = 0;
			
		}
	
  } 

}

