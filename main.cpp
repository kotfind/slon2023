#include "AhoCorasic.h"

#include <iostream>
#include <vector>

int main() {
    AhoCorasic ac;

    std::string text;
    std::getline(std::cin, text);

    std::vector<std::string> words;
    std::string buf;
    while (std::cin >> buf) {
        words.push_back(buf);
        ac.addString(buf);
    }
    ac.prepare();

    auto ans = ac.process(text);

    std::cout << "\nAnswer:\n";
    std::cout << text << '\n';
    for (int pos = 0; pos < ans.size(); ++pos) {
        for (auto id : ans[pos]) {
            for (int i = 0; i < pos; ++i) {
                std::cout << ' ';
            }
            std::cout << words[id] << '\n';
        }
    }
}
