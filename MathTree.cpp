#include "MathTree.h"

#include <sstream>
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

void MathTree::printAsTree(std::ostream& out) const {   
    return root->printAsTree(out);
}

double MathTree::eval() const {
    return root->eval();
}

std::ostream& operator<<(std::ostream& out, const MathTree& tree) {
    out << *tree.root;
    return out;
}
