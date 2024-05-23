/*
 * kiss_uart_interface.h
 *
 *  Created on: May 23, 2024
 *      Author: Alessandro
 */

#ifndef KISS_UART_INTERFACE_H
#define KISS_UART_INTERFACE_H

#include "csp.h"
#include "csp_if_kiss.h"
#include "stm32f4xx_hal.h"

// Function prototypes for KISS UART interface
int kiss_uart_tx(void *driver_data, const uint8_t *data, size_t len);
int kiss_uart_rx(void *driver_data, uint8_t *data, size_t len, uint32_t timeout);

#endif /* KISS_UART_INTERFACE_H */
