/*
 * CSP_Server_Task.c
 *
 *  Created on: May 16, 2024
 *      Author: Alessandro
 */

#include "main.h"
#include "CSP_Client_Task.h"

int result = 0;

void vCSP_Client(void *pvParameters){
	for(;;)
	{
		/* Send ping to server, timeout 1000 mS, ping size 100 bytes */
		result = csp_ping(NODE_ADDRESS_SERVER, 1000, 100, CSP_O_NONE);
		printf("Ping address with result in [mS]: %d \n\r", result);
//        char message[4];
//        snprintf(message,"%d",result);
//        printf(message,4);
//		/* Send data packet (string) to server */
//
//		/* 1. Connect to host on 'server_address', port MY_SERVER_PORT with regular UDP-like protocol and 1000 ms timeout */
//		csp_conn_t * conn = csp_connect(CSP_PRIO_NORM, server_address, MY_SERVER_PORT, 1000, CSP_O_NONE);
//		if (conn == NULL) {
//			/* Connect failed */
//			printf("Connection failed\n",strlen("Connection failed\n"));
//			return;
//		}
//
//		/* 2. Get packet buffer for message/data */
//		csp_packet_t * packet = csp_buffer_get(100);
//		if (packet == NULL) {
//			/* Could not get buffer element */
//			printf("Failed to get CSP buffer\n",strlen("Failed to get CSP buffer\n"));
//			return;
//		}
//
//		/* 3. Copy data to packet */
//        memcpy(packet->data, "Hello world ", 12);
//        memcpy(packet->data + 12, &count, 1);
//        memset(packet->data + 13, 0, 1);
//        count++;
//
//		/* 4. Set packet length */
//		packet->length = (strlen((char *) packet->data) + 1); /* include the 0 termination */
//
//		/* 5. Send packet */
//		csp_send(conn, packet);
//
//		/* 6. Close connection */
//		csp_close(conn);
		vTaskDelay(pdMS_TO_TICKS(100));
	}

    vTaskDelete(NULL);
}
