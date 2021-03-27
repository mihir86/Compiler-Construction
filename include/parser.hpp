#pragma once
#include <bits/stdc++.h>
#include <lexer.hpp>
using namespace std;

class Parser {
    Scanner scanner;
    map<pair<int, int>, string> parseTable;
    map<int, pair<int, int>> reduceTable;
    stack<pair<int, int>> s;
    stack<tuple<int, string, int>> errorStack;
    tuple<int, string, int> getToken();
    public:
    Parser(char* fileName);
    void printTokens();
    void LR1();
};