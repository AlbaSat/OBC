### How to clone this repository

Submodules have been added: use the following snippet.

```shell
git clone https://github.com/AlbaSat/OBC.git -b stm32 --recurse-submodules
```

# OBC Project
This project is a firmware for STM32F411RE microcontroller. It uses FreeRTOS as the real-time operating system and FreeRTOS+FAT for file system support.

## Directory Structure
- Core: Contains the main application source code and headers.
- Drivers: Contains CMSIS and STM32F4xx_HAL_Driver.
- Middlewares: Contains third-party libraries such as FreeRTOS-Kernel and Lab-Project-FreeRTOS-FAT.
- CMakeLists.txt: CMake configuration file for the project.

## Building the Project

### Dependencies
- CMake 3.10 or higher
- GNU Arm Embedded Toolchain
- ST-Link utility from [here](https://github.com/stlink-org/stlink).

This project uses CMake as its build system. To build the project, navigate to the project root directory and run the following commands:
```shell
mkdir -p build
cd build
cmake ..
make
```
This will generate the executable OBC.elf in the build directory.
Please note that the `cmake ..` might take a while to complete the first time.

### Running the Project
To run the project, you will need to flash the OBC.elf file to the STM32F411RE microcontroller using either OpenOCD or ST-Link. The following commands can be used to flash the firmware using ST-Link
- Connect the STM32F411RE microcontroller to your computer and run the following command:

```shell
sudo st-flash write OBC.elf 0x8000000
```


### Contributing
TODO

### License
TODO