#include "MathExpr.h"

#include <iostream>

int main() {
    std::string s;
    std::getline(std::cin, s);

    MathExpr expr(s);
    expr.printAsTree(std::cout);
    std::cout << expr << " = " << expr.eval() << '\n';
}
