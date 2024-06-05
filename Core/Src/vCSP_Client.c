#include "vCSP_Client.h"
#include "csp/csp.h"
#include "main.h"

void vCSP_Client(void *pvParameters) {
    csp_print("Client task started\r\n");

    unsigned int count = 'A';

    while (1) {
        // Send ping to server
        //int result = csp_ping(SERVER_ADDRESS, CSP_DEF_TIMEOUT, 100, CSP_O_NONE);
        //csp_print("Ping address: %u, result %d [mS]\r\n", SERVER_ADDRESS, result);

        // Send data packet to server
        csp_conn_t *conn = csp_connect(CSP_PRIO_NORM, SERVER_ADDRESS, MY_SERVER_PORT, CSP_DEF_TIMEOUT, CSP_O_NONE);
        if (conn == NULL) {
            csp_print("Connection failed\r\n");
            continue;
        }

        csp_packet_t *packet = csp_buffer_get(100);
        if (packet == NULL) {
            csp_print("Failed to get CSP buffer\r\n");
            csp_close(conn);
            continue;
        }

        // Copy data to packet
        memcpy(packet->data, "Hello world ", 12);
        memcpy(packet->data + 12, &count, 1);
        memset(packet->data + 13, 0, 1);
        count++;

        // Set packet length
        packet->length = (strlen((char *)packet->data) + 1);

        // Send packet
        csp_send(conn, packet);

        // Close connection
        csp_close(conn);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    vTaskDelete(NULL);
}
