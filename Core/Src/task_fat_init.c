#include <stdio.h>
#include <stdint.h>

#include "task_fat_init.h"

#define RAM_DISK_NAME "/ram"
#define RAM_DISK_SECTOR_SIZE 512UL
#define RAM_DISK_SECTORS ((50UL * 1024UL) / RAM_DISK_SECTOR_SIZE)
#define IO_MANAGER_CACHE_SIZE (RAM_DISK_SECTOR_SIZE * 15UL)
#define FILES_DIRECTORY "files"

void vTaskFATInit(void *pvParameters) {
    static uint8_t RAM_disk[RAM_DISK_SECTORS * RAM_DISK_SECTOR_SIZE];
    FF_Disk_t *disk = FF_RAMDiskInit(RAM_DISK_NAME, RAM_disk, RAM_DISK_SECTORS, IO_MANAGER_CACHE_SIZE);

    if (disk == NULL) {
        printf("ERROR: Unable to create disk\r\n");
        return;
    }

    FF_RAMDiskShowPartition(disk);
    const char *files_directory = RAM_DISK_NAME "/" FILES_DIRECTORY;
    if (ff_mkdir(files_directory) < 0) {
        printf("ERROR: Unable to create directory %s\r\n", files_directory);
        return;
    }
    printf("SUCCESS\r\n");
}
