#include "stm32f10x.h"

void Encoder_Init(){
	 TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	 TIM_ICInitTypeDef TIM_ICInitStructure;
	 
		 
	 GPIO_InitTypeDef GPIO_InitStructure;
	 NVIC_InitTypeDef NVIC_InitStructure;
	 
	 
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	 
	 GPIO_StructInit(&GPIO_InitStructure);
	 
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1;
	 GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IN_FLOATING;
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
	 
	 
	 NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =TIMx_PRE_EMPTION_PRIORITY;
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority =TIMx_SUB_PRIORITY;
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	 NVIC_Init(&NVIC_InitStructure);

	 
	 TIM_DeInit(TIME5);
	 TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	 
	 TIM_TimeBaseStructure.TIM_Prescaler = 0x0;  // Noprescaling
	 TIM_TimeBaseStructure.TIM_Period =49999; 
	 TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1;  //不分频 
	 TIM_TimeBaseStructure.TIM_CounterMode =TIM_CounterMode_Up;   //上数
	 TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);
	 
	 TIM_EncoderInterfaceConfig(ENCODER_TIMER,TIM_EncoderMode_TI12,    
															TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);   //IC1 IC2都计数
	 TIM_ICStructInit(&TIM_ICInitStructure);
	 TIM_ICInitStructure.TIM_ICFilter = 0x6;
	 TIM_ICInit(TIM5,&TIM_ICInitStructure);
	 
	 // Clearall pending interrupts
	 TIM_ClearFlag(TIM5, TIM_FLAG_Update);
	 TIM_ITConfig(TIM5, TIM_IT_Update,ENABLE);
	 
		//Resetcounter
	 TIM2->CNT = 0;
	 
	// ENC_Clear_Speed_Buffer();
	 
	 TIM_Cmd(TIM5, ENABLE); 
}

void Timer_Init(){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	
	
}