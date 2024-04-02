#include "main.h"

void delaymS(uint32_t ms) //delay for certain amount in milliseconds
	{
	SysTick->LOAD=16000-1;
	SysTick->VAL=0;
	SysTick->CTRL=0x5;

	for (int i=0;i<ms;i++)
	{
		while(!(SysTick->CTRL &0x10000)){}
	}

	SysTick->CTRL=0;

}

void delayuS(uint32_t us) //delay for certain amount in microseconds
	{
	for(int i =0;i<us;i++){

			 while(!(TIM1->SR & 1)){}   /*wait for UIF set*/
				 TIM1->SR &= ~1;

	}
}

uint32_t read_echo(uint32_t timeout)
	{
	uint32_t duration;

	while(!((GPIOA->IDR)&GPIO_IDR_ID1)){duration++;delayuS(1);

	if(duration>timeout){return 0;}

	}

	duration=0;

	while((GPIOA->IDR&GPIO_IDR_ID1)){duration++;delayuS(1);if(duration>timeout){return 0;} }
		return duration;
	}
