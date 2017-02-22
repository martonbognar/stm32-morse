#ifndef UART_CUSTOM_H
#define UART_CUSTOM_H

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "misc.h"
#include "stm32f4xx_usart.h"

void init_USART1(uint32_t baudrate);
void USART_puts(USART_TypeDef* USARTx, volatile char *s);

#endif
