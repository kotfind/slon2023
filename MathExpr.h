#pragma once

#include <string>
#include <ostream>
#include <memory>

#include "Node.h"

class MathExpr;

std::ostream& operator<<(std::ostream&, const MathExpr&);

class MathExpr {
    public:
        MathExpr(const std::string& poland);

        void printAsTree(std::ostream&) const;
        double eval() const;

    private:
        std::unique_ptr<Node> root;

    friend std::ostream& operator<<(std::ostream&, const MathExpr&);
};
