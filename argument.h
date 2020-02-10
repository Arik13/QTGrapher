#ifndef ARGUMENT_H
#define ARGUMENT_H

#include <map>

/*
 * Used internally by the Function class to map variable names to the values they're being evaluated for
 */
class Argument : public std::map<char, float> {
public:
    Argument(char varName, float value);
    Argument(char varNames[], float values[], int n);
private:
};

#endif // ARGUMENT_H
