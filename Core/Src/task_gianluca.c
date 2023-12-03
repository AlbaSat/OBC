#include <stdio.h>

#include "task_gianluca.h"

void vTaskGianluca(void *pvParameters) {
    const char *filepath = "/ram/files/gianluca.txt";
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
