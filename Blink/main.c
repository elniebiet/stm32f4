//PA5
//AHB1
//RCC_AHB1ENR //control register clock to port A

//need to set direction of port in or out; and data
//GPIOx_MODER
//GPIOx_ODR and ..IDR
#include "stm32f4xx.h"                  // Device header
void _delay(uint16_t delay);

int main(void)
{
	RCC->AHB1ENR |= 1; //enable GPIOA clock
	GPIOA->MODER |= 0x400; //01 - set PA5 as output
	
	while(1){
		GPIOA->ODR |= 0X20; //
		_delay((uint16_t)100);
		GPIOA->ODR &=~ 0X20; 
		_delay((uint16_t)100);
		
	}
}

void _delay(uint16_t delay){
	uint16_t i, j = 0;
	for(i=0; i<delay; i++){
		for(j=0; j<3195; j++){
			;
		}
	}
}
