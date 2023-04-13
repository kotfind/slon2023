#include "ParseError.h"

ParseError::ParseError()
    : std::runtime_error("couldn't parse")
{}
