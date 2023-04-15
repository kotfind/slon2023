#include "Matcher.h"

#include "AhoCorasic.h"

#include <memory>
#include <algorithm>
#include <iostream>

#define ALL(v) v.begin(), v.end()

Matcher::Matcher() {}

void Matcher::setPattern(const std::string& s) {
    pattern = s;
}

void Matcher::setText(const std::string& s) {
    text = s;
}

static bool endsWith(const std::string& str, const std::string& suffix) {
    return str.size() >= suffix.size() &&
        str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

static bool startsWith(const std::string& str, const std::string& prefix) {
    return str.size() >= prefix.size() &&
        str.compare(0, prefix.size(), prefix) == 0;
}

void Matcher::process() {
    // Split pattern by *
    std::string buf;
    std::vector<std::string> parts;
    for (int i = 0; i < pattern.size(); ++i) {
        char c = pattern[i];
        if (c == '*') {
            if (!buf.empty()) {
                parts.push_back(buf);
                buf.clear();
            }
        } else {
            buf += c;
        }
    }
    if (!buf.empty()) {
        parts.push_back(buf);
        buf.clear();
    }

    // Check prefix
    if (pattern.front() != '*') {
        if (!startsWith(text, parts.front())) {
            match = false;
            return;
        }
        text.erase(0, parts.front().size());
        parts.erase(parts.begin());
    }

    if (text.empty()) {
        match = parts.empty();
        return;
    }

    // Check suffix
    if (pattern.back() != '*') {
        if (!endsWith(text, parts.back())) {
            match = false;
            return;
        }
        int n = parts.back().size();
        text.erase(text.size() - n, text.size());
        parts.pop_back();
    }

    if (text.empty()) {
        match = parts.empty();
        return;
    }

    // Now we compare the rest of the string
    // with pattern of type "*...*"

    // Find of pattern parts in text
    auto ac = std::make_unique<AhoCorasic>();

    for (const auto& part : parts) {
        ac->addString(part);
    }
    ac->prepare();

    auto partsByEndPos = ac->process(text, true);

    // Check for match

    // dp[i] is max number of parts that
    // could be put into first i symbols of text
    std::vector<int> dp(text.size());

    dp[0] = std::count(ALL(partsByEndPos[0]), 0);
    for (int i = 1; i < text.size(); ++i) {
        dp[i] = dp[i - 1];
        for (int p : partsByEndPos[i]) {
            int startPos = i - parts[p].size() + 1;
            if (dp[startPos] == p) {
                dp[i] = std::max(dp[i], p + 1);
            }
        }
    }

    match = dp.back() == parts.size();
}
