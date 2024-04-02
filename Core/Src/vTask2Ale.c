#include "main.h"

#define Trig_high		GPIOA->BSRR=GPIO_BSRR_BS_0 			// turn on 	PA0 (trig pin)
#define Trig_low		GPIOA->BSRR=GPIO_BSRR_BR_0 			// turn off 	PA0 (trig pin)

uint32_t duration;
double distance;

extern SemaphoreHandle_t printMutex;

void vTask2Ale(void *pvParameters){
	//Dynamically setup timer for the TRIGGER pin
	//This is not good for very fast timers with sub-milliseconds periods (microseconds)

    //TimerHandle_t my_handle = xTimerCreate("MyTimer", pdMS_TO_TICKS(1000), pdTRUE, 0, timerCallback);
    //xTimerStart(my_handle, 0);

    for(;;) {
		Trig_low; 											//turn off trig
		delayuS(10); 										//wait 10uS
		Trig_high;  										//turn on trig
		delayuS(10);
		Trig_low;
		duration=read_echo(400000); 						//measure the time of echo pin in us
		distance=duration*0.1715*0.5;						//distance=duration/2*SOUND_SPEED in cm
		if(xSemaphoreTake(printMutex, (TickType_t)10) == pdTRUE) {
		    FF_PRINTF("distance %f cm\r\n", distance);
		    xSemaphoreGive(printMutex);
		}
		vTaskDelay(pdMS_TO_TICKS(100));
    }
    vTaskDelete(NULL);
}
