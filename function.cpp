#include <math.h>
#include <iostream>
#include "function.h"
#include "functionmap.h"

static std::string constFunc	= "const";
static std::string eFunc		= "e";
static std::string piFunc		= "PI";
static std::string absFunc		= "abs";
static std::string sinFunc		= "sin";
static std::string cosFunc		= "cos";
static std::string tanFunc		= "tan";
static std::string asinFunc     = "arcsin";
static std::string acosFunc     = "arccos";
static std::string atanFunc     = "arctan";
static std::string lnFunc		= "ln";
static std::string logFunc		= "log";
static std::string sumFunc		= "+";
static std::string difFunc		= "-";
static std::string prodFunc     = "*";
static std::string divFunc		= "/";
static std::string powFunc		= "^";

// Constructs a constant function
Function::Function(std::string funcName, float value) {
    this->funcName = funcName;
    subFuncs = nullptr;
    function = [value](Argument* t, Function**) {return value; };
    numSubFuncs = 0;
}

// Constructs a variable function
Function::Function(std::string funcName) {
    this->funcName = funcName;
    subFuncs = nullptr;
    function = FunctionMap::funcMap[funcName];
    numSubFuncs = 0;
}

// 	Constructs a function which is an elementary function with an argument function
Function::Function(std::string funcName, Function* pSubFunc) {
    this->funcName = funcName;
    subFuncs = new Function*[1];
    subFuncs[0] = pSubFunc;
    function = FunctionMap::funcMap[funcName];
    numSubFuncs = 1;
}

// Constructs a function which is comprised of two sub functions and a binary operator
Function::Function(std::string funcName, Function* pSubFunc1, Function* pSubFunc2) {
    this->funcName = funcName;
    subFuncs = new Function*[2];
    subFuncs[0] = pSubFunc1;
    subFuncs[1] = pSubFunc2;
    function = FunctionMap::funcMap[funcName];
    numSubFuncs = 2;
}

// Copy Constructor
Function::Function(Function* func) {
    this->funcName = func->funcName;
    this->numSubFuncs = func->numSubFuncs;
    function = FunctionMap::funcMap[func->funcName];
    if (funcName == constFunc) {
        this->subFuncs = nullptr;
        float value = func->evaluate(nullptr);
        function = [value](Argument* t, Function**) {return value; };
    }
    else if (numSubFuncs == 0) {
        this->subFuncs = nullptr;
    }
    else if (func->numSubFuncs == 1) {
        this->subFuncs = new Function*[1];
        this->subFuncs[0] = new Function(func->subFuncs[0]);
    }
    else {
        this->subFuncs = new Function*[2];
        this->subFuncs[0] = new Function(func->subFuncs[0]);
        this->subFuncs[1] = new Function(func->subFuncs[1]);
    }
}

// Destructor
Function::~Function() {
    for (int i = 0; i < numSubFuncs; i++) {
        delete subFuncs[i];
    }
}

// Evaluates the value of a single variable function for the given variable and value
float Function::evaluate(char var, float val) {
    Argument* arg = new Argument(var, val);
    float evaluation = function(arg, subFuncs);
    delete arg;
    return evaluation;
}

// Evaluates the value of a multi variable function for the given variables and the given values
float Function::evaluate(char* vars, float vals[], int n) {
    Argument* arg = new Argument(vars, vals, n);
    float evaluation = function(arg, subFuncs);
    delete arg;
    return evaluation;
}

// Evaluates the value of a function using an Argument object
float Function::evaluate(Argument* arg) {
    return function(arg, subFuncs);
}

// Checks if the function is a variable
bool Function::isVariable(std::string var) {
    if (funcName == constFunc ||
        funcName == eFunc ||
        funcName == piFunc)
    {
        return false;
    }
    else if (funcName == sinFunc ||
        funcName == cosFunc ||
        funcName == tanFunc ||
        funcName == asinFunc ||
        funcName == acosFunc ||
        funcName == atanFunc ||
        funcName == lnFunc ||
        funcName == logFunc ||
        funcName == absFunc)
    {
        return subFuncs[0]->isVariable(var);
    }
    else if (funcName == sumFunc ||
        funcName == difFunc ||
        funcName == prodFunc ||
        funcName == divFunc ||
        funcName == powFunc)
    {
        return subFuncs[0]->isVariable(var) || subFuncs[1]->isVariable(var);
    }
    else if (var != funcName) {
        return false;
    }
    return true;
}

