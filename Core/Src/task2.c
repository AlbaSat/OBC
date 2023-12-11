/*
 * task2.c
 *
 *  Created on: Dec 2, 2023
 *      Author: Beatrice
 */

#include "task2.h"

void vTask_bea_2(void *pvParameters){

	/*	create RAM disk*/
	static uint8_t buffer_bea [RAM_DISK_SECTOR_SIZE*RAM_DISK_SECTOR_COUNT] = {0};
	FF_Disk_t *disk_bea = FF_RAMDiskInit(RAM_DISK_NAME, buffer_bea, RAM_DISK_SECTOR_COUNT, IOMAN_CACHE_SIZE);

	const char *filepath = "/foodir/files/newfile.txt";
	const char foo[] = "Hello world!";
	size_t foo_size = sizeof(foo)* sizeof(char);
	char readString[foo_size];

	//create a new directory
	ff_mkdir("/foodir/files");

	//	open a new file and see if it is open correctly
	FF_FILE *pxCurrentFile = ff_fopen(filepath, "w");

	if(pxCurrentFile){

		ff_fwrite(foo, foo_size, 1, pxCurrentFile);

		/*	rewind to the start of file	*/
		ff_rewind(pxCurrentFile);

		/*	reads from file and save into a buffer*/
		ff_fgets(readString,foo_size,pxCurrentFile);

		ff_fclose(pxCurrentFile);

		if(FF_strmatch(readString, foo, foo_size) == pdTRUE){
			printf("Successful file-writing procedure\n");
		}
		else /*	FF_strmatch(readString, foo, fooSize) == pdTrue	*/{
			printf("Unsuccessful file-writing procedure: the message was nt written correctly\n");
		}
	}
	else /* if pxCurrent == NULL */{
		int error_value = stdioGET_ERRNO();

		switch(error_value){

		case pdFREERTOS_ERRNO_ENOENT:
			printf("ERROR: file does not exist\n");

		case pdFREERTOS_ERRNO_EACCES:
			printf("ERROR: permission denied\n");
		}

		perror("File could not be opened\n");
	}



}
