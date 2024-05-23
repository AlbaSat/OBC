/*
 * CSP_Server_Task.c
 *
 *  Created on: May 16, 2024
 *      Author: Alessandro
 */
#include <vCSP_Server.h>
#include "main.h"

int my_error = 0;

void vCSP_Server(void *pvParameters){

	csp_socket_t sock = {0};

	my_error = csp_bind(&sock, CSP_ANY);

	my_error = csp_listen(&sock, 10);

	for(;;)
	{

		/* Wait for a new connection, 1000 mS timeout */
		csp_conn_t *conn;
		if ((conn = csp_accept(&sock, 1000)) == NULL) {
			/* timeout */
			continue;
		}

		/* Read packets on connection, timout is 100 mS */
		csp_packet_t *packet;
		while ((packet = csp_read(conn, 50)) != NULL) {
			csp_service_handler(packet);
		}

		/* Close current connection */
		//csp_close(conn);

		vTaskDelay(pdMS_TO_TICKS(100));
	}

    vTaskDelete(NULL);
}

