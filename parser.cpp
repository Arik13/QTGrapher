#include <iostream>
#include <sstream>
#include "parser.h"
#include "functionmap.h"
#include <regex>

bool isFloat(const std::string& str) {
    std::istringstream iss(str);
    float f;
    iss >> std::noskipws >> f; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail();
}

Function* parseFunction(std::string funcStr) {
    std::string trimmedFuncStr = preprocessFuncString(funcStr);
    return parseFunction(trimmedFuncStr, 0, trimmedFuncStr.length() - 1);
}

Function* parseFunction(std::string funcStr, int lo, int hi) {
    if (lo > hi) throw std::string("Invalid function");

    std::string subStr = funcStr.substr(lo, ((hi - lo) + 1));
//    std::cout << subStr << std::endl;

    // Base Case: Function is a variable
    if (lo == hi && funcStr[lo] >= 'a' && funcStr[lo] <= 'z') {
        return new Function(std::string(1, funcStr[lo]));
    }

    // Base Case: Function is a constant
    if (isFloat(subStr)) {
        return new Function("const", boost::lexical_cast<float>(subStr));
    }

    // Split into sum or difference of sub functions
    int bracketLayer = 0;
    for (int i = lo; i < hi; i++) {
        if (funcStr[i] == '(') bracketLayer++;
        if (funcStr[i] == ')') bracketLayer--;
        if (bracketLayer == 0 && funcStr[i] == '+') {
            return new Function("+", parseFunction(funcStr, lo, i - 1), parseFunction(funcStr, i + 1, hi));
        }
        else if (bracketLayer == 0 && funcStr[i] == '-') {
            return new Function("-", parseFunction(funcStr, lo, i - 1), parseFunction(funcStr, i + 1, hi));
        }
    }

    // Split into product or quotient of sub functions
    bracketLayer = 0;
    for (int i = lo; i < hi; i++) {
        if (funcStr[i] == '(') bracketLayer++;
        if (funcStr[i] == ')') bracketLayer--;
        if (bracketLayer == 0 && funcStr[i] == '*') {
            return new Function("*", parseFunction(funcStr, lo, i - 1), parseFunction(funcStr, i + 1, hi));
        }
        else if (bracketLayer == 0 && funcStr[i] == '/') {
            return new Function("/", parseFunction(funcStr, lo, i - 1), parseFunction(funcStr, i + 1, hi));
        }
    }

    // Split into an exponential operation between a base sub function and an exponent sub function
    bracketLayer = 0;
    for (int i = lo; i < hi; i++) {
        if (funcStr[i] == '(') bracketLayer++;
        if (funcStr[i] == ')') bracketLayer--;
        if (bracketLayer == 0 && funcStr[i] == '^') {
            return new Function("^", parseFunction(funcStr, lo, i - 1), parseFunction(funcStr, i + 1, hi));
        }
    }

    // Parse the statement between two brackets
    if (funcStr[lo] == '(') {
        return parseFunction(funcStr, lo + 1, hi - 1);
    }
    // Parse an elementary function and its argument
    else if (funcStr.find("abs", lo) == lo) {
        return new Function("abs", parseFunction(funcStr, lo + 4, hi - 1));
    }
    else if (funcStr.find("sin", lo) == lo) {
        return new Function("sin", parseFunction(funcStr, lo + 4, hi - 1));
    }
    else if (funcStr.find("cos", lo) == lo) {
        return new Function("cos", parseFunction(funcStr, lo + 4, hi - 1));
    }
    else if (funcStr.find("tan", lo) == lo) {
        return new Function("tan", parseFunction(funcStr, lo + 4, hi - 1));
    }
    else if (funcStr.find("arcsin", lo) == lo) {
        return new Function("arcsin", parseFunction(funcStr, lo + 7, hi - 1));
    }
    else if (funcStr.find("arccos", lo) == lo) {
        return new Function("arccos", parseFunction(funcStr, lo + 7, hi - 1));
    }
    else if (funcStr.find("arctan", lo) == lo) {
        return new Function("arctan", parseFunction(funcStr, lo + 7, hi - 1));
    }
    else if (funcStr.find("ln", lo) == lo) {
        return new Function("ln", parseFunction(funcStr, lo + 3, hi - 1));
    }
    else if (funcStr.find("log", lo) == lo) {
        return new Function("log", parseFunction(funcStr, lo + 4, hi - 1));
    }
    else if (funcStr.find("PI", lo) == lo) {
        return new Function("PI", nullptr);
    }
    throw std::string("Invalid function");
}

