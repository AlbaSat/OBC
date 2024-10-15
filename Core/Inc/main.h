/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>

#include "stm32f4xx.h"
#include "stm32f4xx_hal_conf.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "projdefs.h"
#include "portmacro.h"
#include "task.h"
#include "timers.h"

#include "FreeRTOSFATConfig.h"
#include "ff_ramdisk.h"
#include "ff_stdio.h"

#include "timer_utils.h"
#include "task1_ale.h"
#include "task2_ale.h"

#include "csp.h"
#include "csp_types.h"
#include <vCSP_Server.h>
#include <vCSP_Client.h>
#include <kiss_uart_interface.h>
#include "csp/interfaces/csp_if_i2c.h"
#include "csp/interfaces/csp_if_lo.h"
#include <csp/csp_rtable.h>
#include "csp_i2c_settings.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

//PRINT MUTEX
extern SemaphoreHandle_t printMutex;

// ULTRASONIC SENSOR DEFINES
#define TRIG_Pin GPIO_PIN_0
#define TRIG_GPIO_Port GPIOA
#define ECHO_Pin GPIO_PIN_1
#define ECHO_GPIO_Port GPIOA

//libcsp DEFINES
#define MY_SERVER_PORT  0
#define SERVER_ADDRESS  0
#define CSP_DEF_TIMEOUT 100

#define CSP_RX_QUEUE_LENGTH 10
// TODO: pass as item an entire connection instead of a single packet
#define ITEM_SIZE 100    // Each item size

extern char rx_queue_buffer[CSP_RX_QUEUE_LENGTH * ITEM_SIZE];
extern csp_static_queue_t rx_static_queue;
extern csp_queue_handle_t rx_queue_handle;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
