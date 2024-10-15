#include "vCSP_Client.h"
#include "csp/csp.h"
#include "main.h"

void vCSP_Client(void *pvParameters) {
	if(xSemaphoreTake(printMutex, (TickType_t)10) == pdTRUE) {
	    FF_PRINTF("Client task started\r\n");
		xSemaphoreGive(printMutex);
	}

	unsigned int count = 'A';

    while (1) {
        csp_conn_t *conn;
    	conn = csp_connect(CSP_PRIO_NORM, SERVER_ADDRESS, MY_SERVER_PORT, CSP_DEF_TIMEOUT, CSP_O_NONE);

    	if (conn == NULL) {
			if(xSemaphoreTake(printMutex, (TickType_t)10) == pdTRUE) {
				FF_PRINTF("Connection failed\r\n");
				xSemaphoreGive(printMutex);
			}
			continue;
		}
        else{
			if(xSemaphoreTake(printMutex, (TickType_t)10) == pdTRUE) {
	        	FF_PRINTF("Client Connected!\r\n");
				xSemaphoreGive(printMutex);
			}

			// Send packet

    		/* 2. Get packet buffer for message/data */
    		csp_packet_t * packet_sent = csp_buffer_get(ITEM_SIZE);
    		if (packet_sent == NULL) {
    			/* Could not get buffer element */
    			csp_print("Failed to get CSP buffer\n");
    			return;
    		}

    		/* 3. Copy data to packet */
            memcpy(packet_sent->data, "Hello world ", 12);
            memcpy(packet_sent->data + 12, &count, 1);
            memset(packet_sent->data + 13, 0, 1);
            count++;

    		/* 4. Set packet length */
    		packet_sent->length = (strlen((char *) packet_sent->data) + 1); /* include the 0 termination */

			if(csp_queue_enqueue(rx_queue_handle, packet_sent, CSP_DEF_TIMEOUT) == CSP_QUEUE_OK){
				if(xSemaphoreTake(printMutex, (TickType_t)10) == pdTRUE) {
					FF_PRINTF("Packet %s sent\r\n", (char *) packet_sent->data);
					xSemaphoreGive(printMutex);
				}
	            csp_buffer_free(packet_sent);
	            // Close connection
	            csp_close(conn);
			}
			else{
				if(xSemaphoreTake(printMutex, (TickType_t)10) == pdTRUE) {
					FF_PRINTF("Packet not sent\r\n");
					xSemaphoreGive(printMutex);
				}
				continue;
		        // Close connection
		        csp_close(conn);
			}
        }


        vTaskDelay(1000);
    }

//    vTaskDelete(NULL);
}
