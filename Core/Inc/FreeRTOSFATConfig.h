/*
 * FreeRTOSFATConfig.h
 *
 *  Created on: 27 nov 2023
 *      Author: edoardo
 */

#ifndef INC_FREERTOSFATCONFIG_H_
#define INC_FREERTOSFATCONFIG_H_

#define ffconfigBYTE_ORDER pdFREERTOS_LITTLE_ENDIAN
#define ffconfigCWD_THREAD_LOCAL_INDEX 1
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS 15
#define FF_PRINTF printf
#define ffconfigWRITE_BOTH_FATS 1
#define ffconfigMALLOC(size)    pvPortMalloc(size)
#define ffconfigFREE(ptr)       vPortFree(ptr)
#define	ffconfigMAX_PARTITIONS  1
#define ffconfigMIN_CLUSTERS_FAT16  64




#endif /* INC_FREERTOSFATCONFIG_H_ */
