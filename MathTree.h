#pragma once

#include <string>
#include <memory>

#include "Node.h"

class MathTree {
    public:
        MathTree(const std::string& poland);

        std::string toString() const;
        std::string toTreeString() const;
        double eval() const;

    private:
        std::unique_ptr<Node> root;
};
