#include "LED.h"

// 初始化LED函数
void Led_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStruct;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOE, ENABLE); // 打开GPIOF的时钟
		
	
		GPIO_InitStruct.GPIO_Pin 			= GPIO_Pin_9|GPIO_Pin_10; // 初始化的第九个引脚
		GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_OUT; // 初始化为输出模式
		GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed; // 设置GPIO的输出速度
	  GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_NOPULL; // 设置不要接上/下拉电阻
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; // 设置为推挽输出
	
		
		// 1.初始化IO口 PF9
		GPIO_Init(GPIOF, &GPIO_InitStruct);
	
		GPIO_InitStruct.GPIO_Pin 			= GPIO_Pin_13|GPIO_Pin_14; // 初始化的第九个引脚
		GPIO_Init(GPIOE, &GPIO_InitStruct);
	
		// 先让LED灭
	GPIO_SetBits(GPIOF, GPIO_Pin_9); // GPIOF的第9个引脚输出1
	GPIO_SetBits(GPIOF, GPIO_Pin_10); // GPIOF的第10个引脚输出1
	
	GPIO_SetBits(GPIOE, GPIO_Pin_13); // GPIOF的第9个引脚输出1
	GPIO_SetBits(GPIOE, GPIO_Pin_14); // GPIOF的第10个引脚输出1
}
