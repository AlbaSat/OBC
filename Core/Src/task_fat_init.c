#include <stdio.h>
#include <stdint.h>

#include "task_fat_init.h"

#define mainRAM_DISK_NAME "/ram"
#define mainRAM_DISK_SECTOR_SIZE 512UL
#define mainRAM_DISK_SECTORS ((100UL * 1024UL) / mainRAM_DISK_SECTOR_SIZE)
#define mainIO_MANAGER_CACHE_SIZE (mainRAM_DISK_SECTOR_SIZE * 15UL)

void vTaskFATInit(void *pvParameters) {
    static uint8_t RAM_disk[mainRAM_DISK_SECTORS * mainRAM_DISK_SECTOR_SIZE];
    FF_Disk_t *disk = FF_RAMDiskInit(mainRAM_DISK_NAME, RAM_disk, mainRAM_DISK_SECTORS, mainIO_MANAGER_CACHE_SIZE);
    if (disk == NULL) {
        printf("ERROR: Unable to create disk\r\n");
        return;
    }
    FF_RAMDiskShowPartition(disk);
}
