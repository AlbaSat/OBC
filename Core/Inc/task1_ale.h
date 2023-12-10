/*
 * task1_ale.h
 *
 *  Created on: Dec 3, 2023
 *      Author: Alessandro
 */

#ifndef INC_TASK1_ALE_H_
#define INC_TASK1_ALE_H_

#define RAMDISK_NAME "ram_ale"
#define RAMDISK_SECTOR_SIZE 512
#define RAMDISK_SECTOR_COUNT 32
#define IOMAN_CACHE_SIZE (RAMDISK_SECTOR_SIZE * 10UL)

void vTaskAle(void *pvParameters);

#endif /* INC_TASK1_ALE_H_ */
