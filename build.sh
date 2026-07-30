#!/usr/bin/env bash

cmake -S . -B linbuild -D CMAKE_TOOLCHAIN_FILE=cmake/gcc-arm-none-eabi.cmake
cmake --build linbuild
