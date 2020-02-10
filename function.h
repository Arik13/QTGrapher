#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <functional>
#include <map>
#include "argument.h"

class FunctionMap;


/*
 * A mathematical function class. Functions are implemented as a tree, where the leaves
 * are constants or variables, and the branches are operators or elementary functions (e.g "+" or "sin")
 * There are constructors for 4 types of functions:
 *      - variable (leaf)
 *      - constant (leaf)
 *      - unary (branch)
 *      - binary (branch)
 *
 * The behaviour of each mathematical function is stored as a functor which is retrieved from the functionMap class.
 *
 * When calling the evaulate method:
 *      - Variable functions return the value of the supplied argument
 *      - Constant functions return their own value
 *      - Unary functions have a function type, represented by a string (e.g "sin"),
 *        as well as a sub function, which could be any type of function.  Input is
 *        passed to the sub function, and the result is evaluated according to the type
 *        (e.g sin(result)) and returned.
 *      - Binary functions also have a function type, represented by a string, usually of an
 *        arithmetic operator (e.g "+"). Input is passed to the sub functions, and the results
 *        are combined according to the type (e.g return result1 + result2)
 *
 * Single variable functions can also be differentiated, returning the derivative as a Function pointer
 *
 * Multi variable functions can also return the tangent plane intersecting a single point
 */
class Function {
public:
    Function(std::string funcName);				// Variable Function Constructor
    Function(std::string func, float val);		// Constant Function Constructor
    Function(std::string func, Function* arg);	// Unary Function Constructor
    Function(std::string func, Function* arg1, Function* arg2);		// Binary Function Constructor
    Function(Function* func);
    ~Function();
    float evaluate(char var, float val);
    float evaluate(char vars[], float vals[], int n);
    float evaluate(Argument* arg);
    bool isVariable(std::string var);
    Function* differentiate(std::string var);
    Function* tangentPlane(char* vars, float* values, int n);
    std::string name();

private:
    std::string funcName;
    std::function<float(Argument*, Function**)> function;
    Function** subFuncs;
    int numSubFuncs;
};

#endif // FUNCTION_H
