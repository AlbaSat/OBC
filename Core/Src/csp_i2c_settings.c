/*
 * csp_i2c_settings.c
 *
 *  Created on: Jun 5, 2024
 *      Author: Alessandro
 */
#include "main.h"
#include "csp_i2c_settings.h"

// Custom I2C transmit function
int my_i2c_tx(void *driver_data, csp_packet_t *packet) {
    I2C_HandleTypeDef *hi2c = (I2C_HandleTypeDef *)driver_data;
    uint16_t device_address = packet->id.dst;

    // Send the packet data over I2C
    if (HAL_I2C_Master_Transmit(hi2c, device_address << 1, packet->data, packet->length, HAL_MAX_DELAY) == HAL_OK) {
        csp_buffer_free(packet);
        return CSP_ERR_NONE;
    } else {
        return CSP_ERR_DRIVER;
    }
}
