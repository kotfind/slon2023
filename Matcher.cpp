#include "Matcher.h"

#include "AhoCorasic.h"

#include <memory>
#include <algorithm>
#include <iostream>
#include <optional>

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

static std::vector<std::string> split(const std::string& s, char delim) {
    std::string buf;
    std::vector<std::string> parts;
    for (char c : s) {
        if (c == delim) {
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
    }
    return parts;
}

void Matcher::process() {
    matchSegments.clear();

    // Split pattern by *
    auto parts = split(pattern, '*');

    // Check prefix
    std::optional<std::pair<int, int>> firstMatchSegment = std::nullopt;
    int deletedPrefixLength = 0;
    if (pattern.front() != '*') {
        if (!startsWith(text, parts.front())) {
            match = false;
            return;
        }

        deletedPrefixLength = parts.front().size();
        firstMatchSegment = {0, deletedPrefixLength - 1};

        text.erase(0, deletedPrefixLength);
        parts.erase(parts.begin());
    }

    if (text.empty()) {
        match = parts.empty();
        return;
    }

    // Check suffix
    std::optional<std::pair<int, int>> lastMatchSegment = std::nullopt;
    if (pattern.back() != '*') {
        if (!endsWith(text, parts.back())) {
            match = false;
            return;
        }
        int n = parts.back().size();
        lastMatchSegment = {
            text.size() - n + deletedPrefixLength,
            text.size() - 1 + deletedPrefixLength
        };

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

    // pr[i] is j if (dp[i] was calculateded from dp[j])
    // or -1 otherwise
    std::vector<int> pr(text.size(), -1);

    dp[0] = std::count(ALL(partsByEndPos[0]), 0);
    for (int i = 1; i < text.size(); ++i) {
        dp[i] = dp[i - 1];
        for (int p : partsByEndPos[i]) {
            int startPos = i - parts[p].size() + 1;
            if (dp[startPos] == p && p + 1 > dp[i]) {  // XXX startPos - 1
                pr[i] = startPos;
                dp[i] = p + 1;
            }
        }
    }

    match = dp.back() == parts.size();
    if (!match) return;

    // Calculate matchSegments
    if (lastMatchSegment.has_value()) {
        matchSegments.push_back(*lastMatchSegment);
    }

    int cur = (int)text.size() - 1;
    while (cur >= 0) {
        if (pr[cur] == -1) {
            --cur;
        } else {
            matchSegments.push_back({
                pr[cur] + deletedPrefixLength,
                cur + deletedPrefixLength
            });
            cur = pr[cur] - 1;
        }
    }

    if (firstMatchSegment.has_value()) {
        matchSegments.push_back(*firstMatchSegment);
    }

    std::reverse(ALL(matchSegments));
}
