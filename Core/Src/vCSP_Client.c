#include "vCSP_Client.h"
#include "csp/csp.h"
#include "main.h"

void vCSP_Client(void *pvParameters) {
    FF_PRINTF("Client task started\r\n");

	unsigned int count = 'A';

    while (1) {
        csp_conn_t *conn;
    	conn = csp_connect(CSP_PRIO_NORM, SERVER_ADDRESS, MY_SERVER_PORT, CSP_DEF_TIMEOUT, CSP_O_NONE);

    	if (conn == NULL) {
			FF_PRINTF("Connection failed\r\n");
			continue;
		}
        else{
        	FF_PRINTF("Client Connected!\r\n");

			// Send packet

    		/* 2. Get packet buffer for message/data */
    		csp_packet_t * packet = csp_buffer_get(100);
    		if (packet == NULL) {
    			/* Could not get buffer element */
    			csp_print("Failed to get CSP buffer\n");
    			return;
    		}

    		/* 3. Copy data to packet */
            memcpy(packet->data, "Hello world ", 12);
            memcpy(packet->data + 12, &count, 1);
            memset(packet->data + 13, 0, 1);
            count++;

    		/* 4. Set packet length */
    		packet->length = (strlen((char *) packet->data) + 1); /* include the 0 termination */

			if(csp_queue_enqueue(rx_queue_handle, &packet, CSP_DEF_TIMEOUT) == CSP_QUEUE_OK){
				FF_PRINTF("Packet %s sent\r\n", (char *) packet->data);
	            csp_buffer_free(packet);
			}
			else{
				FF_PRINTF("Packet not sent\r\n");
				continue;
			}
        }

        // Close connection
        csp_close(conn);
    }

    vTaskDelete(NULL);
}
