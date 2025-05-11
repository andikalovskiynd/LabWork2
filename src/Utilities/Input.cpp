/**
 * @file Input.cpp 
 * @brief Implementation of class Input methods. 
*/

#include "Utilities/Input.h"
#include "Utilities/Console.h"

namespace InputManager
{
    void clearBuffer()
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::string getStringInput()
    {
        std::string input;
        std::getline(std::cin >> std::ws, input);
        while (input.empty()) 
        {
            Console::printInvalidInput("Input must not be empty.");
            std::getline(std::cin >> std::ws, input);
        }
        return input;
    }

    int getInt(int min, int max)
    {
        int value = -1;
        bool validInput = false;
        while (!validInput)
        {
            if (std::cin >> value)
            {
                char remains;
                if(std::cin.get(remains) && remains == '\n')
                {
                    if (value >= min && value <= max)
                    {
                        validInput = true;
                    }
                    else
                    {
                        Console::printInvalidInput("Out of range.");
                    }
                }
                else 
                {
                    Console::printInvalidInput("Incorrect input. Please enter ONLY a number");
                    clearBuffer();
                }
            }
            else
            {
                Console::printInvalidInput("Incorrect input. Please enter a number.");
                clearBuffer();
            }
        }

        return value;
    }

    int getMenuChoice()
    {
        int choice = -1;
        bool validInput = false;

        while (!validInput)
        {
            if(std::cin >> choice)
            {
                char remains;
                if(std::cin.get(remains) && remains == '\n')
                {
                    validInput = true;
                }

                else 
                {
                    Console::printInvalidInput("Incorrect input. Please enter ONLY a number");
                    clearBuffer(); 
                }
            }

            else 
            {
                Console::printInvalidInput("Incorrect input. Please enter a number.");
                clearBuffer(); 
            }
        }

        return choice;
    }
}