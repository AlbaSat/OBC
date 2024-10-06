# Building libcsp for STM32 F411RE NUCLEO Board

## Prerequisites

1. Use Ubuntu or WSL (Windows Subsystem for Linux). This process doesn't work directly on Windows.

2. Set up the ARM GNU toolchain (compilers, linkers, debuggers) on Linux:
   Follow the guide at [Install Arm GNU Toolchain on Ubuntu](https://lindevs.com/install-arm-gnu-toolchain-on-ubuntu)

## Build Process

1. Navigate to the libcsp directory in your workspace:
   ```
   cd <your_workspace>/OBC/Libraries/libcsp
   ```

2. Configure WAF (replace paths with your actual directories):
   ```
   ./waf configure --toolchain=arm-none-eabi- --with-os=freertos --enable-rtable --prefix=/mnt/c/Users/Alessandro/STM32CubeIDE/workspace_1.13.2/OBC/Libraries --includes=/mnt/c/Users/Alessandro/STM32CubeIDE/workspace_1.13.2/OBC/Middlewares/Third_Party/FreeRTOS-Kernel/include,/mnt/c/Users/Alessandro/STM32CubeIDE/workspace_1.13.2/OBC/Core/Inc,/mnt/c/Users/Alessandro/STM32CubeIDE/workspace_1.13.2/OBC/Middlewares/Third_Party/FreeRTOS-Kernel/portable/GCC/ARM_CM4F -v CFLAGS="-mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -g"
   ```

3. Build and install:
   ```
   ./waf build install
   ```

## STM32CubeIDE Configuration

4. Configure linker flags:
   - Go to: Project -> Properties -> C/C++ General -> Tool Settings -> MCU GCC Linker -> Miscellaneous
   - Add to "Other flags": `-Wl,--whole-archive -lcsp -Wl,--no-whole-archive`

5. Set library search path:
   - Go to: Project -> Properties -> C/C++ General -> Tool Settings -> MCU GCC Linker -> Libraries
   - Add to "Libraries search path (-L)": `${workspace_loc:/OBC/Libraries/libcsp/build}`

6. Build the project. Your `libcsp.a` should now be correctly linked.