
#include <asf.h>
#include <stdio.h>

/* Scheduler header files */
#include "FreeRTOS.h"
#include "task.h"

TaskHandle_t vTask1Handle = NULL;

void vTask1(void *p)
{	
    /* As per most tasks, this task is implemented in an infinite loop. */
    for( ;; )
    {
		int in = 0;
		//vTaskDelay(1);	// 1 sec delay
		while(in < 100)
		{
			printf(in++);
		}
		vTaskDelete(vTask1Handle);
    }
}

int main (void)
{
	board_init();
	
	xTaskCreate(vTask1, "task1", 1000, NULL, 1, &vTask1Handle);
	
	/* Start the scheduler. */
	vTaskStartScheduler();
	
	/* Execution will only reach here if there was 
	insufficient heap to start the scheduler. */
	
	for (;;);
	return 0;
}
