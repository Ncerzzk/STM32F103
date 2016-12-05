#include <stdio.h>
#include <stdarg.h>

void Usart_Init(USART_TypeDef * USARTx,int BaudRate);
void uprintf(USART_TypeDef* USARTx, char *fmt, ...);