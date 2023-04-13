#include "MathExpr.h"

#include "ParseError.h"

#include <sstream>
#include <stack>

MathExpr::MathExpr(const std::string& poland) {
    std::stringstream ss(poland);

    std::stack<Node*> st;

    std::string s;
    while (ss >> s) {
        if (s.size() == 1 && Node::isOperator(s[0])) {
            // Operator
            if (st.size() < 2) throw ParseError();

            auto* y = st.top();
            st.pop();
            auto* x = st.top();
            st.pop();

            st.push(new Node(s[0], x, y));
        } else if (Node::isFunction(s)) {
            // Function
            if (st.size() < 1) throw ParseError();

            auto* x = st.top();
            st.pop();

            st.push(new Node(s, x));
        } else {
            // Number
            try {
                st.push(new Node(std::stod(s)));
            } catch(const std::invalid_argument&) {
                throw ParseError();
            }
        }
    }

    if (st.size() != 1) throw ParseError();

    root.reset(st.top());
}

void MathExpr::printAsTree(std::ostream& out) const {   
    return root->printAsTree(out);
}

double MathExpr::eval() const {
    return root->eval();
}

std::ostream& operator<<(std::ostream& out, const MathExpr& expr) {
    out << *expr.root;
    return out;
}
