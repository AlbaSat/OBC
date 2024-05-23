/*
 * usart_driver_freeRTOS.c
 *
 *  Created on: May 23, 2024
 *      Author: Alessandro
 */

#include "usart_driver_freeRTOS.h"

extern SemaphoreHandle_t csp_usart_Mutex;

void csp_usart_lock(void *driver_data) {
    if (csp_usart_Mutex != NULL) {
        xSemaphoreTake(csp_usart_Mutex, portMAX_DELAY);
    }
}

void csp_usart_unlock(void *driver_data) {
    if (csp_usart_Mutex != NULL) {
        xSemaphoreGive(csp_usart_Mutex);
    }
}
