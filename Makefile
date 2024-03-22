project-name ::= OBC

toolchain-prefix ::= arm-none-eabi-
cc ::= $(toolchain-prefix)gcc
size ::= $(toolchain-prefix)size
objdump ::= $(toolchain-prefix)objdump

# Change to 'release' to make a release build and remove debug info
target ::= debug
builddir ::= $(target)
bin ::= $(builddir)/$(project-name).elf

cflags ::= -mcpu=cortex-m4 -std=gnu11 \
		  -DUSE_HAL_DRIVER -DSTM32F411xE \
		  --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb \
		  -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP
#-fcyclomatic-complexity 

asmflags ::= -mcpu=cortex-m4 \
			-x assembler-with-cpp -MMD -MP \
			--specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb 

ldflags ::= -mcpu=cortex-m4 \
		   -T"./STM32F411RETX_FLASH.ld" --specs=nosys.specs \
		   -Wl,-Map="./$(builddir)/$(project-name).map" \
		   -Wl,--gc-sections -static --specs=nano.specs \
		   -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb \
		   -Wl,--start-group -lc -lm -Wl,--end-group

srcs ::= ./Middlewares/Third_Party/Lab-Project-FreeRTOS-FAT/portable/common/ff_ramdisk.c \
		 ./Middlewares/Third_Party/Lab-Project-FreeRTOS-FAT/ff_crc.c \
		 ./Middlewares/Third_Party/Lab-Project-FreeRTOS-FAT/ff_dir.c \
		 ./Middlewares/Third_Party/Lab-Project-FreeRTOS-FAT/ff_error.c \
		 ./Middlewares/Third_Party/Lab-Project-FreeRTOS-FAT/ff_fat.c \
		 ./Middlewares/Third_Party/Lab-Project-FreeRTOS-FAT/ff_file.c \
		 ./Middlewares/Third_Party/Lab-Project-FreeRTOS-FAT/ff_format.c \
		 ./Middlewares/Third_Party/Lab-Project-FreeRTOS-FAT/ff_ioman.c \
		 ./Middlewares/Third_Party/Lab-Project-FreeRTOS-FAT/ff_locking.c \
		 ./Middlewares/Third_Party/Lab-Project-FreeRTOS-FAT/ff_memory.c \
		 ./Middlewares/Third_Party/Lab-Project-FreeRTOS-FAT/ff_stdio.c \
		 ./Middlewares/Third_Party/Lab-Project-FreeRTOS-FAT/ff_string.c \
		 ./Middlewares/Third_Party/Lab-Project-FreeRTOS-FAT/ff_sys.c \
		 ./Middlewares/Third_Party/Lab-Project-FreeRTOS-FAT/ff_time.c \
		 ./Middlewares/Third_Party/FreeRTOS-Kernel/portable/MemMang/heap_4.c \
		 ./Middlewares/Third_Party/FreeRTOS-Kernel/portable/GCC/ARM_CM4F/port.c \
		 ./Middlewares/Third_Party/FreeRTOS-Kernel/croutine.c \
		 ./Middlewares/Third_Party/FreeRTOS-Kernel/event_groups.c \
		 ./Middlewares/Third_Party/FreeRTOS-Kernel/list.c \
		 ./Middlewares/Third_Party/FreeRTOS-Kernel/queue.c \
		 ./Middlewares/Third_Party/FreeRTOS-Kernel/stream_buffer.c \
		 ./Middlewares/Third_Party/FreeRTOS-Kernel/tasks.c \
		 ./Middlewares/Third_Party/FreeRTOS-Kernel/timers.c \
		 ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
		 ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
		 ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
		 ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c \
		 ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c \
		 ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c \
		 ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c \
		 ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c \
		 ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
		 ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c \
		 ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
		 ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
		 ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
		 ./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c \
		 ./Core/Src/freertos.c \
		 ./Core/Src/main.c \
		 ./Core/Src/stm32f4xx_hal_msp.c \
		 ./Core/Src/stm32f4xx_it.c \
		 ./Core/Src/syscalls.c \
		 ./Core/Src/sysmem.c \
		 ./Core/Src/system_stm32f4xx.c \
		 ./Core/Src/vTaskAle.c \

objs ::= $(srcs:%.c=./$(builddir)/%.o) 
deps ::= $(srcs:%.c=./$(builddir)/%.d)

incs ::= ./Core/Inc \
		 ./Drivers/STM32F4xx_HAL_Driver/Inc \
		 ./Drivers/STM32F4xx_HAL_Driver/Inc/Legacy \
		 ./Drivers/CMSIS/Device/ST/STM32F4xx/Include \
		 ./Drivers/CMSIS/Include \
		 ./Middlewares/Third_Party/FreeRTOS/Source/include \
		 ./Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS \
		 ./Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F \
		 ./Middlewares/Third_Party/FreeRTOS-Kernel/include \
		 ./Middlewares/Third_Party/FreeRTOS-Kernel/portable \
		 ./Middlewares/Third_Party/Lab-Project-FreeRTOS-FAT/include \
		 ./Middlewares/Third_Party/FreeRTOS-Kernel/portable/GCC/ARM_CM4F \
		 ./Middlewares/Third_Party/Lab-Project-FreeRTOS-FAT/portable/STM32F4xx \
		 ./Middlewares/Third_Party/Lab-Project-FreeRTOS-FAT/portable/common \
		 ./Middlewares/Third_Party/FreeRTOS-Kernel/portable/MemMang \
		 ./Middlewares/Third_Party/FreeRTOS-Kernel \
		 ./Middlewares/Third_Party/Lab-Project-FreeRTOS-FAT 

cflags += $(incs:%=-I%)

ifeq ($(target),debug)
	cflags += -DDEBUG -g3 -ggdb
	asmflags += -DDEBUG -g3 -ggdb
endif

.PHONY: help clean

all: $(bin)

help:
	@printf "Usage:\n"
	@printf "  -'make clean': clean all object files and binaries by removing the target directory\n"
	@printf "  -'make flash': flash target name to the board. Requires st-flash and super user privileges\n"
	@printf "  -'make': builds the project in the directory specified by the target\n"

$(bin): $(objs) $(builddir)/Core/Startup/startup_stm32f411retx.o
	$(cc) $(ldflags) $^ -o $@
	$(size) $@
	$(objdump) -h -S $@ > "./$(builddir)/$(project-name).list"

$(builddir)/%.o: %.c
	@mkdir -p '$(@D)'
	$(cc) $(cflags) -c $< -MF"$(@:%.o=%.d)" -MT"$@" -o $@

$(builddir)/Core/Startup/startup_stm32f411retx.o: ./Core/Startup/startup_stm32f411retx.s
	@mkdir -p '$(@D)'
	$(cc) $(asmflags) -c $< -MF"$(@:%.o=%.d)" -MT"$@" -o $@

clean:
	rm -rf $(builddir)

flash: $(bin)
	st-flash write $(bin) 0x8000000
