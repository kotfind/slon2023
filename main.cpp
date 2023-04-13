#include "MathTree.h"

#include <iostream>

int main() {
    std::string s;
    std::getline(std::cin, s);

    MathTree tree(s);
    tree.printAsTree(std::cout);
    std::cout << tree << " = " << tree.eval() << '\n';
}
