#include "vCSP_Server.h"
#include "csp/csp.h"
#include "main.h"

void vCSP_Server(void *pvParameters) {
    FF_PRINTF("Server task started\r\n");

    while (1) {
		csp_packet_t * packet_received = csp_buffer_get(ITEM_SIZE);
		if(csp_queue_size(rx_queue_handle) != 0){
			if (csp_queue_dequeue(rx_queue_handle, packet_received, CSP_DEF_TIMEOUT) == CSP_QUEUE_OK) {
				if(xSemaphoreTake(printMutex, (TickType_t)10) == pdTRUE) {
					FF_PRINTF("Packet %s received in the server\r\n", (char*) packet_received->data);
					xSemaphoreGive(printMutex);
				}
				csp_buffer_free(packet_received);
			}
			else {
				if(xSemaphoreTake(printMutex, (TickType_t)10) == pdTRUE) {
					FF_PRINTF("Failed to dequeue connection\n");
					xSemaphoreGive(printMutex);
				}
			}
		}
		vTaskDelay(1000);
    }

//    vTaskDelete(NULL);
}