std::string preprocessFuncString(std::string funcStr) {
    std::string processedFuncStr = "";

    // Remove whitespace
    for (int i = 0; i < funcStr.length(); i++) {
        if (funcStr[i] != ' ') {
            processedFuncStr += funcStr[i];
        }
    }
/*
    for (int i = 0; i < processedFuncStr.length() - 1; i++) {
        char *c1 = &processedFuncStr[i];
        char *c2 = &processedFuncStr[i + 1];

        if (*c2 == '^') {
            if (isLetter(c1)) {
                processedFuncStr.insert(i, "(");
                processedFuncStr.insert(i + 3, "(");
                int bracketLevel = 0;

                // Finds index of end of term
                int k;
                for (k = i + 4;
                     k < processedFuncStr.length() &&
                     (bracketLevel != 0 ||
                     (processedFuncStr[k] != '+' &&
                     (processedFuncStr[k] != '-' || isOperator(&processedFuncStr[k-1]))));
                     k++) {
                    if (processedFuncStr[k] == '(') bracketLevel++;
                    if (processedFuncStr[k] == ')') bracketLevel--;
                    std::cout << "Substr: " << processedFuncStr.substr(k) << std::endl;
                }
                std::cout << "Substr: " << processedFuncStr.substr(k) << std::endl;
                processedFuncStr.insert(k, "))");
                i += 3;
                std::cout << "New Position: " << processedFuncStr.substr(i) << std::endl;
            }
//            else if (isNumber(c1)) {
//                int j, k;
//                for (j = i; j >= 0 && !isOperator(&processedFuncStr[j]); j--) {}
//                int bracketLevel = 1;
//                processedFuncStr.insert(j, "(");
//                i++;
//                processedFuncStr.insert(i + 1, "(");
//                for (k = i + 2; k < processedFuncStr.length() && bracketLevel != 0; k++) {}
//                std::cout << "Substr: " << processedFuncStr.substr(k) << std::endl;
//                processedFuncStr.insert(k + 1, "))");
//                i += 2;
//            }
            std::cout << processedFuncStr << std::endl;
        }
    }
    for (int i = 0; i < processedFuncStr.length() - 1; i++) {
        char *c1 = &processedFuncStr[i];
        char *c2 = &processedFuncStr[i + 1];

        if (*c1 == ')' && *c2 == '(') {
            processedFuncStr.insert(i, "*");
            std::cout << processedFuncStr << std::endl;
            i += 1;
        }
        // xy -> (x*y)
        else if (isLetter(c1) && isLetter(c2)) {
            int j;
            // Find the index of the end of the current term
            for (j = ++i; j < processedFuncStr.length() && !isOperator(&processedFuncStr[j]); j++) {}
            std::string substr = processedFuncStr.substr(i, j - i);
            std::cout << "SubString: " << substr  << " [" << i << ", " << j << "]" << std::endl;

            // As long as letters do not represent a function name, format them as variables
            if (FunctionMap::funcMap.count(substr) == 0) {
                processedFuncStr.insert(i, "(");
                processedFuncStr.insert(i+2, "*");
                processedFuncStr.insert(i+4, ")");
                std::cout << processedFuncStr << std::endl;
                i += 3;
            }
            else {
                i += substr.length();
            }
        }

        // cx -> (c*x)
        else if (isNumber(c1) && isLetter(c2)) {
            int k;
            // Find the index of the end of the current term
            for (k = i; k < processedFuncStr.length() && !isOperator(&processedFuncStr[k]); k++) {}
            std::string substr = processedFuncStr.substr(i, k - i);
            std::cout << "SubString: " << substr  << " [" << i << ", " << k << "]" << std::endl;

            // As long as letters do not represent a function name, format them as variables
            if (FunctionMap::funcMap.count(substr) == 0) {
                int j;
                // Find the index of the end of the current term
                for (j = i; j >= 0 && !isOperator(&processedFuncStr[j]); j--){}
                processedFuncStr.insert(j+1, "(");
                processedFuncStr.insert(i+2, "*");
                processedFuncStr.insert(k+4, ")");
                std::cout << processedFuncStr << std::endl;
                i += 3;
            }
            else {
                i += substr.length();
            }
        }

        // c(f(...)) -> c*(f(...))
        else if (isNumber(c1) && processedFuncStr[i+1] == '(') {
            int j;
            int k;

            // Find the index of the start of the coefficient
            for (j = i; j >= 0 && !isOperator(&processedFuncStr[j]); j--){}
            int bracketLevel = 1;

            // Find the index of the end of the current term
            for (k = i + 2; k <= processedFuncStr.length() && bracketLevel != 0; k++) {

            }

            // Enclose coefficient and the term it multiplies in brackets, and add multiplication operator
            processedFuncStr.insert(j+1, "(");
            processedFuncStr.insert(i+2, "*");
            processedFuncStr.insert(k + 1, ")");
            std::cout << processedFuncStr << std::endl;
            i += 3;
        }
        // c(f(...)) -> c*(f(...))
        else if (isLetter(c1) && processedFuncStr[i+1] == '(') {
            processedFuncStr.insert(i+1, "*");
            std::cout << processedFuncStr << std::endl;
            i += 1;
        }

        else if (processedFuncStr[i] == ')' && !isOperator(c2) && *c2 != ')') {
            processedFuncStr.insert(i + 1, "*");
            i += 1;
        }
    }


    // Handle unary minus
    // -f(x) -> ((-1)*f(x))
    std::cout << "got here" << std::endl;
    for (int i = 0; i < processedFuncStr.length(); i++) {
        char *c = &processedFuncStr[i];
        if (*c == '-' && (i == 0 || isOperator(--c))) {
            std::cout << processedFuncStr << std::endl;
            processedFuncStr.replace(i, 1, "((-1)*");
            std::cout << processedFuncStr << std::endl;
            i += 6;
            int bracketLevel = 0;
            std::cout << processedFuncStr.substr(i) << std::endl;
            int j;
            for (j = i; j < processedFuncStr.length(); j++) {
                if (processedFuncStr[j] == '(') bracketLevel++;
                if (processedFuncStr[j] == ')') bracketLevel--;
                if (bracketLevel == 0 && (j == processedFuncStr.length() - 1 || (processedFuncStr[j] == '+' || processedFuncStr[j] == '-'))) {
                    break;
                }
            }
            processedFuncStr.insert(j, ")");
            i+=1;
        }
    }

    // Handle adjacent brackets
    // (f(x))(g(x)) -> (f(x))*(g(x))
    for (int i = 0; i < processedFuncStr.length() - 1; i++) {
        char *c1 = &processedFuncStr[i];
        char *c2 = &processedFuncStr[i + 1];

        if (*c1 == ')' && *c2 == '(') {
            processedFuncStr.insert(i + 1, "*");
            std::cout << processedFuncStr << std::endl;
            i += 1;
        }
    }
    std::cout << funcStr << " --> " << processedFuncStr << std::endl;
    */
    return processedFuncStr;
}

bool isOperator(char* c) {
    switch(*c) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
    case '(':
        return true;
    default:
        return false;
    }
}

bool isNumber(char* c) {
    int n = *c - '0';
    return (n >= 0 && n <= 9)? true : false;
}

bool isLetter(char* c) {
    return (*c >= 'a' && *c <= 'z')? true : false;
}


