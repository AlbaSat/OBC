/*
 * csp_i2c_settings.c
 *
 *  Created on: Jun 5, 2024
 *      Author: Alessandro
 */
#include "main.h"
#include "csp_i2c_settings.h"

// Custom I2C transmit function
//This will be used only when some other Microcontroller will be attached to the 2 GPIOs
//that act as SCL and SDA
int my_i2c_tx(void *driver_data, csp_packet_t *packet) {
    I2C_HandleTypeDef *hi2c = (I2C_HandleTypeDef *)driver_data;
    uint16_t device_address = packet->id.dst;
    HAL_StatusTypeDef status;

    // Debugging output
    printf("I2C State before transmit: %d\r\n", hi2c->State);
    printf("I2C ErrorCode before transmit: %d\r\n", hi2c->ErrorCode);

    // Clear any previous errors
    __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_BUSY | I2C_FLAG_ARLO | I2C_FLAG_BERR | I2C_FLAG_AF);

    // Send the packet data over I2C
    status = HAL_I2C_Master_Transmit(hi2c, device_address << 1, packet->data, packet->length, HAL_MAX_DELAY);

    // Debugging output
    printf("I2C State after transmit: %d\r\n", hi2c->State);
    printf("I2C ErrorCode after transmit: %d\r\n", hi2c->ErrorCode);

    if (status == HAL_OK) {
        csp_buffer_free(packet);
        return CSP_ERR_NONE;
    } else {
        printf("I2C transmit error: %d\r\n", status);
        return CSP_ERR_DRIVER;
    }
}
