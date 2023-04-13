#pragma once

#include <string>

class Node;

class MathTree {
    public:
        MathTree(const std::string& poland);

        std::string toString() const;
        std::string toTreeString() const;
        double eval() const;

    private:
        Node* root = nullptr;
};
