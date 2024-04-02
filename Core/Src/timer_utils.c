#include "main.h"
#include <stdbool.h>

//macros for trigger pin
#define Trig_high		GPIOA->BSRR = GPIO_BSRR_BS_0 			// turn on 	PA0 (trig pin)
#define Trig_low		GPIOA->BSRR = GPIO_BSRR_BR_0 			// turn off PA0 (trig pin)

volatile bool my_trig = false;

void TIMER_setup(void){
	//Configure Timer to generate microseconds delay
	//The default freeRTOS xTimerCreate is too slow and memory hungry;
	//use one of many dedicated timers

	//Update frequency: freqclk /(Prescaler-1)

	//Atm there is no HAL for the timers ¯\_(ツ)_/¯

	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;	/* Enable TIM3 connection with clock through APB1*/

	TIM2->PSC = 1 - 1;  				/* 16MHz / 1 = 16 MHz*/
	TIM2->ARR = 160 - 1;  				/* 160 ticks at 62.5ns are 10us*/
	TIM2->CNT = 0;						/* Initial counter value to zero*/
	TIM2->DIER |= TIM_DIER_UIE;			/* Enable timer interrupts*/

	NVIC_EnableIRQ(TIM2_IRQn);
	NVIC_SetPriority(TIM2_IRQn, configMAX_PRIORITIES-1);

	TIM2->CR1 = TIM_CR1_CEN;			/* Enable TIM2 counting*/

	return;
}

//Delay for certain amount in microseconds
void delayuS(uint32_t us){
	for(int i=0; i<us; i++){
		//Wait for UIF set
		while(!(TIM2->SR & TIM_SR_UIF)){

		}
		//Clear the flag
		TIM2->SR &= ~TIM_SR_UIF;
	}
}


void TIM2_IRQHandler(void)
{
	if(TIM2->SR & TIM_SR_UIF){
		if(my_trig){
			Trig_low;
		}
		else{
			Trig_high;
		}
		my_trig = !my_trig;
	}

	/* Clear the Interrupt Status */
	TIM2->SR &= ~TIM_SR_UIF;
}
