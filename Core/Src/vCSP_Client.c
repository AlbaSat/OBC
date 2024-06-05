/*
 * CSP_Server_Task.c
 *
 *  Created on: May 16, 2024
 *      Author: Alessandro
 */

#include <vCSP_Client.h>
#include "main.h"

int result = 0;

void vCSP_Client(void *pvParameters){
	for(;;)
	{
		csp_socket_t sock = {0};
		int my_error = 0;

		my_error = csp_bind(&sock, CSP_ANY);

		my_error = csp_listen(&sock, 10);
		/* Send ping to server, timeout 1000 mS, ping size 100 bytes */
		result = csp_ping(NODE_ADDRESS_SERVER, 1000, 10, CSP_O_NONE);
		printf("Ping address with result in [mS]: %d \n\r", result);

		vTaskDelay(pdMS_TO_TICKS(100));
	}

    vTaskDelete(NULL);
}
