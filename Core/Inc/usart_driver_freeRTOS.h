/*
 * usart_driver_freeRTOS.h
 *
 *  Created on: May 23, 2024
 *      Author: Alessandro
 */

#ifndef INC_USART_DRIVER_FREERTOS_H_
#define INC_USART_DRIVER_FREERTOS_H_

#include "FreeRTOS.h"
#include "semphr.h"

void csp_usart_lock(void *driver_data);
void csp_usart_unlock(void *driver_data);

#endif /* INC_USART_DRIVER_FREERTOS_H_ */
