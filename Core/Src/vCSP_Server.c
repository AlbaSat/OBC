#include "vCSP_Server.h"
#include "csp/csp.h"
#include "main.h"

void vCSP_Server(void *pvParameters) {
    FF_PRINTF("Server task started\r\n");

    while (1) {
		csp_packet_t *packet;
        if (csp_queue_dequeue(rx_queue_handle, &packet, CSP_MAX_TIMEOUT) == CSP_QUEUE_OK) {
            FF_PRINTF("Dequeued connection from rx_queue\r\n");
            FF_PRINTF("Packet %s received in the server\r\n", (char*) packet->data);
            csp_buffer_free(packet);
        } else {
            FF_PRINTF("Failed to dequeue connection\n");
        }
    }

    vTaskDelete(NULL);
}
