#include "main.h"

#define Trig_high		GPIOA->BSRR=GPIO_BSRR_BS_0 			// turn on 	PA0 (trig pin)
#define Trig_low		GPIOA->BSRR=GPIO_BSRR_BR_0 			// turn off PA0 (trig pin)

#define ERROR_FACTOR  5;

volatile uint32_t dur=0;
double distance;

extern SemaphoreHandle_t printMutex;

volatile void vTask2Ale(void *pvParameters){
    //TimerHandle_t my_handle = xTimerCreate("MyTimer", pdMS_TO_TICKS(1000), pdTRUE, 0, timerCallback);
    //xTimerStart(my_handle, 0);

	//TODO: my counter is counting 5 times slower
    for(;;) {
//		Trig_low; 											//turn off trig
		Trig_high;  										//turn on trig
		delayuS(1);
		Trig_low;
		delayuS(1);
//		dur = read_echo(400000); 			//measure the time of echo pin in us
//		distance = dur * 0.01715 * ERROR_FACTOR;		//distance = (duration/2) * SOUND_SPEED
//		if(xSemaphoreTake(printMutex, (TickType_t)10) == pdTRUE) {
//		    FF_PRINTF("Distance %f cm\r\n", distance);
//		    xSemaphoreGive(printMutex);
//		}
//		delayuS(100*1000);
    }
    vTaskDelete(NULL);
}
