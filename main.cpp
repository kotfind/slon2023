#include "Matcher.h"

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::string pattern;
    std::cout << "Enter pattern: " << std::flush;
    std::cin >> pattern;

    std::string text;
    std::cout << "Enter text: " << std::flush;
    std::cin >> text;

    Matcher matcher;
    matcher.setText(text);
    matcher.setPattern(pattern);
    matcher.process();

    std::cout << '\n';
    if (!matcher.hasMatch()) {
        std::cout << "No match\n";
        return 0;
    }

    std::cout << "Match!\n";

    // Match string
    std::string matchString(text.size(), ' ');
    for (auto [from, to] : matcher.getMatchSegments()) {
        std::fill(
            matchString.begin() + from,
            matchString.begin() + to + 1,
            '^'
        );
    }

    std::cout << text << '\n';
    std::cout << matchString << '\n';
}
