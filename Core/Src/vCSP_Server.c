#include "vCSP_Server.h"
#include "csp/csp.h"
#include "main.h"

void vCSP_Server(void *pvParameters) {
    csp_print("Server task started\r\n");

    // Create socket
    csp_socket_t sock;

    // Bind socket to all ports, e.g., all incoming connections will be handled here
    if (csp_bind(&sock, CSP_ANY) != CSP_ERR_NONE) {
        printf("Server: Socket bind failed\r\n");
        vTaskDelete(NULL);
    }

    // Listen for incoming connections
    if (csp_listen(&sock, 10) != CSP_ERR_NONE) {
        printf("Server: Socket listen failed\r\n");
        vTaskDelete(NULL);
    }

    while (1) {
        // Accept incoming connection
        csp_conn_t *conn = csp_accept(&sock, CSP_DEF_TIMEOUT);

        if (conn == NULL) {
            // Timeout, no connection received
            continue;
        }

        // Read incoming packet
        csp_packet_t *packet;
        while ((packet = csp_read(conn, 50)) != NULL) {
            switch (csp_conn_dport(conn)) {
                case MY_SERVER_PORT:
                    // Process packet here
                    csp_print("Packet received on MY_SERVER_PORT: %s\r\n", (char *)packet->data);
                    csp_buffer_free(packet);
                    server_received++;
                    break;

                default:
                    // Call the default CSP service handler, handle pings, buffer use, etc.
                    csp_service_handler(packet);
                    break;
            }
        }

        // Close connection
        csp_close(conn);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    vTaskDelete(NULL);
}
