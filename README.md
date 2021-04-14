# C++++
G11 - C++++
2018A7PS0215H	Mihir Bansal
2018A7PS0164H	Bhavyesh Desai
2018A7PS0286H	Vaishnavee Nautiyal

A simple programming language written in C++.

A standard folder structure is being used, with the .hpp files being stored in the directory ./include/ and the .cpp files stored in the directory ./src/

## Language specifications:

The BNF of the language can be found in ./language/BNF.txt

./actionTable.txt contains information about the BNF of the language in a simple format for the parser to read.

The LALR(1) parse table can be found in ./language/parseTable.csv, generated by the help of a tool.

./parseTable.txt contains the above parse table in a simple format for the parser to read.

## Running the program

To obtain only the tree traversal, the following commands can be run:

$ ./run.sh

To obtain the tree traversal (saved in tree.txt) of the program in program.c++++ along with generating the tree visually:

$ ./treeRun.sh

Note: The terminal may not be able to display the tree properly. It is reccomended to view the tree in a capable editor such as Visual Studio Code.

For both of these scripts, ./tree.txt stores the inorder tree traversal of the parse tree generated.
The symbols '[' and ']' have been used to make distinguish parents and children in the tree.

In case the program has some error, the parser enters Panic Recovery Mode and continues it's operation after reaching some valid state.

# Test cases

Some test cases along with their outputs have been saved in the directory ./test_cases/