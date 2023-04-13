#include "Node.h"

#include <cassert>

Node::Node(char oper, std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs)
  : type(Type::OPER),
    oper(oper),
    lhsNode(std::move(lhs)),
    rhsNode(std::move(rhs))
{}

Node::Node(const std::string& func, std::unique_ptr<Node> lhs)
  : type(Type::FUNC),
    func(func),
    lhsNode(std::move(lhs))
{}

Node::Node(double num)
  : type(Type::NUM),
    num(num)
{}

bool Node::isOper() const { return type == Type::OPER; }
bool Node::isFunc() const { return type == Type::FUNC; }
bool Node::isNum() const { return type == Type::NUM; }

char Node::getOper() const {
    assert(isOper());
    return oper;
}

std::string Node::getFunc() const {
    assert(isFunc());
    return func;
}

double Node::getNum() const {
    assert(isNum());
    return num;
}

Node* Node::getLhsNode() const {
    assert(isFunc() || isOper());
    return lhsNode.get();
}

Node* Node::getRhsNode() const {
    assert(isOper());
    return rhsNode.get();
}

bool Node::isFunction(const std::string& s) {
    return functions.count(s);
}

bool Node::isOperator(char c) {
    return operators.count(c);
}

void Node::printAsTree(std::ostream& out, int depth) {
    std::string indentString;
    for (int i = 0; i < depth - 1; ++i) {
        indentString += "|   ";
    }
    if (depth) {
        indentString += "|--- ";
    }

    if (isFunc()) {
        // Function
        out << indentString << getFunc() << '\n';
        getLhsNode()->printAsTree(out, depth + 1);
    } else if (isOper()) {
        // Operator
        out << indentString << "(" << getOper() << ")" << '\n';
        getLhsNode()->printAsTree(out, depth + 1);
        getRhsNode()->printAsTree(out, depth + 1);
    } else {
        // Number
        out << indentString << getNum() << '\n';
    }
}

double Node::eval() const {
    if (isFunc()) {
        // Function
        return functions.at(getFunc())(getLhsNode()->eval());
    } else if (isOper()) {
        // Operator
        return operators.at(getOper())(
            getLhsNode()->eval(),
            getRhsNode()->eval()
        );
    } else {
        // Number
        return getNum();
    }
}

std::ostream& operator<<(std::ostream& out, const Node& node) {
    if (node.isFunc()) {
        // Function
        out << node.getFunc()
            << "("
            << *node.getLhsNode()
            << ")";

    } else if (node.isOper()) {
        // Operator
        // Lhs
        if (node.getLhsNode()->isOper()) {
            out << "(";
        }
        out << *node.getLhsNode();
        if (node.getLhsNode()->isOper()) {
            out << ")";
        }

        // Oper
        out << " " << node.getOper() << " ";

        // Rhs
        if (node.getRhsNode()->isOper()) {
            out << "(";
        }
        out << *node.getRhsNode();
        if (node.getRhsNode()->isOper()) {
            out << ")";
        }

    } else {
        // Number
        out << node.getNum();
    }

    return out;
}
