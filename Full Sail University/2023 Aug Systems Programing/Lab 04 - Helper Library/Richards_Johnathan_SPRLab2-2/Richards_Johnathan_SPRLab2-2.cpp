
#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>

// Declare Helper namespace
namespace Helper 
{
    // Function to get and validate an integer from user input
    int GetValidatedInt(const char* strMessage, int nMinimumRange = 0, int nMaximumRange = 0) 
    {
        // Variable to store user input
        int value;
        // Loop to ask for input until it's valid
        while (true) 
        {
            // Display provided message
            std::cout << strMessage;
            // Read integer from user
            std::cin >> value;
            // Check if input is non-integer
            if (std::cin.fail()) 
            {
                // Clear error flags
                std::cin.clear();
                // Ignore rest of input buffer
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            // Check if input is within range or if no range is specified
            if ((nMinimumRange == 0 && nMaximumRange == 0) || (value >= nMinimumRange && value <= nMaximumRange)) 
            {
                // Return valid input
                return value;
            }
        }
    }
    // Function to generate a random number within a range
    int GetRandomNumberInRange(int min, int max) 
    {
        // srand(time(NULL)); needs to be added to int main when used.
        // Return random number between min and max (inclusive)
        return min + std::rand() % (max - min + 1);
    }
    // Function to clear and ignore the cin input buffer
    void ClearCinBuffer() 
    {
        // Clear error flags
        std::cin.clear();
        // Ignore rest of input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

#endif