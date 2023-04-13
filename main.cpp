#include "MathExpr.h"
#include "ParseError.h"

#include <iostream>

int main() {
    std::cout << "Polish:\n";
    std::string s;
    std::getline(std::cin, s);

    try {
        MathExpr expr(s);
        std::cout << "\nTree:\n";
        expr.printAsTree(std::cout);

        std::cout << "\nAnswer:\n";
        std::cout << expr << " = " << expr.eval() << '\n';
    } catch(const ParseError& err) {
        std::cerr << "ParseError: " << err.what() << '\n';
    }
}