// Returns the derivative of a single variable function
Function* Function::differentiate(std::string var) {
    if (funcName == constFunc) {
        return new Function(constFunc, 0.0f);
    }
    else if (funcName == eFunc) {
        return new Function(constFunc, 0.0f);
    }
    else if (funcName == piFunc) {
        return new Function(constFunc, 0.0f);
    }
    else if (funcName == absFunc) {
        return nullptr;
    }
    else if (funcName == sinFunc) {
        Function* argFunc = new Function(subFuncs[0]);
        Function* derivFunc = new Function(cosFunc, argFunc);
        Function* chainFunc = new Function(argFunc->differentiate(var));
        return new Function(prodFunc, derivFunc, chainFunc );
    }
    else if (funcName == cosFunc) {
        Function* minusFunc = new Function(constFunc, -1.0f);
        Function* argFunc = new Function(subFuncs[0]);
        Function* derivFunc = new Function(cosFunc, argFunc);
        Function* chainFunc = new Function(argFunc->differentiate(var));
        Function* derivative = new Function(prodFunc, derivFunc, chainFunc);
        return new Function(prodFunc, minusFunc, derivative);
    }
    else if (funcName == tanFunc) {
        Function* argFunc = new Function(subFuncs[0]);
        Function* difFunc = new Function(sinFunc, argFunc);
        Function* expFunc = new Function(constFunc, -2.0f);
        Function* diffFunc2 = new Function(powFunc, difFunc, expFunc);
        Function* chainFunc = argFunc->differentiate(var);
        return new Function(prodFunc, diffFunc2, chainFunc);
    }
    else if (funcName == asinFunc) {
        // t^2
        Function* argFunc = new Function(subFuncs[0]);
        Function* powFunc1 = new Function(constFunc, 2.0f);
        Function* argSquareFunc = new Function(powFunc, argFunc, powFunc1);

        // 1 - t^2
        Function* oneFunc = new Function(constFunc, 1.0f);
        Function* botFunc = new Function(difFunc, oneFunc, argFunc);

        // sqrt(1 - t^2)
        Function* powFunc2 = new Function(constFunc, 0.5f);
        Function* denominator = new Function(powFunc, botFunc, powFunc2);

        Function* numerator = argFunc->differentiate(var);
        Function* derivative = new Function(divFunc, numerator, denominator);
        return derivative;
    }
    else if (funcName == acosFunc) {
        // t^2
        Function* argFunc = new Function(subFuncs[0]);
        Function* powFunc1 = new Function(constFunc, 2.0f);
        Function* argSquareFunc = new Function(powFunc, argFunc, powFunc1);

        // 1 - t^2
        Function* oneFunc = new Function(constFunc, 1.0f);
        Function* botFunc = new Function(difFunc, oneFunc, argFunc);

        // sqrt(1 - t^2)
        Function* powFunc2 = new Function(constFunc, 0.5f);
        Function* denominator = new Function(powFunc, botFunc, powFunc2);

        Function* numerator = argFunc->differentiate(var);
        Function* derivative = new Function(divFunc, numerator, denominator);
        Function* minusFunc = new Function(constFunc, -1.0f);
        return new Function(prodFunc, minusFunc, derivative);
    }
    else if (funcName == atanFunc) {
        // t^2
        Function* argFunc = new Function(subFuncs[0]);
        Function* powFunc1 = new Function(constFunc, 2.0f);
        Function* argSquareFunc = new Function(powFunc, argFunc, powFunc1);

        // 1 + t^2
        Function* oneFunc = new Function(constFunc, 1.0f);
        Function* denominator = new Function(sumFunc, oneFunc, argFunc);

        Function* numerator = argFunc->differentiate(var);
        Function* derivative = new Function(divFunc, numerator, denominator);
        return derivative;
    }
    else if (funcName == lnFunc) {
        Function* denominator = new Function(subFuncs[0]);
        Function* numerator = denominator->differentiate(var);
        Function* derivative = new Function(divFunc, numerator, denominator);
        return derivative;
    }
    else if (funcName == logFunc) {
        Function* arg = new Function(subFuncs[0]);
        Function* numerator = arg->differentiate(var);
        Function* logBase = new Function(constFunc, 10.0f);
        Function* lnOfBase = new Function(lnFunc, logBase);
        Function* denominator = new Function(prodFunc, arg, lnOfBase);
        Function* derivative = new Function(divFunc, numerator, denominator);
        return derivative;
    }
    else if (funcName == sumFunc) {
        Function* diffFunc1 = subFuncs[0]->differentiate(var);
        Function* diffFunc2 = subFuncs[1]->differentiate(var);
        return new Function(sumFunc, diffFunc1, diffFunc2);
    }
    else if (funcName == difFunc) {
        Function* diffFunc1 = subFuncs[0]->differentiate(var);
        Function* diffFunc2 = subFuncs[1]->differentiate(var);
        return new Function(difFunc, diffFunc1, diffFunc2);
    }
    else if (funcName == prodFunc) {
        Function* f = new Function(subFuncs[0]);
        Function* g = new Function(subFuncs[1]);
        Function* fPrime = subFuncs[0]->differentiate(var);
        Function* gPrime = subFuncs[1]->differentiate(var);
        Function* term1 = new Function(prodFunc, fPrime, g);
        Function* term2 = new Function(prodFunc, f, gPrime);
        Function* derivative = new Function(sumFunc, term1, term2);
        return derivative;
    }
    else if (funcName == divFunc) {
        Function* f = new Function(subFuncs[0]);
        Function* g = new Function(subFuncs[1]);
        Function* fPrime = subFuncs[0]->differentiate(var);
        Function* gPrime = subFuncs[1]->differentiate(var);
        Function* term1 = new Function(prodFunc, fPrime, g);
        Function* term2 = new Function(prodFunc, f, gPrime);
        Function* numerator = new Function(difFunc, term1, term2);
        Function* denominator = new Function(powFunc, g, new Function(constFunc, 2.0));
        Function* derivative = new Function(divFunc, numerator, denominator);
        return derivative;
    }
    else if (funcName == powFunc) {
        Function* base = new Function(subFuncs[0]);
        Function* exponent = new Function(subFuncs[1]);
        if (base->isVariable(var) && !exponent->isVariable(var)) {	// Apply power rule
            Function* n = new Function(exponent);
            Function* oneFunc = new Function(constFunc, 1.0f);
            Function* nMinusOne = new Function(difFunc, exponent, oneFunc);
            Function* newPower = new Function(powFunc, base, nMinusOne);
            Function* fPrimeOfG = new Function(prodFunc, n, newPower);
            Function* gPrime = base->differentiate(var);
            Function* derivative = new Function(prodFunc, fPrimeOfG, gPrime);
            return derivative;
        }
        else if (!base->isVariable(var) && !exponent->isVariable(var)) {	// Derivative is zero
            Function* zero = new Function(constFunc, 0.0f);
            return zero;
        }
        else if (!base->isVariable(var) && exponent->isVariable(var)) {
            Function* base = new Function(subFuncs[0]);
            Function* thisFunc = new Function(this);
            Function* lnFuncProd = new Function(lnFunc, base);
            Function* derivative = new Function(prodFunc, lnFuncProd, thisFunc);
            return derivative;
        }
        else {
            return nullptr;
        }
    }
    else if (var == funcName) {
        return new Function(constFunc, 1.0f);
    }
    else {
        return new Function(constFunc, 0.0f);
    }
}

