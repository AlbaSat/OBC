#include "main.h"

//REFERENCE:
//rm0383-stm32f411xce-advanced-armbased-32bit-mcus-stmicroelectronics.pdf

#define ERROR_FACTOR 1.1


//Delay for certain amount in microseconds
volatile void delayuS(uint32_t us){
	if(us < 2) us = 2;
	TIM4->ARR = us - 1;
	TIM4->EGR = 1;
	TIM4->SR &= ~1;
	TIM4->CR1 |= 1;
	while((TIM4->SR&0x0001) != 1);
	TIM4->SR &= ~(0x0001);
}
