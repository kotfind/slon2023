#include "Matcher.h"

#include <iostream>
#include <vector>

int main() {
    std::string pattern;
    std::cout << "Enter pattern: ";
    std::cin >> pattern;

    std::string text;
    std::cout << "Enter text: ";
    std::cin >> text;

    Matcher matcher;
    matcher.setText(text);
    matcher.setPattern(pattern);
    matcher.process();
    std::cout << (matcher.hasMatch() ? "Match!" : "No match") << '\n';
}
