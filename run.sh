#!/bin/bash
echo "Compiling Program!!!"
echo "#####################################"
make
echo ""

echo "Running Program!!!"
echo "#####################################"
./main program.c++++ > tree.txt
echo ""

cat tree.txt
echo ""