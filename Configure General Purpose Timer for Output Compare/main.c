#include "stm32f4xx.h"                  // Device header

//toggle LED using compare mode
int main(void)
{
	RCC->AHB1ENR |= 1; 
	GPIOA->MODER |= 0x800; //set mode of PA5 to ALT function
	GPIOA->AFR[0] |= 0x00100000; //select AF1 
	
	RCC->APB1ENR |= 1; //enable clock access for timer 2
	TIM2->PSC = 1600 - 1;
	TIM2->ARR = 10000 - 1; 
	TIM2->CCMR1 = 0x30; //set output to toggle on match
	TIM2->CCR1 = 0; //set match mode
	TIM2->CCER |= 1; //enable timer 2 compare mode
	TIM2->CR1 = 1; //enable TIM2;
	
	while(1){
		
	}
}
