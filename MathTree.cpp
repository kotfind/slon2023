#include "MathTree.h"

#include "Node.h"

#include <sstream>
#include <iostream>
#include <stack>

MathTree::MathTree(const std::string& poland) {
    std::stringstream ss(poland);

    std::stack<Node*> st;

    std::string s;
    while (ss >> s) {
        if (s.size() == 1 && Node::isOperator(s[0])) {
            // Operator
            auto* y = st.top();
            st.pop();
            auto* x = st.top();
            st.pop();

            st.push(new Node(s[0], x, y));
        } else if (Node::isFunction(s)) {
            // Function
            auto* x = st.top();
            st.pop();

            st.push(new Node(s, x));
        } else {
            // Number
            st.push(new Node(std::stod(s)));
        }
    }

    root = st.top();
}

std::string MathTree::toString() const {

}

static void nodeToString(std::string& ans, Node* node, int depth = 0) {
    std::string indentString;
    for (int i = 0; i < 4 * depth; ++i) {
        indentString += ' ';
    }

    if (node->isFunc()) {
        // Function
        ans += indentString + node->getFunc() + '\n';
        nodeToString(ans, node->getLhsNode(), depth + 1);
    } else if (node->isOper()) {
        // Operator
        ans += indentString + node->getOper() + '\n';
        nodeToString(ans, node->getLhsNode(), depth + 1);
        nodeToString(ans, node->getRhsNode(), depth + 1);
    } else {
        // Number
        ans += indentString + std::to_string(node->getNum()) + '\n';
    }
}

std::string MathTree::toTreeString() const {   
    std::string ans;
    nodeToString(ans, root);
    return ans;
}

double MathTree::eval() const {

}
