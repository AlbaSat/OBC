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

/*	Libraries included from FreeRTOS FAT	*/
/*#include "../../Middlewares/Third_Party/Lab-Project-FreeRTOS-FAT/include/ff_stdio.h"
#include "../../Middlewares/Third_Party/Lab-Project-FreeRTOS-FAT/include/ff_file.h"
#include "../../Middlewares/Third_Party/Lab-Project-FreeRTOS-FAT/include/ff_string.h"
*/
//#include "ff_headers.h"
#include "../../Middlewares/Third_Party/Lab-Project-FreeRTOS-FAT/include/ff_stdio.h"
#include "FreeRTOSConfig.h"

/*	variable which saves task2 operation's result, should be extern?	*/
static int result;

/*	Function's declaration	*/
void vTask2(void *pvParameters);

#ifdef __cplusplus
}
#endif

#endif /* INC_TASK2_H_ */
