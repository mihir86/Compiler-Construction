#pragma once
#include <bits/stdc++.h>
using namespace std;

//parseTreeNode class used to represent a parse tree node
class parseTreeNode {
    //the token stored in the node
    string token;
    //list of children of the node in the parse tree
    vector<parseTreeNode*> children;
    public:
    //initialise the node with a string
    parseTreeNode(string _token);
    //add a node to the list of children
    void addNode(parseTreeNode *node);
    //perform corrective measures to ensure the order of children in the tree is correct
    void correctOrder();
    //print the parse tree in a bracketed format
    void printTree();
};