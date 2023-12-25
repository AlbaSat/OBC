/*
 * task1_ale.h
 *
 *  Created on: Dec 3, 2023
 *      Author: Alessandro
 */

#ifndef INC_TASK1_ALE_H_
#define INC_TASK1_ALE_H_

#define RAMDISK_NAME "/ram"
#define RAMDISK_SECTOR_SIZE 512UL
#define RAMDISK_SECTOR_COUNT ((100UL * 1024UL) / RAMDISK_SECTOR_SIZE)
#define IOMAN_CACHE_SIZE (RAMDISK_SECTOR_SIZE * 15UL)

void vTaskAle(void *pvParameters);

#endif /* INC_TASK1_ALE_H_ */
