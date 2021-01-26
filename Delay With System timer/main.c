#include "stm32f4xx.h"                  // Device header

void systickDelayMs(int n);

int main(void)
{
	RCC->AHB1ENR |= 1; 
	GPIOA->MODER |= 0x400; //set PA5 as output 
	
	while(1){
		systickDelayMs(1000);
		GPIOA->ODR ^= 0x20;
	}
}
void systickDelayMs(int n){
	SysTick->LOAD = 16000; //reload with number of clocks per milliseconds
	SysTick->VAL = 0; //clear current value register
	SysTick->CTRL = 0x5; //Enable Systick
	
	for(int i=0; i<n; i++){
		//wait until count flag is set
		while((SysTick->CTRL & 0x10000) == 0);
	}
	
	SysTick->CTRL = 0;
};

