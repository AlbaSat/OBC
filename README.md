# AlbaSat-OBC

## Work in progress

Temporary repo for OBC software development

## Branches

The architecture chosen for the cubesat is AVR32.
However, development for now will proceed for a stm32 architecture.
Considering this choice, the repo has been devided into two branches: `microchi-studio` and `stm32`.

The branch `microchip-studio` will be kept for future development and simulation of the AVR32 architecture.
The branch `stm32` is currently used to develop the draft of the project with STM32CubeIDE.

## Start working on the project

If you are new to the project you can start developing for stm32 cloning the repo and switching to the correct branch.

If you don't have one already create a workspace for STM32CudeIDE.
From inside the workspace clone the repo ad switch to the right branch running the following:

```bash
git clone https://github.com/AlbaSat/OBC.git
git switch stm32
git submodule init
git submodule update
```
After cloining the repo, you can open the IDE and import the project from:
File -> import -> General -> "Import an Existing ... (.ioc)"
Select OBC.ioc from the OBC folder inside the workspace and you should be good to go.
