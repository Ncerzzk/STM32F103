
#include "stm32f10x.h"
#include <stdio.h>
GPIO_InitTypeDef GPIO_InitStructure;

void main(){
	system_clk_set();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIOB->ODR=0x0;
	
	/*
	Usart_Init(USART1,115200);
	USART_SendData(USART1,'2');
	uprintf("hello,world");
	*/
	usart1_init();
	uprintf(USART1,"hello,world!\n");
//	Timer_Init();
	while(1){
		;
	}
	return ;
}

