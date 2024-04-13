#include "main.h"

#define Trig_high		GPIOA->BSRR=GPIO_BSRR_BS_0 			// turn on 	PA0 (trig pin)
#define Trig_low		GPIOA->BSRR=GPIO_BSRR_BR_0 			// turn off PA0 (trig pin)

#define us_per_Tick 3	//50% error (3us instead of 2us with the oscilloscope) due to use of HSI

uint32_t numTicks;

//Speed of sound in cm/us divided by two
const float speed_of_sound = 0.0343 / 2;
float distance;

extern SemaphoreHandle_t printMutex;

volatile void vTask2Ale(void *pvParameters){
    //TimerHandle_t my_handle = xTimerCreate("MyTimer", pdMS_TO_TICKS(1000), pdTRUE, 0, timerCallback);
    //xTimerStart(my_handle, 0);

    for(;;) {
//		//Set TRIG to LOW for few us
//		HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);
//		delayuS(3);

		HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_SET);
		delayuS(2);
		HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);
		delayuS(2);
//
//		//Wait for pulse to arrive
//		while(HAL_GPIO_ReadPin(ECHO_GPIO_Port, ECHO_Pin) == GPIO_PIN_RESET);
//
//		//Start measuring pulse width in us
//		numTicks = 0;
//		while(HAL_GPIO_ReadPin(ECHO_GPIO_Port, ECHO_Pin) == GPIO_PIN_SET){
//		  numTicks++;
//		  delayuS(2);	//TODO measure this delay that each tick is taking; for now put 2.8
//		}
//
//		//Estimate distance
//		distance = (numTicks + 0.0f) * us_per_Tick * speed_of_sound;
//		if(xSemaphoreTake(printMutex, (TickType_t)10) == pdTRUE) {
//			FF_PRINTF("Distance %f cm\r\n", distance);
//			xSemaphoreGive(printMutex);
//		}
//
//		HAL_Delay(100);
    }
    vTaskDelete(NULL);
}
