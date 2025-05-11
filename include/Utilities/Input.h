#ifndef INPUT_H
#define INPUT_H

/**
 * @file Input.h 
 * @brief Namespace for input declaration.
*/

#include <vector>
#include <iostream>
#include <string>
#include <limits>

/// @brief Input manager.
namespace InputManager
{
    /**
     * @brief Get input as a string. 
     * @return String which was put by user. 
    */
    std::string getStringInput();

    /**
     * @brief Get input as integer in specified range. 
     * @param min Minimal value of integer. 
     * @param max Maximal value of integer. 
     * @return Integer which was put by user.
    */
    int getInt(int min, int max);

    /**
     * @brief Get choice in menu. Separate method is used to avoid mistakes common for input from zsh. 
     * @return Integer if it is appropriate, different error messages if it is not.
    */
    int getMenuChoice();

    /**
     * @brief Clear stream so there is no excess information in input.
    */
    void clearBuffer();
}

#endif