// Returns the tangent plane to a multi variable function that touches a specific point
Function* Function::tangentPlane(char* vars, float* values, int n) {
    float f0 = evaluate(vars, values, n);
    Function* function = new Function(constFunc, f0);
    std::cout << "Function: " << name() << std::endl;
    for (int i = 0; i < n; i++) {
        std::string var(1, vars[i]);
        Function* partial = differentiate(var);
        std::cout << "Partial " << vars[i] << ": " << partial->name() << std::endl;
        float partialValue = partial->evaluate(vars, values, n);
        delete partial;
        Function* partialValueFunc = new Function(constFunc, partialValue);
        Function* varFunc = new Function(var);
        Function* pointFunc = new Function(constFunc, values[i]);
        Function* delta = new Function(difFunc, varFunc, pointFunc);
        Function* term = new Function(prodFunc, partialValueFunc, delta);
        function = new Function(sumFunc, function, term);
    }
    return function;
}

// Returns the function as a string
std::string Function::name() {
    if (funcName == sinFunc  ||
        funcName == cosFunc  ||
        funcName == tanFunc  ||
        funcName == asinFunc ||
        funcName == acosFunc ||
        funcName == atanFunc ||
        funcName == lnFunc   ||
        funcName == logFunc  ||
        funcName == absFunc)
    {
        return funcName + "(" + subFuncs[0]->name() + ")";
    }
    else if (funcName == sumFunc ||
        funcName == difFunc ||
        funcName == prodFunc ||
        funcName == divFunc ||
        funcName == powFunc)
    {
        return "(" + subFuncs[0]->name() + funcName + subFuncs[1]->name() + ")";
    }
    else if (funcName == eFunc ||
        funcName == piFunc)
    {
        return funcName;
    }
    else if (funcName == constFunc)
    {
        return "(" + std::to_string(evaluate(nullptr)) + ")";
    }
    else {
        return funcName;
    }
}
