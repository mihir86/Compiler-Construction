#pragma once
#include <bits/stdc++.h>
#include <lexer.hpp>
#include <parseTreeNode.hpp>
using namespace std;

class Parser {
    Scanner scanner;
    map<pair<int, int>, string> parseTable;
    map<int, pair<int, int>> reduceTable;
    stack<tuple<int, int, parseTreeNode*>> s;
    stack<tuple<int, string, int>> errorStack;
    tuple<int, string, int> getToken();
    map<int, string> getString;
    public:
    Parser(char* fileName);
    void printTokens();
    void LR1();
};