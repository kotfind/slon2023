#include "MathExpr.h"

#include "ParseError.h"

#include <sstream>
#include <stack>

MathExpr::MathExpr(const std::string& poland) {
    std::stringstream ss(poland);

    std::stack<std::unique_ptr<Node>> st;

    std::string s;
    while (ss >> s) {
        if (s.size() == 1 && Node::isOperator(s[0])) {
            // Operator
            if (st.size() < 2) throw ParseError();

            auto y = std::move(st.top());
            st.pop();
            auto x = std::move(st.top());
            st.pop();

            st.push(std::make_unique<Node>(s[0], std::move(x), std::move(y)));
        } else if (Node::isFunction(s)) {
            // Function
            if (st.size() < 1) throw ParseError();

            auto x = std::move(st.top());
            st.pop();

            st.push(std::make_unique<Node>(s, std::move(x)));
        } else {
            // Number
            try {
                st.push(std::make_unique<Node>(std::stod(s)));
            } catch(const std::invalid_argument&) {
                throw ParseError();
            }
        }
    }

    if (st.size() != 1) throw ParseError();

    root = std::move(st.top());
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
