#!/bin/bash
echo "Compiling Program!!!"
echo "#####################################"
make
echo ""

echo "Running Program!!!"
echo "#####################################"
./main program.c++++ > tree.txt
echo ""

echo "Generating Tree!!!"
echo "#####################################"
python3 generateTree.py
echo ""

