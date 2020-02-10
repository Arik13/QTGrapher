#ifndef KEYBOARDSTATEMAP_H
#define KEYBOARDSTATEMAP_H


#include <map>
#include <QKeyEvent>
#include <iostream>

/*
 * Stores the pressed/unpressed state of keys
 */
class KeyboardStateMap : public std::map<int, bool>{
public:
    KeyboardStateMap();
    friend std::ostream& operator<<(std::ostream &os, const KeyboardStateMap& ksMap);
};

#endif // KEYBOARDSTATEMAP_H
