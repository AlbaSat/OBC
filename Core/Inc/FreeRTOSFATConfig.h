/*
 * FreeRTOSFATConfig.h
 *
 *  Created on: 27 nov 2023
 *      Author: edoardo
 */

#ifndef INC_FREERTOSFATCONFIG_H_
#define INC_FREERTOSFATCONFIG_H_

#define ffconfigBYTE_ORDER pdFREERTOS_LITTLE_ENDIAN
#define ffconfigHAS_CWD 0

#define ffconfigLFN_SUPPORT 0
#define ffconfigINCLUDE_SHORT_NAME 0
#define ffconfigSHORTNAME_CASE 0
#define ffconfigUNICODE_UTF16_SUPPORT 0
#define ffconfigUNICODE_UTF8_SUPPORT 0
#define ffconfigFAT12_SUPPORT 0
#define ffconfigOPTIMISE_UNALIGNED_ACCESS 0
#define ffconfigCACHE_WRITE_THROUGH 0
#define ffconfigWRITE_BOTH_FATS 0
#define ffconfigWRITE_FREE_COUNT 0
#define ffconfigTIME_SUPPORT 0
#define ffconfigREMOVABLE_MEDIA 0
#define ffconfigMOUNT_FIND_FREE 0
#define ffconfigFSINFO_TRUSTED 0
#define ffconfigPATH_CACHE 0
#define ffconfigPATH_CACHE_DEPTH 0
#define ffconfigHASH_CACHE 0
#define ffconfigHASH_FUNCTION 0
#define ffconfigMKDIR_RECURSIVE 0
//#define ffconfigBLKDEV_USES_SEM 1
#define ffconfigMALLOC(size) pvPortMalloc(size)
#define ffconfigFREE(ptr) vPortFree(ptr)
#define ffconfig64_NUM_SUPPORT 0
#define ffconfigMAX_PARTITIONS 1
#define ffconfigMAX_FILE_SYS 2
#define ffconfigDRIVER_BUSY_SLEEP_MS 4
#define ffconfigFPRINTF_SUPPORT 1
#define ffconfigFPRINTF_BUFFER_LENGTH 10
#define ffconfigINLINE_MEMORY_ACCESS 0
#define ffconfigFAT_CHECK 0
#define ffconfigMAX_FILENAME 10

#define configNUM_THREAD_LOCAL_STORAGE_POINTERS 15
#define ffconfigCWD_THREAD_LOCAL_INDEX 0

#define ffconfigSD_OK 0

#define ffconfigDEV_SUPPORT    1

#endif /* INC_FREERTOSFATCONFIG_H_ */
