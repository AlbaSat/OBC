#ifndef TASK_FAT_INIT_H_
#define TASK_FAT_INIT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ff_stdio.h"
#include "ff_headers.h"
#include "ff_ramdisk.h"

void vTaskFATInit(void *pvParameters);

#ifdef __cplusplus
}
#endif

#endif // TASK_FAT_INIT_H_
