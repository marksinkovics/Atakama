#!/bin/bash

cmake -S . -B build/ninja -DCMAKE_BUILD_TYPE=Debug -G Ninja
cmake --build build/ninja