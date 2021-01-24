#include "stm32f4xx.h"                  // Device header
#include <stdio.h>

void USART2_init(void); 
void USART2_write_char(int ch);
char USART2_read(void);
void delay_ms(int delay);
int fgetc(FILE *f);
int fputc(int c, FILE *f);

int main(void)
{
	int n;
	char str[100];
	USART2_init();
	printf("Hello from me\r\n");
	fprintf(stdout, "test for stdout\r\n");
	fprintf(stderr, "test for stderr\r\n");
	
	while(1){
		printf("How old are you ? ");
		scanf("%d", &n);
		printf("Your age is: %d\r\n", n);
		printf("Enter your first name: ");
		gets(str);
		printf("hello again: ");
		puts(str);
		printf("\r\n"); 		
	}
}

void USART2_init(void){
	RCC->AHB1ENR |= 1; //enable GPIOA
	RCC->APB1ENR |= 0x20000; //enable USART2
	
	GPIOA->AFR[0] |= 0x7700;
	GPIOA->MODER |= 0x00A0; //enable alt function for PA2 and PA3
	
	USART2->BRR = 0x0683; //set baud rate 9600 @ 16MHz
	USART2->CR1 = 0x000C; //enable the TX and RX bits of control register
	USART2->CR1 |= 0x2000;
}

void USART2_write_char(int ch){
	//wait while tx buffer is empty
	USART2->DR = (ch & 0xFF);
	while(!(USART2->SR & (1 << 6)));
	
}

//void USART2_write_string(char* str){
	//while(*str){
		//USART_write_char(*str);
		//str++;
	//}
//}

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

struct __FILE {
	int handle;
};

FILE __stdin = { 0 };
FILE __stdout = { 1 };
FILE __stderr = { 2 };

int fgetc(FILE *f){
	int c;
	c = USART2_read();
	if(c == '\r'){
		USART2_write_char(c);
		c = '\n';
	}
	USART2_write_char(c); 
	return c;
}


int fputc(int c, FILE *f){
	USART2_write_char(c);
	return c;
}
