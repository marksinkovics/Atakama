#!/bin/bash


echo "Generate Ninja"
cmake -S . -B build/ninja -DCMAKE_BUILD_TYPE=Debug -G Ninja

echo "Generate Xcode"
cmake -S . -B build/xcode -G Xcode
