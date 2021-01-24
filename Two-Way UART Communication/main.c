#include "stm32f4xx.h"                  // Device header

void USART2_init(void);
char USART2_read(void);
void delay_ms(int delay);
void LED_play(int value);
void USART2_init(void);
void USART_write_char(int ch);
void USART_write_string(char* str);

int main(void)
{
	RCC->AHB1ENR |= 1; //enable clock to PortA
	//GPIOA->MODER |= 0x400; //Set pin as output
	USART2_init();
	
	while(1){
		GPIOA->MODER |= 0x400;
		USART2->CR1 &=~ 0x0008;
		USART2->CR1 |= 0x0004; //enable RX
		char ch = USART2_read();
		LED_play(ch);
		
		GPIOA->MODER &=~ 0x400;
		USART2->CR1 &=~ 0x0004; //enable RX
		USART2->CR1 |= 0x0008;
		USART_write_string("Hello world\r\n");
		delay_ms(1000);
		
	}
}

void USART2_init(void){		
	RCC->AHB1ENR |= 0x1; //Enable GPIO Port A Clock
	RCC->APB1ENR |= 0X20000; //Enable USART2 Clock 
	
	//configure PA3 as USART2 RX
	GPIOA->AFR[0] |= 0x7000; //select alternate function
	GPIOA->MODER |= 0x0080; //enable alternate function at PA3
	
	//configure PA2 as USART2 TX
	GPIOA->AFR[0] |= 0x0700; //select alternate function
	GPIOA->MODER |= 0x0020; //set PA2 to alternate function
	
	USART2->BRR = 0x0683; //9600 baudrate @ 16MHz
	
	//USART2->CR1 = 0x0004; //enable RX
	//USART2->CR1 = 0x0008; //enable TX
	
	USART2->CR1 |= 0x2000; //enable USART2
}

char USART2_read(void){
	while(!(USART2->SR & 0X0020)){} //wait until char arrives
	return USART2->DR;
}

void delay_ms(int delay){
	int i;
	for(; delay > 0; delay--){
		for(i=0; i<3195; i++){
			;
		}
	}
}

void LED_play(int value){
	value %= 16; 
	for(; value>0; value--){
		GPIOA->BSRR = 0x20; //turn on LED
		delay_ms(10);
		GPIOA->BSRR = 0x00200000; //Turn off LED
		delay_ms(10);
	}
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
