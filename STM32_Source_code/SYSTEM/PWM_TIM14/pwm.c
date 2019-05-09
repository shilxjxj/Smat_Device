#include "pwm.h"

// 初始化PF9为复用 TIM14的通道1
void PWM_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStruct;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef TIM_OCInitStructure;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); // 打开GPIOF的时钟
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE); // 打开TIM14的时钟
	
		GPIO_InitStruct.GPIO_Pin 			= GPIO_Pin_9; // 初始化的第九个引脚
		GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AF; // 初始化为输出模式
		GPIO_InitStruct.GPIO_Speed 	= GPIO_Fast_Speed; // 设置GPIO的输出速度
	  GPIO_InitStruct.GPIO_PuPd 		= GPIO_PuPd_NOPULL; // 设置不要接上/下拉电阻
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; // 设置为推挽输出

		// 1.初始化IO口 PF9
		GPIO_Init(GPIOF, &GPIO_InitStruct);
	
		GPIO_PinAFConfig(GPIOF, GPIO_PinSource9, GPIO_AF_TIM14);

			 /*3.初始化定时器，配置ARR,PSC。 */
		TIM_TimeBaseStructure.TIM_Period = 100; // arr 自动重装载值
		TIM_TimeBaseStructure.TIM_Prescaler = 840; // psc 预分频值
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; // 不再进行分频
		TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure); // 选择向上计数
		
		 /* PWM1 Mode configuration: Channel1 */
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  // 选择PWM模式1
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 使能PWM输出
		TIM_OCInitStructure.TIM_Pulse = 0; // 设置比较值
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; // 选择高电平有效
		
		TIM_OC1Init(TIM14, &TIM_OCInitStructure);
		
		// 使能通道1
		TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);
		
		TIM_ARRPreloadConfig(TIM14, ENABLE);
		
		/* TIM3 enable counter */
		TIM_Cmd(TIM14, ENABLE);
}

void PWM_TIM9_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStruct;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef TIM_OCInitStructure;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); // 打开GPIOF的时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE); // 打开TIM14的时钟
	
		GPIO_InitStruct.GPIO_Pin 			= GPIO_Pin_5; // 初始化的第九个引脚
		GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AF; // 初始化为输出模式
		GPIO_InitStruct.GPIO_Speed 	= GPIO_Fast_Speed; // 设置GPIO的输出速度
	  GPIO_InitStruct.GPIO_PuPd 		= GPIO_PuPd_NOPULL; // 设置不要接上/下拉电阻
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; // 设置为推挽输出

		// 1.初始化IO口 PF9
		GPIO_Init(GPIOE, &GPIO_InitStruct);
	
		GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_TIM9);

			 /*3.初始化定时器，配置ARR,PSC。 */
		TIM_TimeBaseStructure.TIM_Period = 100; // arr 自动重装载值
		TIM_TimeBaseStructure.TIM_Prescaler = 1680; // psc 预分频值
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; // 不再进行分频
		TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure); // 选择向上计数
		
		 /* PWM1 Mode configuration: Channel1 */
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  // 选择PWM模式1
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 使能PWM输出
		TIM_OCInitStructure.TIM_Pulse = 50; // 设置比较值
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; // 选择高电平有效
		
		TIM_OC1Init(TIM9, &TIM_OCInitStructure);
		
		// 使能通道1
		TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable);
		
		TIM_ARRPreloadConfig(TIM9, ENABLE);
		
		/* TIM3 enable counter */
		TIM_Cmd(TIM9, ENABLE);
}
