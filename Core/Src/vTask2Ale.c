#include "main.h"

#define Trig_high		GPIOA->BSRR=GPIO_BSRR_BS_0 			// turn on 	PA0 (trig pin)
#define Trig_low		GPIOA->BSRR=GPIO_BSRR_BR_0 			// turn off 	PA0 (trig pin)

uint32_t duration;
double distance;

void vTask2Ale(void *pvParameters){
	//Dynamically setup timer for the TRIGGER pin
	//This is not good for very fast timers with sub-milliseconds periods (microseconds)

    //TimerHandle_t my_handle = xTimerCreate("MyTimer", pdMS_TO_TICKS(1000), pdTRUE, 0, timerCallback);
    //xTimerStart(my_handle, 0);

    for(;;) {
    	  Trig_low; 														//turn off trig
    	  delayuS(10); 													//wait 4uS
    	  Trig_high;  													//turn on trig
    	  delayuS(10);
    	  Trig_low;
    	  duration=read_echo(400000); 								    //measure the time of echo pin
    	  distance=duration/58;											//distance=duration/2*SOUND_SPEED in cm
    	  printf("distance %f\r\n", distance);
    	  delaymS(100);													//delay for .1 second between each read
    }
    vTaskDelete(NULL);
}
