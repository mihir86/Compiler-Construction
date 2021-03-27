#pragma once
#include <bits/stdc++.h>
using namespace std;

#define LPAREN 110
#define RPAREN 111
#define LBRACE 112
#define RBRACE 113
#define SEMICOL 114
#define COMMA 115
#define OP_ADD 120
#define OP_MUL 121
#define LESS 122
#define NOT 123
#define ASSIGN 124
#define IDENTIFIER 130
#define INTEGER_LITERAL 131
#define END 132

//Scanner class that can be initialised with a .c+++ file
//has only one public constructor, Scanner(string programFile)
//has one public member function, tuple<int, string, int> getToken() which returns a token
class Scanner {
    //current program line number
    int line;
    //is bufferChar loaded?
    bool bufferCharLoaded;
    //the buffer character
    char bufferChar;
    //input stream for program
    ifstream program;
    //table for keyword lookup
    vector<pair<string, int>> v;
    //peek the next character without consuming it
    char peekChar();
    //peek the next character and consume it
    char getChar();
    //skip a line in program file, used to handle comments
    void skipLine();
    //used to identify seperator characters
    bool isSeparator(char c);
    //the DFA representing the lexer
    //0 is the initial state
    //1 is the state for integer literals
    //2 is the state for identifiers and keywords
    //once a identifier/keyword is generated, it is matched against the keyword table
    //a string error is thrown in case the token generated is invalid or a bad symbol occurs
    int DFA(int state, string &token);
    public:
    //constructor for Scanner
    Scanner(string programFile);
    //used to get the next token
    tuple<int, string, int> getToken();
};