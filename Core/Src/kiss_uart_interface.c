/*
 * kiss_uart_interface.c
 *
 *  Created on: May 23, 2024
 *      Author: Alessandro
 */

#include "kiss_uart_interface.h"
#include "main.h" // Include the header where huart2 is declared

extern UART_HandleTypeDef huart2; // Ensure this points to your UART handle

/**
 * @brief Transmit data over UART for KISS interface
 *
 * @param driver_data Pointer to driver-specific data (unused)
 * @param data Pointer to the data to be transmitted
 * @param len Length of the data to be transmitted
 * @return int CSP_ERR_NONE on success, CSP_ERR_DRIVER on failure
 */
int kiss_uart_tx(void *driver_data, const uint8_t *data, size_t len) {
    if (HAL_UART_Transmit(&huart2, (uint8_t *)data, len, HAL_MAX_DELAY) != HAL_OK) {
        return CSP_ERR_DRIVER;
    }
    return CSP_ERR_NONE;
}

/**
 * @brief Receive data over UART for KISS interface
 *
 * @param driver_data Pointer to driver-specific data (unused)
 * @param data Pointer to the buffer to store received data
 * @param len Length of the data to be received
 * @param timeout Timeout duration for the reception
 * @return int CSP_ERR_NONE on success, CSP_ERR_DRIVER on failure
 */
int kiss_uart_rx(void *driver_data, uint8_t *data, size_t len, uint32_t timeout) {
    if (HAL_UART_Receive(&huart2, data, len, timeout) != HAL_OK) {
        return CSP_ERR_DRIVER;
    }
    return CSP_ERR_NONE;
}
