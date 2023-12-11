# OBC Project

This project is a firmware for STM32F411RE microcontroller. It uses FreeRTOS as the real-time operating system and
FreeRTOS+FAT for file system support.

## Directory Structure

- Core: Contains the main application source code and headers.
- Drivers: Contains CMSIS and STM32F4xx_HAL_Driver.
- Middlewares: Contains third-party libraries such as FreeRTOS-Kernel and Lab-Project-FreeRTOS-FAT.
- CMakeLists.txt: CMake configuration file for the project.

## Building the Project

### Dependencies

- CMake 3.11 or higher
- GNU Arm Embedded Toolchain
- ST-Link utility from [here](https://github.com/stlink-org/stlink).

#### Arch Linux

On Arch Linux installing `arm-none-eabi-gcc` doesn't install the whole toolcahin and leads to compilation issues.
You should also install `arm-none-eabi-newlib`

#### MacOs

On macOs installing `arm-none-eabi-gcc` doesn't install the whole toolchain and leads to compilation issues.
You should instead install:

```shell
brew install --cask gcc-arm-embedded
```

### Get the code

Submodules have been added: use the following snippet.

```shell
git clone --recurse-submodules https://github.com/AlbaSat/OBC.git -b stm32
```

### Build

This project uses CMake as its build system. To build the project, navigate to the project root directory and run the
following commands:

```shell
mkdir -p build && cd build
cmake ..
make
```

This will generate the executable OBC.elf in the build directory.
Please note that the `cmake ..` might take a while to complete the first time.

### Running the Project

To run the project, you will need to flash the OBC.elf file to the STM32F411RE microcontroller using either OpenOCD or
ST-Link. The following commands can be used to flash the firmware using ST-Link

- Connect the STM32F411RE microcontroller to your computer and run the following command:

```shell
sudo st-flash write OBC.elf 0x8000000
```

### Running the project with QEMU

To run the project with QEMU, you will need to install QEMU and the Olimex STM32-H405 board emulation files. The
following commands can be used to run the project with QEMU:

- `qemu-system-arm`
- `qemu-system`

```shell
qemu-system-arm -M olimex-stm32-h405  -kernel OBC.elf -smp 1 -display none
```

### Running the proejct using qemu-system-gnuarmeclipse

Dependencies:

- Node.js
- NPM

From the root of the project run the following commands:

```shell
# Install XPM
npm install --global xpm@latest

# Check the installation
xpm --version

# Install Qemu-arm and Qemu-system-gnuarmeclipse
xpm init
xpm install @xpack-dev-tools/qemu-arm@latest 

# Check if the installation was successful, and qemu-system-gnuarmeclipse is installed
xpacks/.bin/qemu-system-gnuarmeclipse --version

# Run the project, please read the note below for more details about the FPU and CPU
xpacks/.bin/qemu-system-gnuarmeclipse -cpu cortex-m3 -machine STM32F4-Discovery -gdb tcp::3333 -kernel build/OBC.elf
```

To debug using gdb, run the following commands from another terminal:

```shell
gdb -q build/OBC.elf  -ex "target remote:3333"
```


Note: qemu-system-gnuarmeclipse doesn't support the FPU, so we need to comment the following lines in the system_stm32f4xx.c file:
```c
  #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */
  #endif
 ```
on top of that we need to change the compiler flags in the CMakeLists.txt file to:
```cmake
#from this
set(COMMON_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -specs=nano.specs -specs=nosys.specs")
# to this
set(COMMON_FLAGS "-mcpu=cortex-m4 -mthumb -specs=nano.specs -specs=nosys.specs")
```
However the port of FreeRTOS (GCC_ARM_CM4F) that we are using cannot compile without the FPU, so we need to change it to GCC_ARM_CM3 for qemu-system-gnuarmeclipse to work.

### Contributing

TODO

### License

TODO
