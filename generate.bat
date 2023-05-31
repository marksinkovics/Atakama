@echo off

echo "Generate Visual Studio project"
cmake -S . -B build/visualstudio -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 17 2022"