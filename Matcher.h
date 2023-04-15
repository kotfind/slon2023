#pragma once

#include <vector>
#include <string>

class Matcher {
    public:
        Matcher();

        void setPattern(const std::string&);
        void setText(const std::string&);

        void process();

        bool hasMatch() const { return match; }
        std::vector<std::pair<int, int>> getMatchSegments() const { return matchSegments; }

    private:
        std::string pattern;
        std::string text;

        bool match;
        std::vector<std::pair<int, int>> matchSegments;
};
