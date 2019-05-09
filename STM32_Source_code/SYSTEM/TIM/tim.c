#include "tim.h"

void TIM_Init(TIM_TypeDef *TIMx, uint32_t arr, uint16_t psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* 1、能定时器时钟。 */
	if(TIMx == TIM3)
	{
			RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE);
			NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	}
	else if(TIMx == TIM7)
	{
			RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM7, ENABLE);
			NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	}
	else if(TIMx == TIM8)
	{
			RCC_APB2PeriphClockCmd( RCC_APB2Periph_TIM8, ENABLE);
			NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_TIM13_IRQn;
	}
	else if(TIMx == TIM14)
	{
			RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM14, ENABLE);
			NVIC_InitStructure.NVIC_IRQChannel = TIM8_TRG_COM_TIM14_IRQn;
	}

  /* 2、启定时器中断，配置NVIC */
  
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	 /*3.初始化定时器，配置ARR,PSC。 */
	TIM_TimeBaseStructure.TIM_Period = arr; // arr 自动重装载值
	TIM_TimeBaseStructure.TIM_Prescaler = psc; // psc 预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; // 不再进行分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 选择向上计数
	
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);
	
	// 4、设置 TIM_IT_Update  允许更新中断
	TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);
	
	/* 5、使能定时器。 */
	TIM_Cmd(TIMx, ENABLE);

}

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		PFout(10) = ~PFout(10);
	}
	
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}

void TIM7_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
	{
		PEout(13) = ~PEout(13);
	}
	
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
}

void TIM8_TRG_COM_TIM14_IRQHandler(void)
{

	if(TIM_GetITStatus(TIM14, TIM_IT_Update) != RESET)
	{
		PEout(14) = ~PEout(14);
	}
	
	
	TIM_ClearITPendingBit(TIM14, TIM_IT_Update);
}

void TIM8_UP_TIM13_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM8, TIM_IT_Update) != RESET)
	{
		PFout(9) = ~PFout(9);
	}
	TIM_ClearITPendingBit(TIM8, TIM_IT_Update);
}
