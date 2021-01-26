#include "stm32f4xx.h"                  // Device header

//create a 1sec timer
int main()
{
	RCC->AHB1ENR |= 1;
	GPIOA->MODER |= 0x400; 
	
	//TIM2 configuration
	RCC->APB1ENR |= 0x1;
	//To create 1MHz timer, divide by 1600, then by 10000
	TIM2->PSC = 1600 - 1; //divide 16M by 1600 
	TIM2->ARR = 10000 - 1; //autoreload (now 10000) by 10000
	TIM2->CNT = 0; //clear timer counter
	TIM2->CR1 = 1; //enable timer by setting timer control register
	
	while(1){
		while(!(TIM2->SR & 1)); 
		TIM2->SR &=~ 1;
		GPIOA->ODR ^= 0x20; 
	}
}
