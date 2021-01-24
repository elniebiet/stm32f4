//APB1 bit 17 - USART2
//USART connected to PA2

#include "stm32f4xx.h"                  // Device header

void USART2_init(void);
void USART_write_char(int ch);
void USART_write_string(char* str);
void delay_ms(int delay);

int main()
{
		USART2_init();
		while(1){
			USART_write_string("Hello world\r\n");
			delay_ms(1000);
		}
}

void USART2_init(void){
		RCC->APB1ENR |= 0x20000; //enable clock to USART2
		RCC->AHB1ENR |= 0x1; //enable clock source to PA2
	
		//GPIOA->AFR[0] = 0x0700; //set alternate function AF7, USART2 connected to AF Low, pass 0 not 1 
		GPIOA->AFR[0] = 0x0700; //set alternate function AF7, USART2 connected to AF Low, pass 0 not 1 
		GPIOA->MODER |= 0x0020; //set PA2 to alternate function
	
		USART2->BRR = 0x0683; //9600 @16MHz
		USART2->CR1 = 0x0008; //enable transmitter
		USART2->CR1 |= 0x2000; //enable USART Module, pin 13 high
}

void USART_write_char(int ch){
	//wait while tx buffer is empty
	USART2->DR = (ch & 0xFF);
	while(!(USART2->SR & (1 << 6)));
	
}

void USART_write_string(char* str){
	while(*str){
		USART_write_char(*str);
		str++;
	}
}

void delay_ms(int delay){
	int i;
	for(; delay > 0; delay--){
		for(i=0; i<3195; i++){
			;
		}
	}
}

