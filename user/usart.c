#include "stm32f10x.h"
#include "usart.h"



void Usart_Init(USART_TypeDef * USARTx,int BaudRate){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	
	//设置串口信息
  USART_InitStructure.USART_BaudRate = BaudRate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

		

	//设置中断
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	//NVIC_InitStructure.NVIC_IRQChannel = USARTy_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  //NVIC_Init(&NVIC_InitStructure);
	
	if(USARTx==USART1){
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		
			//设置TX,推挽输出
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
			GPIO_Init(GPIOA,&GPIO_InitStructure);
			
			//设置RX,浮空输入
			GPIO_InitStructure.GPIO_Pin= GPIO_Pin_10;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	
			GPIO_Init(GPIOA,&GPIO_InitStructure);
			
			//设置USART1中断
			NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
			NVIC_Init(&NVIC_InitStructure);
		
			
		
	}

	USART_Init(USARTx,&USART_InitStructure);
	
	USART_Cmd(USARTx,ENABLE);
	USART_ClearFlag(USARTx, USART_FLAG_TC);
	
	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE); 
	USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);  //发送中断  发送一般不需要中断
	
}

void usart1_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	  USART_InitStructure.USART_BaudRate = 115200;                 /*??????115200*/
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;  /*??????8?*/
    USART_InitStructure.USART_StopBits = USART_StopBits_1;       /*??????1?*/
    USART_InitStructure.USART_Parity = USART_Parity_No;          /*?????*/    
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; /*??????*/
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;      /*?????*/
    /*????COM1??????GPIO??,????????????*/
	
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
}

void uprintf(USART_TypeDef* USARTx, char *fmt, ...)
{

	char buffer[100 + 1];
	u8 i = 0;
	
	va_list arg_ptr;
	
	va_start(arg_ptr, fmt);  
	
	vsnprintf(buffer, 100 + 1, fmt, arg_ptr);
	
	USART_ClearFlag(USARTx, USART_FLAG_TXE);
	
	while ((i < 100) && buffer[i])
	{
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
	  USART_SendData(USARTx, (u8)buffer[i++]); 
	}
	
	va_end(arg_ptr);
	
}