/*
 * vTask1.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Alessandro
 */

#include "task1_ale.h"
#include "main.h"
#include "ff_ramdisk.h"
#include "ff_stdio.h"

void vTaskAle(void *pvParameters)
{
	//Create RAM disk
	FF_Disk_t * disk_ale;
	static uint8_t buffer_ale[RAMDISK_SECTOR_SIZE * RAMDISK_SECTOR_COUNT] = {0};
	disk_ale = FF_RAMDiskInit(RAMDISK_NAME,//
			buffer_ale, RAMDISK_SECTOR_COUNT,//
			IOMAN_CACHE_SIZE);

	//Mount newly created disk
	FF_Error_t mounting_error;
	mounting_error = FF_Mount(disk_ale, 0);
	FF_GetErrMessage(mounting_error);

	//Create mock directory
	int dir_ok = 0;
	//Do not call the folder "subfolder", that keyword crashes
	dir_ok = ff_mkdir("/ram/hello");

	int change_ok = 0;
	if(ff_finddir("/ram/hello") == 0){
		printf("Could not find the newly created folder");
	}
	else{
		change_ok = ff_chdir("/ram/hello");
	}

	//Create mock file
	int my_file = 0;
	my_file = ff_fopen("prova.txt", "a");	//TODO: now this crashes into a semaphore wait forever

	size_t written_items = 0;
	char * hello;
	if(my_file != NULL){
		//Write on it
		hello = "Hello, World!";
		written_items = ff_fwrite(hello, sizeof(char), strlen(hello) / sizeof(char), my_file);
	}
	ff_fclose(my_file);


	for(;;)
	{
		//printf("Task1\n\r");
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_12);

		char* read_buffer[50];
		my_file = ff_fopen("prova.txt", "r");
		written_items = ff_fread(read_buffer, sizeof(char),//
				strlen(hello) / sizeof(char), my_file);

		printf(read_buffer);

		ff_fclose(my_file);

		vTaskDelay(1000);

	}

}
