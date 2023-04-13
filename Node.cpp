#include "Node.h"

#include <cassert>

Node::Node(char oper, Node* lhs, Node* rhs)
  : type(Type::OPER),
    oper(oper),
    lhsNode(lhs),
    rhsNode(rhs)
{}

Node::Node(const std::string& func, Node* lhs)
  : type(Type::FUNC),
    func(func),
    lhsNode(lhs)
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
