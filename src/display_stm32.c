#include "display.h"
#include "uart_custom.h"
#include "stm32f4xx.h"

static void delay(int counter)
{
    int i;
    for (i = 0; i < counter * 10000; i++);
}

static void blinkPeriod(int unit) {
  	GPIO_SetBits(GPIOD, GPIO_Pin_15); // LED ON
	delay(200 * unit);
	GPIO_ResetBits(GPIOD, GPIO_Pin_15); // LED OFF
}

static void offPeriod(int unit) {
	delay(200 * unit);
}

void displayDot(void) {
	USART_puts(USART1, ".");
	blinkPeriod(1);
}

void displayDash(void) {
	USART_puts(USART1, "-");
	blinkPeriod(3);
}

void displaySmallSpace(void) {
	USART_puts(USART1, " ");
	offPeriod(1);
}

void displayLetterSpace(void) {
	USART_puts(USART1, "   ");
	offPeriod(3);
}

void displayWordSpace(void) {
	USART_puts(USART1, "       ");
	offPeriod(7);
}

void displaySentenceEnd(void) {
	USART_puts(USART1, "\r\n");
}
