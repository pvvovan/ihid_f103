#!/usr/bin/env bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &> /dev/null && pwd)
cd ${SCRIPT_DIR}
cmake -S . --preset=Debug -D OS_ARCH_VARIANT=cortex_m3
cmake --build --preset=Debug
