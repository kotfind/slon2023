#include "Node.h"

#include <functional>
#include <map>
#include <math.h>

const std::map<char, std::function<double(double, double)>> Node::operators = {
    {'+', [](double lhs, double rhs) { return lhs + rhs; }},
    {'-', [](double lhs, double rhs) { return lhs - rhs; }},
    {'*', [](double lhs, double rhs) { return lhs * rhs; }},
    {'/', [](double lhs, double rhs) { return lhs / rhs; }},
};

#define F(f) {#f, [](double x) { return f(x); }}

const std::map<std::string, std::function<double(double)>> Node::functions = {
    F(sin),
    F(cos),
    F(tan),
    F(log),
};
