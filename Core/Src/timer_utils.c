#include "main.h"

//REFERENCE:
//rm0383-stm32f411xce-advanced-armbased-32bit-mcus-stmicroelectronics.pdf

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


volatile uint32_t read_echo(uint32_t timeout){
	volatile uint32_t duration = 0;

	//Wait for pulse to arrive
	while(!((GPIOA->IDR)&GPIO_IDR_ID1)){
		duration++;
		delayuS(1);
		if(duration>timeout){
			return 0;
		}
	}

	duration=0;

	//Measure pulse duration
	while((GPIOA->IDR&GPIO_IDR_ID1)){
		duration++;
		delayuS(1);
		if(duration>timeout){
			return 0;
		}
	}

	return duration;
}
