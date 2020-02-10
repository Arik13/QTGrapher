#include "keyboardstatemap.h"

KeyboardStateMap::KeyboardStateMap() {
    emplace(Qt::Key_W, false);
    emplace(Qt::Key_A, false);
    emplace(Qt::Key_S, false);
    emplace(Qt::Key_D, false);
    emplace(Qt::Key_Space, false);
    emplace(Qt::Key_Shift, false);
}

std::ostream& operator<<(std::ostream &os, const KeyboardStateMap& ksMap) {
    std::cout << "W: " << ((ksMap.at(Qt::Key_W))? "true" : "false") << std::endl;
    std::cout << "A: " << ((ksMap.at(Qt::Key_A))? "true" : "false") << std::endl;
    std::cout << "S: " << ((ksMap.at(Qt::Key_S))? "true" : "false") << std::endl;
    std::cout << "D: " << ((ksMap.at(Qt::Key_D))? "true" : "false") << std::endl;
    std::cout << "Space: " << ((ksMap.at(Qt::Key_Space))? "true" : "false") << std::endl;
    std::cout << "Shift: " << ((ksMap.at(Qt::Key_Shift))? "true" : "false") << std::endl;
    return os;
}
