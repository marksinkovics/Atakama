#!/bin/bash

cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -G Ninja
cmake --build build