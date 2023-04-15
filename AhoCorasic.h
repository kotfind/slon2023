#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>

class AhoCorasic {
    struct Node {
        std::unordered_map<char, std::unique_ptr<Node>> to;
        Node* sln = nullptr;    // suffix link
        Node* fln = nullptr;    // fast link
        std::vector<int> words; // terminal node words
    };

    public:
        AhoCorasic();

        void addString(const std::string&);

        // Should be called after added all strings
        void prepare();

        // for each position returns
        // numbers of string starting/ending here
        std::vector<std::vector<int>> process(const std::string& text, bool endPos = false);

    private:
        Node* go(Node* v, char c);

        // Returns words that end in cur
        std::vector<int> getWordIds(Node* cur);

        std::unique_ptr<Node> root; // root of trie
        std::vector<int> wordLengths;
};
