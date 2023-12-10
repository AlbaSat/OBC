/*
 * vTask1.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Alessandro
 */

#include "task1_ale.h"
#include "main.h"
#include "ff_ramdisk.h"

void vTaskAle(void *pvParameters)
{
	//Create RAM disk
	FF_Disk_t * disk_ale;
	static uint8_t buffer_ale[RAMDISK_SECTOR_SIZE * RAMDISK_SECTOR_COUNT] = {0};
	disk_ale = FF_RAMDiskInit(RAMDISK_NAME,//
			buffer_ale, RAMDISK_SECTOR_COUNT,//
			IOMAN_CACHE_SIZE);
	//TODO: disk gets created and partitioned correctly, but not formatted and consequently
	//not mounted correctly; following code does not work.

	//Create directory inside RAM disk
	int dir_ok = 0;
	dir_ok = ff_mkdir("/ram");

	//Create mock file
	FF_FILE * file_ale = ff_fopen("/ram/dir_ale/text_ale.txt", "w");

	//Write on it
	char * hello = "Hello, World!";
	ff_fwrite(hello, strlen(hello), 1, file_ale);
	ff_fclose(file_ale);

	pcRAMBuffer = (char *) pvPortMalloc(512);


	for(;;)
	{
		//printf("Task1\n\r");
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_12);
		vTaskDelay(1000);

		//Read already created file
		file_ale = ff_fopen("/ram/dir_ale/text_ale.txt", "r");
		//Destination buffer
		char readen_buffer[100];

		ff_fread(readen_buffer, sizeof(readen_buffer), 13, file_ale);
		//Null termination
		readen_buffer[sizeof(readen_buffer)- 1] = '\0';

		//Close file
		ff_fclose(file_ale);

		//Print over serial port
		printf(readen_buffer);
	}

}
