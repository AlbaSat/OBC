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
    ff_mkdir("/ram/files/");
//    ff_chdir("/ram");
//
//    const char *filepath = "test.txt";
//    const char *message = "Hello, space!\r\n";
//    size_t message_size = sizeof(message);
//    char buffer[64] = {0};
//
//    FF_FILE *file = ff_fopen(filepath, "w");
//    if (!file) {
//        printf("ERROR: Unable to open file\r\n");
//        return;
//    }
//
//    size_t written = ff_fwrite(message, 1, message_size, file);
//    if (written < message_size) {
//        printf("ERROR: Unable to write the full message\n\r");
//        ff_fclose(file);
//        return;
//    }
//    ff_fclose(file);
//
//    file = ff_fopen(filepath, "r");
//    if (!file) {
//        printf("ERROR: Unable to open file\r\n");
//        return;
//    }
//
//    size_t read = ff_fread(buffer, 1, message_size, file);
//    if (read < message_size) {
//        printf("ERROR: Unable to read the full message\r\n");
//        ff_fclose(file);
//        return;
//    }
//    ff_fclose(file);
//
//    printf("File Message: %s\r\n", buffer);
}
