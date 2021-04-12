#include <parseTreeNode.hpp>
using namespace std;

parseTreeNode::parseTreeNode(string _token)
    : token(_token)
    {}
void parseTreeNode::addNode(parseTreeNode *node) {
    children.push_back(node);
}
void parseTreeNode::correctOrder() {
    reverse(children.begin(), children.end());
}
void parseTreeNode::printTree() {
    cout << "[ " << token << " ";
    for(auto &k: children) {
        k->printTree();
        cout << " ";
    }
    cout << "]";
}