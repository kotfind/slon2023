#include "MathExpr.h"

#include <iostream>

int main() {
    std::cout << "Polish:\n";
    std::string s;
    std::getline(std::cin, s);

    MathExpr expr(s);
    std::cout << "\nTree:\n";
    expr.printAsTree(std::cout);

    std::cout << "\nAnswer:\n";
    std::cout << expr << " = " << expr.eval() << '\n';
}
