#pragma once
#include <bits/stdc++.h>
using namespace std;

class parseTreeNode {
    string token;
    vector<parseTreeNode*> children;
    public:
    parseTreeNode(string _token);
    void addNode(parseTreeNode *node);
    void correctOrder();
    void printTree();
};