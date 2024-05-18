/*
 * CSP_Server_Task.c
 *
 *  Created on: May 16, 2024
 *      Author: Alessandro
 */
#include "main.h"
#include "CSP_Server_Task.h"


void vCSP_Server(void *pvParameters){
	csp_socket_t sock = {0};

	csp_bind(&sock, CSP_ANY);

	csp_listen(&sock, 10);

	for(;;)
	{

		/* Wait for a new connection, 10000 mS timeout */
		csp_conn_t *conn;
		if ((conn = csp_accept(&sock, 10000)) == NULL) {
			/* timeout */
			continue;
		}

		/* Read packets on connection, timout is 100 mS */
		csp_packet_t *packet;
		while ((packet = csp_read(conn, 50)) != NULL) {
			switch (csp_conn_dport(conn)) {
			case CSP_PORT:
				/* Process packet here */
				printf("Packet received on CSP_PORT:",strlen("Packet received on CSP_PORT:"));
                printf((char *) packet->data,packet->length);
                printf("\r\n",strlen("\r\n"));
				csp_buffer_free(packet);
				break;

			default:
				/* Call the default CSP service handler, handle pings, buffer use, etc. */
				csp_service_handler(packet);
				break;
			}
		}

		/* Close current connection */
		csp_close(conn);

		vTaskDelay(pdMS_TO_TICKS(100));
	}

    vTaskDelete(NULL);
}

