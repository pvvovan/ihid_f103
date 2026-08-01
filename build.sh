#!/usr/bin/env bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &> /dev/null && pwd)
cd ${SCRIPT_DIR}
cmake -S . --preset Debug
cmake --build --preset Debug
