# C++++
G11 - C++++
2018A7PS0215H	Mihir Bansal
2018A7PS0164H	Bhavyesh Desai	
2018A7PS0286H	Vaishnavee Nautiyal

A simple programming language written in C++.

## Language specifications:

The BNF of the language can be found in ./language/BNF.txt

./actionTable.txt contains information about the BNF of the language in a simple format for the parser to read.

The LR(1) parse table can be found in ./language/parseTable.csv, generated by the help of a tool.

./parseTable.txt contains the above parse table in a simple format for the parser to read.

## Running the program

To obtain only the tree traversal, the following commands can be run:

$ make
$ ./main <program-name>

To obtain the tree traversal (saved in tree.txt) of the program in program.c++++ along with generating the tree visually:

$ ./run.sh
