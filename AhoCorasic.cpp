#include "AhoCorasic.h"

#include <queue>

#define ALL(v) v.begin(), v.end()

AhoCorasic::AhoCorasic()
  : root(std::make_unique<Node>())
{}

void AhoCorasic::addString(const std::string& s) {
    Node* v = root.get();
    for (char c : s) {
        if (!v->to.count(c)) {
            v->to[c] = std::make_unique<Node>();
        }
        v = v->to[c].get();
    }
    v->words.push_back(wordLengths.size());
    wordLengths.push_back(s.size());
}

void AhoCorasic::prepare() {
    root->fln = root->sln = root.get();

    std::queue<Node*> q;
    for (const auto& [c, v] : root->to) {
        v->fln = v->sln = root.get();
        q.push(v.get());
    }

    while (!q.empty()) {
        Node* v = q.front();
        q.pop();

        for (const auto& [c, u] : v->to) {
            u->sln = go(v->sln, c);
            u->fln = u->sln->words.empty()
                ? u->sln->fln
                : u->sln;
            q.push(u.get());
        }
    }
}

AhoCorasic::Node* AhoCorasic::go(Node* v, char c) {
    while (v != root.get() && !v->to.count(c)) {
        v = v->sln;
    }
    return v->to.count(c)
        ? v->to[c].get()
        : root.get();
}

std::vector<int> AhoCorasic::getWordIds(Node* v) {
    std::vector<int> ans;
    while (v != root.get()) {
        ans.insert(ans.begin(), ALL(v->words));
        v = v->fln;
    }
    return ans;
}

std::vector<std::vector<int>> AhoCorasic::process(const std::string& text, bool endPos) {
    std::vector<std::vector<int>> ans(text.size());

    Node* cur = root.get();
    for (int i = 0; i < text.size(); ++i) {
        char c = text[i];
        cur = go(cur, c); // step

        auto wordIds = getWordIds(cur);
        for (auto id : wordIds) {
            int pos = endPos
                ? i // position of word's end
                : i - wordLengths[id] + 1; // position of word's start
            ans[pos].push_back(id);
        }
    }

    return ans;
}
