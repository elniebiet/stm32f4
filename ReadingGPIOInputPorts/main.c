#include "stm32f4xx.h"                  // Device header

int main()
{
	RCC->AHB1ENR |= 4; //enable clock to port C 
	RCC->AHB1ENR |= 1; //enable clock to port A
	
	GPIOA->MODER |= 0x400; //set direction of port
	
	while(1){
		if(GPIOC->IDR & 0x2000){ //if Pin 13 is high
			GPIOA->BSRR = 0X00200000; //turn off green LED
		} else { 
			GPIOA->BSRR = 0X20;// turn on green LED
		}
	}
}

