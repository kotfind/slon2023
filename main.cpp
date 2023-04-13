#include "MathTree.h"

#include <iostream>

int main() {
    std::string s;
    std::getline(std::cin, s);
    MathTree tree(s);
    std::cout << tree.toTreeString();
    std::cout << tree.toString() << " = " << tree.eval() << '\n';
}
