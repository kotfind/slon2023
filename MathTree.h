#pragma once

#include <string>
#include <ostream>
#include <memory>

#include "Node.h"

class MathTree;

std::ostream& operator<<(std::ostream& out, const MathTree& tree);

class MathTree {
    public:
        MathTree(const std::string& poland);

        void printAsTree(std::ostream&) const;
        double eval() const;

    private:
        std::unique_ptr<Node> root;

    friend std::ostream& operator<<(std::ostream& out, const MathTree& tree);
};
