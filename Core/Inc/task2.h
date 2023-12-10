/*
 * task2.h
 *
 *  Created on: Dec 2, 2023
 *      Author: Beatrice
 */

#ifndef INC_TASK2_H_
#define INC_TASK2_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ff_headers.h"
#include "ff_stdio.h"
#include "FreeRTOSConfig.h"

/**
 * @brief creates, writes and checks if the message is written correctly
 * in case of errors ecountered opening the file prints the nature of the error
 * itself
 * */
void vTask_bea_2(void *pvParameters);

#ifdef __cplusplus
}
#endif

#endif /* INC_TASK2_H_ */
