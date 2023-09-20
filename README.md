# AlbaSat-OBC
Temporary repo for OBC software development

## Tutorial

This tutorial shows how to setup a working Microchip Studio project with FreeRTOS 12.0.1 and ASF 

Last tested: Sep. 15, 2023 

 

New Project → GCC C ASF Board Project 

Device Family → UC3L → AT32UC3L0256 → User Board template - UC3 L0/L3U/L4U 

 

On ASF Wizard: Select project, then Add 

- GPIO - General-Purpose Input/Output (driver) 
- INTC - Interrupt Controller (driver) 
- PM - Power Manager (driver) 
- TC - Timer/Counter (driver) 
- USART - Universal Synchronous/Asynchronous Receiver/Transmitter (driver) 
- System Clock Control (service) 
- Newlib optimization selector (library) (speed)

and Apply 

 

In the project folder: 

1. Create new folder "freertos" inside src/ASF/thirdparty/ 
1. Create new folder "freertos-12.0.1" inside src/ASF/thirdparty/freertos/ 
1. Copy the Source folder from the "FreeRTOS" folder within the FreeRTOS distribution to src/ASF/thirdparty/freertos/ 
1. In the Source/portable/ folder, only keep GCC folder, MemMang folder and the text files 
1. In the GCC folder, only keep the AVR32_UC3 folder 
1. In MemMang, only keep heap_3 file 
1. Inside src/config/ paste a FreeRTOSConfig.h file gotten from an example project
 

From Solution Explorer: Show all -> Right Click, Include In Project the Source folder just added and the FreeRTOSConfig.h file 

### important step 

NOW File -> Save

All BECAUSE THE NEXT STEP IS HEAVY FOR MICROCHIP STUDIO, IT MIGHT CRASH IN THE PROCESS! 

In Project Properties: Toolchain -> AVR32/GNU C Compiler -> Directories -> Include paths for the freertos-12.0.1/Source/include folder and the freertos-12.0.1/Source/portable/GCC/AVR32_UC3 folder 

## Last edits

Apply some changes to the code:

- line 73 in Source/portable/GCC/AVR32_UC3/port.c to #include "nlao_cpu.h" 
- line 74 in Source/portable/GCC/AV32_UC3/port.c to #include "nlao_usart.h" 
- line 68 in src/config/FreeRTOSConfig.h removing the cast (#define configMAX_PRIORITIES     ( 8 )) 
- flag at line 91 in src/config/FreeRTOSConfig.h to 1 (#define INCLUDE_xTaskGetCurrentTaskHandle 1) 
- Comment the whole "Constant data area" at the end of the Source/portable/GCC/AVR32_UC3/exception.S file (it is already defined in the int.c file) 
- change both instances of INT0 at lines 443 and 460 of Source/portable/GCC/AV32_UC3/port.c to AVR32_INTC_INT0 
- Define FOSC0 in the config/conf_board.h file and set it to the desired clock frequency 
- Remove ASF/avr32/drivers/intc/Exception.S file from the project or delete it 
