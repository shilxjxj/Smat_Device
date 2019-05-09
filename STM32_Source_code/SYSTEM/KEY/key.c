#include "key.h"

void Key_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStruct;
		NVIC_InitTypeDef NVIC_InitStruct;
		EXTI_InitTypeDef EXTI_InitStruct;
	
		// 1.GPIO口要设置为输入
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE, ENABLE); // 打开GPIOA的时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
		
		GPIO_InitStruct.GPIO_Pin 			= GPIO_Pin_0; // 初始化的第九个引脚
		GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_IN; // 初始化为输出模式
	 // GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_UP; // 设置不要接上/下拉电阻	

		GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	
		GPIO_InitStruct.GPIO_Pin 			= GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4; // 初始化的第九个引脚
		GPIO_Init(GPIOE, &GPIO_InitStruct);
		
		
		 
		// 2.将外部中断线和GPIO连接起来。
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);
	
		// 3.配置NVIC 中断向量管理（优先级、向量号）
		NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;    // 指定中断向量号
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x3;
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x3;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStruct);
		
		NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;    // 指定中断向量号
		NVIC_Init(&NVIC_InitStruct);
		
		NVIC_InitStruct.NVIC_IRQChannel = EXTI3_IRQn;    // 指定中断向量号
		NVIC_Init(&NVIC_InitStruct);
		
		NVIC_InitStruct.NVIC_IRQChannel = EXTI4_IRQn;    // 指定中断向量号
		NVIC_Init(&NVIC_InitStruct);

		// 4.配置EXTI 中断线的检测方式（下降沿）
		EXTI_InitStruct.EXTI_Line = EXTI_Line0; // 选择外部中断线
		EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt; // 设置为中断
		EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling; // 下降沿触发
		EXTI_InitStruct.EXTI_LineCmd = ENABLE;

		EXTI_Init(&EXTI_InitStruct);
		
		EXTI_InitStruct.EXTI_Line = EXTI_Line2; // 选择外部中断线
		EXTI_Init(&EXTI_InitStruct);
		
		EXTI_InitStruct.EXTI_Line = EXTI_Line3; // 选择外部中断线
		EXTI_Init(&EXTI_InitStruct);
		
		EXTI_InitStruct.EXTI_Line = EXTI_Line4; // 选择外部中断线
		EXTI_Init(&EXTI_InitStruct);
}

		
// 5.自己写一个外部中断的服务函数
void EXTI0_IRQHandler(void)
{
		// 判断是否产生了我们需要的中断
		if(EXTI_GetITStatus(EXTI_Line0) != RESET)
		{
			PFout(9) = ~PFout(9);
		}
		
		// 清除中断标志位
		EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI2_IRQHandler(void)
{
		// 判断是否产生了我们需要的中断
		if(EXTI_GetITStatus(EXTI_Line2) != RESET)
		{
				// 点灯
			if(GPIO_ReadOutputDataBit(GPIOF, GPIO_Pin_10)) // 如果原本就是输出1，就是熄灭的
			{
					GPIO_ResetBits(GPIOF, GPIO_Pin_10); // GPIOF的第9个引脚输出0
			}
			else
			{
					GPIO_SetBits(GPIOF, GPIO_Pin_10); // GPIOF的第9个引脚输出1
			}

		}
		
		// 清除中断标志位
		EXTI_ClearITPendingBit(EXTI_Line2);
}

void EXTI3_IRQHandler(void)
{
		// 判断是否产生了我们需要的中断
		if(EXTI_GetITStatus(EXTI_Line3) != RESET)
		{
				// 点灯
			if(GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_13)) // 如果原本就是输出1，就是熄灭的
			{
					GPIO_ResetBits(GPIOE, GPIO_Pin_13); // GPIOF的第9个引脚输出0
			}
			else
			{
					GPIO_SetBits(GPIOE, GPIO_Pin_13); // GPIOF的第9个引脚输出1
			}

		}
		
		// 清除中断标志位
		EXTI_ClearITPendingBit(EXTI_Line3);
}

void EXTI4_IRQHandler(void)
{
		// 判断是否产生了我们需要的中断
		if(EXTI_GetITStatus(EXTI_Line4) != RESET)
		{
				// 点灯
			if(GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_14)) // 如果原本就是输出1，就是熄灭的
			{
					GPIO_ResetBits(GPIOE, GPIO_Pin_14); // GPIOF的第9个引脚输出0
			}
			else
			{
					GPIO_SetBits(GPIOE, GPIO_Pin_14); // GPIOF的第9个引脚输出1
			}

		}
		
		// 清除中断标志位
		EXTI_ClearITPendingBit(EXTI_Line4);
}


