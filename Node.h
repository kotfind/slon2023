#pragma once

#include <map>
#include <functional>
#include <string>
#include <memory>

class Node {
    public:
        Node(char oper, Node* lhs, Node* rhs);
        Node(const std::string& func, Node* lhs);
        Node(double num);

        bool isOper() const;
        bool isFunc() const;
        bool isNum() const;

        char getOper() const;
        std::string getFunc() const;
        double getNum() const;

        Node* getLhsNode() const;
        Node* getRhsNode() const;

        static bool isFunction(const std::string& s);
        static bool isOperator(char c);

    private:
        enum class Type {
            OPER,
            FUNC,
            NUM,
        };

        Type type;

        char oper;          // for type == OPER only
        std::string func;   // for type == FUNC only
        double num;         // for type == NUM only

        std::unique_ptr<Node> lhsNode;  // for type == OPER or FUNC
        std::unique_ptr<Node> rhsNode;  // for type == FUNC

        static const std::map<char, std::function<double(double, double)>> operators;
        static const std::map<std::string, std::function<double(double)>> functions;
};
