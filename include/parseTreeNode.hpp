#pragma once
#include <bits/stdc++.h>
using namespace std;

class parseTreeNode {
    string token;
    vector<parseTreeNode*> children;
    public:
    parseTreeNode(string _token)
    : token(_token)
    {}
    void addNode(parseTreeNode *node) {
        children.push_back(node);
    }
    void correctOrder() {
        reverse(children.begin(), children.end());
    }
    void printTree() {
        cout << "( " << token;
        for(auto &k: children)
            k->printTree();
        cout << " )";
    }
};