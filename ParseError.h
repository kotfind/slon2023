#pragma once

#include <stdexcept>

class ParseError : public std::runtime_error {
    public:
        ParseError();
};
