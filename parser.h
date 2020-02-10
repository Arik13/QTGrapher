#ifndef PARSER_H
#define PARSER_H


#include "function.h"
#include <boost/lexical_cast.hpp>
#include <string>

bool isFloat(const std::string& someString);
Function* parseFunction(std::string funcStr);
Function* parseFunction(std::string funcStr, int lo, int hi);
std::string preprocessFuncString(std::string funcStr);
bool isOperator(char* c);
bool isNumber(char* c);
bool isLetter(char* c);

//enum ElementaryFunctions {ABS, SIN, COS, TAN, ARCSIN, ARCCOS, ARCTAN, LN, LOG, LENGTH};
//std::string elemFuncStrs[] = {"abs", "sin", "tan", "arcsin", "arccos", "arctan", "ln", "log"};

#endif // PARSER_H
