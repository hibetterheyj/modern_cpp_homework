#!/usr/bin/env bash
echo "Task 1: Build the ipb_arithmetic library"
rm -rf build
mkdir build
# -I dir include headers dir
c++ -I ./include/ -c src/subtract.cpp -o build/subtract.o
c++ -I ./include/ -c src/sum.cpp -o build/sum.o

# archive two objects and create library
ar rcs build/libipb_arithmetic.a build/sum.o build/subtract.o

echo "Task 2: Build the example program"
# -I <include_headers_folder>
# -L <include_libs_folder> -l<libname>
# -o <outfile>
c++ src/main.cpp -I ./include/ -L ./build/ -lipb_arithmetic -o ./results/yujie_example
echo "Finished!"