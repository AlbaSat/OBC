#!/bin/sh

set -e

BUILDDIR="build"

if [ "$1" = "clean" ]; then
    rm -rf ./"$BUILDDIR"
fi

cmake --toolchain ./cmake/arm-gcc-toolchain.cmake -B "$BUILDDIR" && cmake --build "$BUILDDIR"
