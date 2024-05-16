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

// ULTRASONIC SENSOR DEFINES
#define TRIG_Pin GPIO_PIN_0
#define TRIG_GPIO_Port GPIOA
#define ECHO_Pin GPIO_PIN_1
#define ECHO_GPIO_Port GPIOA

//libcsp DEFINES
// Define the addresses of the nodes
#define NODE_ADDRESS_SENDER  1
#define NODE_ADDRESS_RECEIVER 2
// Define the port for communication
#define CSP_PORT 10
//Default timeout
#define CSP_DEF_TIMEOUT 1000

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
