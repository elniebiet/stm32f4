#include "stm32f4xx.h"                  // Device header
void USART2_init(void);
char USART2_read(void);
void delay_ms(int delay);
void LED_play(int value);


int main(void)
{
	RCC->AHB1ENR |= 1; //enable clock to PortA
	GPIOA->MODER |= 0x400; //Set pin as output
	USART2_init();
	
	while(1){
		char ch = USART2_read();
		LED_play(ch);
	}
}

void USART2_init(void){		
	RCC->AHB1ENR |= 1; //Enable GPIOA Clock
	RCC->APB1ENR |= 0X20000; //Enable USART2 Clock 
	
	//configure PA3 as USART2 RX
	GPIOA->AFR[0] |= 0x7000;
	GPIOA->MODER |= 0x0080; //enable alternate function at PA3
	
	//USART2->BRR = 0x008B; //115200 baudrate @ 16MHz
	USART2->BRR = 0x0683; //9600 baudrate @ 16MHz
	USART2->CR1 = 0x0004; //enable RX
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

