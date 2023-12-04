/*
 * task2.c
 *
 *  Created on: Dec 2, 2023
 *      Author: Beatrice
 */

#include "task2.h"

void vTask2(void *pvParameters){

	const char foo[] = "Prova";
	int fooSize = 0;
	/*	since in "ff_string.h" there's not a function
	 * 	similar to strlen from standard library, fooSize must be counted manually,
	 * 	assuming the size of a singular char is 1 byte	*/
	while(foo[fooSize] != '\0'){
		fooSize++;
	}
	char readString[fooSize];
	const char fileName[] = "newFile";

	//	open a new file
	FF_FILE *pxCurrentFile = ff_fopen(fileName, "w");

	/*	since size of char is 1 Byte fooSizeinBytes = fooSize	*/
	ff_fwrite(foo, fooSize, 1, pxCurrentFile);

	/*	rewind to the start of file	*/
	ff_rewind(pxCurrentFile);

	/*	reads from file and save into a buffer*/
	ff_fgets(readString,fooSize,pxCurrentFile);

	ff_fclose(pxCurrentFile);

	if(FF_strmatch(readString, foo, fooSize) == pdTRUE){
		result = 1;
	}
	else /*	FF_strmatch(readString, foo, fooSize) == pdTrue	*/{
		result = 0;
	}



}
