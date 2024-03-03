#include "main.h"

void timerCallback(TimerHandle_t xTimer) {
}

void vTask2Ale(void *pvParameters){
	//Dynamically setup timer for the TRIGGER pin
	//This is not good for very fast timers with sub-milliseconds periods (microseconds)

    //TimerHandle_t my_handle = xTimerCreate("MyTimer", pdMS_TO_TICKS(1000), pdTRUE, 0, timerCallback);
    //xTimerStart(my_handle, 0);

    for(;;) {
    	delayuS(10);
    	timerCallback(NULL);
    }
    vTaskDelete(NULL);
}
