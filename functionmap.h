#ifndef FUNCTIONMAP_H
#define FUNCTIONMAP_H

#include <functional>
#include <map>
#include "function.h"
#include "argument.h"

/*
 * A map whos keys are mathematical function (or operator) names as strings (e.g "sin" or "+"). and whos values are
 * functors containing the code implementation for that mathematical function
 */
class FunctionMap : public std::map<std::string, std::function<float(Argument*, Function**)>> {
public:
    FunctionMap();
    static FunctionMap &funcMap;
};

#endif // FUNCTIONMAP_H
