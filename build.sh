#!/bin/bash

set -e

cd src || exit 1
gfortran -c constants.f90 base_eos.f90 directeos.f90 variants.f90
cp constants.mod ../wrappers/constants.mod
cp base_eos.mod ../wrappers/base_eos.mod
cp directeos.mod ../wrappers/directeos.mod
cp variants.mod ../wrappers/variants.mod
python -m fortwrap -g -i ../FortWrapOptions.txt
cd ../wrappers || exit 2
gfortran -c FortranISOWrappers.f90
g++-12 -c BaseEos.cpp NotIdGas.cpp VariantEoS.cpp Variant1.cpp Variant2.cpp
cd ..
g++-12 -c main.cpp
g++-12 -o main main.o wrappers/*.o src/*.o /opt/homebrew/lib/gcc/12/libgfortran.dylib

echo "Finished building and wrapping. Executable is : ./main"