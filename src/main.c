#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "misc.h"
#include "stm32f4xx_usart.h"
#include "uart_custom.h"
#include "display.h"
#include "structs.h"


#define MAX_STRLEN 12
volatile char received_string[MAX_STRLEN+3];

Sign characterToSign(char c) {
  if (c == '.') return DOT;
  if (c == '-') return DASH;
  return WORD_SPACE;
}

int letterToSigns(char letter, Sign * signs) {
  Letter * target = NULL;

  for (int i = 0; i < 26; ++i) {
    if (letters[i].ascii == letter) {
      target = &letters[i];
    }
  }

  if (target == NULL) return 0;

  int length = strlen(target->morse);

  for (int i = 0; i < length; ++i) {
    signs[i] = characterToSign(target->morse[i]);
  }

  return length;
}

void displaySign(Sign sign) {
  switch(sign) {
    case DOT: displayDot(); break;
    case DASH: displayDash(); break;
    case SMALL_SPACE: displaySmallSpace(); break;
    case LETTER_SPACE: displayLetterSpace(); break;
    case WORD_SPACE: displayWordSpace(); break;
  }
}

void codeString(volatile char * text, uint8_t length) {
  for (int i = 0; i < length; ++i) {
    char c = toupper(text[i]);
    if (c == ' ') {
      displaySign(WORD_SPACE);
    } else {
      Sign signs[4];
      int signLength = letterToSigns(c, signs);
      for (int j = 0; j < signLength; ++j) {
        displaySign(signs[j]);
        if (j != signLength - 1) {
          displaySign(SMALL_SPACE);
        }
      }
      if (i != length - 1 && text[i + 1] != ' ') {
        displaySign(LETTER_SPACE);
      }
    }
  }
  displaySentenceEnd();
}

int main(void) {
	init_USART1(9600); // initialize USART1 @ 9600 baud
	USART_puts(USART1, "Hello World!\r\n"); // just send a message to indicate that it works

	GPIO_InitTypeDef gpio;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = GPIO_Pin_15;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOD, &gpio);

	GPIO_ResetBits(GPIOD, GPIO_Pin_15);

	while (1)
	{

	}


}

void USART1_IRQHandler(void){
	if( USART_GetITStatus(USART1, USART_IT_RXNE) ){

		static uint8_t cnt = 0; // this counter is used to determine the string length
		char t = USART1->DR; // the character from the USART1 data register is saved in t

		if( (t != '\r') && (cnt < MAX_STRLEN) ){
			received_string[cnt++] = t;
		}
		else{ // otherwise reset the character counter and print the received string
			codeString(received_string, cnt);
			cnt = 0;
			//USART_puts(USART1, received_string);
		}
	}
}
