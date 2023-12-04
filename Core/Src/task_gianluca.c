#include <stdio.h>

#include "task_gianluca.h"

#define SRAM1_BASE            0x20000000UL /*!< SRAM1(128 KB) base address in the alias region                             */
#define DISK_SECTORS 512
#define DISK_CACHE_SECTORS (512 * 128)

#define HIDDEN_SECTOR_COUNT 8
#define PRIMARY_PARTITIONS 1

static FF_Disk_t *disk;

//#define FILE_SYSTEM_ERROR(error_code, message)                                              \
//    do {                                                                                    \
//        printf("ERROR: Unable to %s: %s", message, FF_GetErrMessage(error_code));           \
//        FF_RAMDiskDelete(disk);                                                             \
//        return;                                                                             \
//    } while (0)


static void setup_disk(void) {
    const char *disk_name = "ramdisk";
    uint8_t *disk_start = SRAM1_BASE;
    FF_Error_t error;

    disk = FF_RAMDiskInit(disk_name, disk_start, DISK_SECTORS, DISK_CACHE_SECTORS);
    if (!disk) {
        printf("ERROR: Unable to create disk %s", disk_name);
        return;
    }

    //error = FF_Partition(disk, &(FF_PartitionParameters_t) {
    //                                .ulSectorCount = disk->ulNumberOfSectors,
    //                                .ulHiddenSectors = HIDDEN_SECTOR_COUNT,
    //                                .xPrimaryCount = PRIMARY_PARTITIONS,
    //                                .eSizeType = eSizeIsQuota,
    //                            });

    //FILE_SYSTEM_ERROR(error, "Partiton Disk");

    //error = FF_Format(disk, ramPARTITION_NUMBER, pdTRUE, pdTRUE);

    //FILE_SYSTEM_ERROR(error, "Format Disk");
}

static void delete_disk(void) {
    FF_RAMDiskDelete(disk);
}

static void read_write_file(void) {
    const char *filepath = "/ramdisk/gianluca.txt";
    const char *message = "Hello, Space!";
    char buffer[64] = {0};
    size_t message_size = sizeof(message);

    FF_FILE *file = ff_fopen(filepath, "w");
    if (!file) {
        printf("ERROR: Unable to open file: %s\n\r", filepath);
    }

    size_t written = ff_fwrite(message, 1, message_size, file);
    if (written < message_size) {
        printf("ERROR: Expected to write %zu but written %zu\n\r", message_size, written);
    }

    ff_fclose(file);

    file = ff_fopen(filepath, "r");
    if (!file) {
        printf("ERROR: Unable to open file: %s\n\r", filepath);
    }

    size_t read = ff_fread(&buffer, 1, message_size, file);
    if (read < message_size) {
        printf("ERROR: Expected to write %zu but written %zu\n\r", message_size, written);
    }

    ff_fclose(file);

    printf("File Message: %s\n\r", buffer);
}

void vTaskGianluca(void *pvParameters) {
    setup_disk();
    read_write_file();
}
