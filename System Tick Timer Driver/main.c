#include "stm32f4xx.h"                  // Device header

int main(void)
{
	RCC->AHB1ENR |= 1;
	GPIOA->MODER |= 0x400; 
	
	//configure systick to generate 200ms delay
	
	SysTick->LOAD = 3200000 - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = 5; 
	
	while(1){
		//check if count flag is set
		if(SysTick->CTRL & 0x10000){
			GPIOA->ODR ^= 0x20; //toggle LED
		}
	}
}
