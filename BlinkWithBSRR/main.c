#include "stm32f4xx.h"                  // Device header

void _delay(uint16_t delay);

int main(void)
{
	RCC->AHB1ENR |= 1; //enable GPIOA clock
	GPIOA->MODER |= 0x400; //01 - set PA5 as output
	
	while(1){
		GPIOA->BSRR = 0X20; //set bit 5 of BSRR i.e set the output of set high
		_delay((uint16_t)100);
		GPIOA->BSRR = 0X00200000; //set bit 21 of BSRR low i.e set the output of reset high
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
