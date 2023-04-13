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

    root.reset(st.top());
}

static std::string nodeToString(Node* node) {
    if (node->isFunc()) {
        // Function
        return node->getFunc() +
            "(" +
            nodeToString(node->getLhsNode()) +
            ")";
    } else if (node->isOper()) {
        // Operator
        std::stringstream ss;

        // Lhs
        if (node->getLhsNode()->isOper()) {
            ss << "(";
        }
        ss << nodeToString(node->getLhsNode());
        if (node->getLhsNode()->isOper()) {
            ss << ")";
        }

        // Oper
        ss << " " << node->getOper() << " ";

        // Rhs
        if (node->getRhsNode()->isOper()) {
            ss << "(";
        }
        ss << nodeToString(node->getRhsNode());
        if (node->getRhsNode()->isOper()) {
            ss << ")";
        }

        return ss.str();
    } else {
        // Number
        return std::to_string(node->getNum());
    }
}

std::string MathTree::toString() const {
    return nodeToString(root.get());
}

static void nodeToTreeString(std::string& ans, Node* node, int depth = 0) {
    std::string indentString;
    for (int i = 0; i < depth - 1; ++i) {
        indentString += "|   ";
    }
    if (depth) {
        indentString += "|--- ";
    }

    if (node->isFunc()) {
        // Function
        ans += indentString + node->getFunc() + '\n';
        nodeToTreeString(ans, node->getLhsNode(), depth + 1);
    } else if (node->isOper()) {
        // Operator
        ans += indentString + "(" + node->getOper() + ")" + '\n';
        nodeToTreeString(ans, node->getLhsNode(), depth + 1);
        nodeToTreeString(ans, node->getRhsNode(), depth + 1);
    } else {
        // Number
        ans += indentString + std::to_string(node->getNum()) + '\n';
    }
}

std::string MathTree::toTreeString() const {   
    std::string ans;
    nodeToTreeString(ans, root.get());
    return ans;
}

double MathTree::eval() const {

}
