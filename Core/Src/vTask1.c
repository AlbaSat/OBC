/*
 * vTask1.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Alessandro
 */

#include "main.h"

void vTaskAle(void *pvParameters)
{
	for(;;)
	{
		printf("Task1\n\r");
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_14);
		vTaskDelay(1000);
	}

}
