#include "stm32f4xx.h"                  // Device header

int main(void)
{
	RCC->AHB1ENR |= 0x01;
	GPIOA->AFR[0] |= 0x00100000; //set PA5 for tim2
	GPIOA->MODER |= 0x00000800;
	
	//Setup timer
	
	RCC->APB1ENR |= 0x01;
	TIM2->PSC = 10 - 1; //1.6MHz clock
	TIM2->ARR = 26667 - 1;
	TIM2->CNT = 0;
	TIM2->CCMR1 = 0x0060; //enable PWM Mode
	TIM2->CCER = 1; //enable PWM ch1
	TIM2->CCR1 = 8889 - 1; //pulse width 1/3 the period
	TIM2->CR1 = 1; 
	
	while(1){
		
	}
	
	
}

