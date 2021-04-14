#pragma once
#include <bits/stdc++.h>
#include <lexer.hpp>
#include <parseTreeNode.hpp>
using namespace std;

//Parser class that can be initialised with a file
class Parser {
    //scanner object to get stream of tokens
    Scanner scanner;
    //parse table stored in the memory for quick access
    map<pair<int, int>, string> parseTable;
    //information about the BNF moves
    //is stored in the reduceTable
    //gives information about the non terminal on the LHS
    //along with the number of items on the RHS
    map<int, pair<int, int>> reduceTable;
    //stack used in the parsing process
    //the first argument is the token number of the token
    //second argument is the state number
    //third argument is the parse tree node associated with the token
    stack<tuple<int, int, parseTreeNode*>> s;
    //errorStack is used in the error handling part of the parser
    //it is used to push input tokens if they're temporarily not needed
    stack<tuple<int, string, int>> errorStack;
    //get token works in sync with scanner and errorStack to return the next token
    tuple<int, string, int> getToken(int &flag);
    //getString is used to get the relevant string to be stored in the parse tree nodes
    map<int, string> getString;
    public:
    //constructor to initialise the file
    Parser(char* fileName);
    //print all tokens, used to debug the class
    void printTokens();
    //used to perform parsing on the given input .c++++ file
    void LALR1();
};