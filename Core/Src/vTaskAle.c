/*
 * vTask1.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Alessandro
 */

#include "task1_ale.h"
#include "main.h"

extern SemaphoreHandle_t printMutex;

void vTaskAle(void *pvParameters)
{
	//Setup the CSP socket to receive stuff
    csp_socket_t sock = {0};
    csp_conn_t *conn;
    csp_packet_t *packet;
    int my_error;

    my_error = csp_bind(&sock, CSP_ANY);
    if(my_error == CSP_ERR_NONE){
    	FF_PRINTF("Bound correctly \n\r");
    }

    // Set the socket to listen for incoming connections
    my_error = csp_listen(&sock, 10);
    if(my_error == CSP_ERR_NONE){
    	FF_PRINTF("Listening correctly \n\r");
    }

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
	dir_ok = ff_mkdir("/ram/firstSub");

	//Change dir
	int change_ok = 0;
	change_ok = ff_chdir("/ram/firstSub");

	//Create mock file
	FF_FILE* my_file = 0;
	my_file = ff_fopen("./a.txt", "a+");

	size_t written_items;
	char * hello;
	if(my_file != NULL){
		//Write on it
		hello = "Hello, World!\n\r";
		written_items = ff_fwrite(hello, sizeof(char), strlen(hello) / sizeof(char), my_file);
		//Close before re accessing it in the loop
		int close_ok = 0;
		close_ok = ff_fclose(my_file);
	}


	for(;;)
	{
		// TODO: this always times out
		if ((conn = csp_accept(&sock, CSP_DEF_TIMEOUT)) == NULL) {
			/* timeout */
			FF_PRINTF("Timed out \n\r");
			continue;
		}

        // Read the packet
        packet = csp_read(conn, CSP_DEF_TIMEOUT);

        // Extract the float variable from the packet
        float received_distance;
        memcpy(&received_distance, packet->data, sizeof(float));

        // Print the received distance
        printf("Received distance: %f\n", received_distance);

		char* read_buffer = pvPortMalloc(50);
		my_file = ff_fopen("./a.txt", "r");
		written_items = ff_fread(read_buffer, sizeof(char),//
				strlen(hello) / sizeof(char), my_file);

		if(xSemaphoreTake(printMutex, (TickType_t)10) == pdTRUE) {
			FF_PRINTF(read_buffer);
		    xSemaphoreGive(printMutex);
		}

		ff_fclose(my_file);

		vPortFree(read_buffer);

	    // Close the connection
	    csp_close(conn);

		vTaskDelay(pdMS_TO_TICKS(100));

	}

	vTaskDelete(NULL);
}
