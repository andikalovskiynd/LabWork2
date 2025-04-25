#ifndef INPUT_H
#define INPUT_H
#include <vector>
#include <iostream>
#include <string>
#include <limits>

namespace InputManager
{
    std::string getStringInput();
    int getInt(int min, int max);
    int getMenuChoice();
    void clearBuffer();
}

#endif