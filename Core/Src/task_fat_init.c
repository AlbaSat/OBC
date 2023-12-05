#include <stdio.h>

#include "task_fat_init.h"

#define RAMDISK_NAME "ramdisk"
#define RAMDISK_SECTOR_SIZE 512
#define RAMDISK_SECTORS 64
#define IOMANAGER_CACHE_SIZE (RAMDISK_SECTOR_SIZE * 15UL)

static void read_write_file(void) {
    const char *filepath = "/ramdisk/files/testfile.txt";
    const char *message = "Hello, Space!";
    char buffer[32] = {0};
    size_t message_size = sizeof(message);

    ff_mkdir("/ramdisk/files");

    FF_FILE *file = ff_fopen(filepath, "w");
    if (!file) {
        printf("ERROR: Unable to open file: %s\n\r", filepath);
        return;
    }

    size_t written = ff_fwrite(message, 1, message_size, file);
    if (written < message_size) {
        printf("ERROR: Expected to write %zu but written %zu\n\r", message_size, written);
        ff_fclose(file);
        return;
    }

    ff_fclose(file);

    file = ff_fopen(filepath, "r");
    if (!file) {
        printf("ERROR: Unable to open file: %s\n\r", filepath);
        return;
    }

    size_t read = ff_fread(&buffer, 1, message_size, file);
    if (read < message_size) {
        printf("ERROR: Expected to write %zu but written %zu\n\r", message_size, written);
        ff_fclose(file);
        return;
    }

    ff_fclose(file);

    printf("File Message: %s\n\r", buffer);
}

void vTaskFATInit(void *pvParameters) {
    static uint8_t RAMDiskBuff[RAMDISK_SECTOR_SIZE * RAMDISK_SECTORS] = {0};
    FF_Disk_t *disk = FF_RAMDiskInit(RAMDISK_NAME, RAMDiskBuff, RAMDISK_SECTORS, IOMANAGER_CACHE_SIZE);
    FF_RAMDiskShowPartition(disk);
    read_write_file();
}
