
#include <iostream>
#include <bitset>
#include <climits>

// Global Declarations
bool getValidNumber(int& number);
void printBits();
unsigned int bitField = 19;
int Console1();
int Console2();
void TurnOn(int bit);
void TurnOff(int bit);
void Toggle(int bit);
void Negate();
void LeftShift();
void RightShift();


// Main function
int main()
{
    // Int variables for the user's selections
    int userSelection1 = 0;
    int userSelection2 = 0;
    // default switch exit condition bool variable set to true
    bool continueRunning = true;
    // Do while loop for the console menu to allow to continue use of the menu and for validation purposes
    do {
        // Call Console1 function and return the user's answer to userSelection1
        userSelection1 = Console1();
        // Use a switch statement taking in the user's selection and applying it to the case
        switch (userSelection1)
        {
        case 1:
            // Call Console2 function and assign it to the userSelection2 variable
            userSelection2 = Console2();
            // Print out the user's selection and the original Bits
            std::cout << "You've selected TurnOn at index " << userSelection2 << std::endl;
            std::cout << "Old Bits: ";
            printBits();
            // Run the TurnOn function taking in the user's selection and display the new Bits
            TurnOn(userSelection2);
            std::cout << "New Bits: ";
            printBits();
            // Break out of switch
            break;
        case 2:
            // Call Console2 function and assign it to the userSelection2 variable
            userSelection2 = Console2();
            // Print out the user's selection and the original Bits
            std::cout << "You've selected TurnOff at index " << userSelection2 << std::endl;
            std::cout << "Old Bits: ";
            printBits();
            // Run the TurnOff function taking in the user's selection and display the new Bits
            TurnOff(userSelection2);
            std::cout << "New Bits: ";
            printBits();
            // Break out of switch
            break;
        case 3:
            // Call Console2 function and assign it to the userSelection2 variable
            userSelection2 = Console2();
            // Print out the user's selection and the original Bits
            std::cout << "You've selected Toggle at index " << userSelection2 << std::endl;
            std::cout << "Old Bits: ";
            printBits();
            // Run the Toggle function taking in the user's selection and display the new Bits
            Toggle(userSelection2);
            std::cout << "New Bits: ";
            printBits();
            // Break out of switch
            break;
        case 4:
            // Print out the user's selection and the original Bits
            std::cout << "You've selected Negate" << std::endl;
            std::cout << "Old Bits: ";
            printBits();
            // Run the Negate function and display the new Bits
            Negate();
            std::cout << "New Bits: ";
            printBits();
            // Break out of switch
            break;
        case 5:
            // Print out the user's selection and the original Bits
            std::cout << "You've selected LeftShift" << std::endl;
            std::cout << "Old Bits: ";
            printBits();
            // Run the LeftShift function and display the new Bits
            LeftShift();
            std::cout << "New Bits: ";
            printBits();
            // Break out of switch
            break;
        case 6:
            // Print out the user's selection and the original Bits
            std::cout << "You've selected RightShift" << std::endl;
            std::cout << "Old Bits: ";
            printBits();
            // Run the RightShift function and display the new Bits
            RightShift();
            std::cout << "New Bits: ";
            printBits();
            // Break out of switch
            break;
        case 7:
            // Print exit statement and the do while will be set to false exiting the loop and program
            std::cout << "Exiting the program. Goodbye!\n";
            continueRunning = false;
            break;
            // default of all invalid selections which will print statement to console and then continue inside the loop menu
        default:
            std::cout << "Invalid option. Try again" << std::endl;
            break;
        }
    } while (continueRunning);
    // Not needed but from what I researched it is normal to end the main in C++ with a return 0; statement so I added it. 
    return 0;
}

// Validation function, I went with a bool and pass in a int to validate
bool getValidNumber(int& number)
{
    // If the input is not a int value
    if (!(std::cin >> number))
    {
        // Clear the console in value
        std::cin.clear();
        // Ignore max possible character up to the \n
        std::cin.ignore(INT_MAX, '\n');
        // Return false as the value was not a valid int
        return false;
    }
    // Clear the console in value
    std::cin.clear();
    // Ignore max possible character up to the \n
    std::cin.ignore(INT_MAX, '\n');
    // Return true as the value was a valid int
    return true;
}

// Void printBits function to print out the orignial bits
void printBits()
{
    // This is a for loop that is set to 31 for the 32 bits and counts down the index
    for (int bitIndex = 31; bitIndex >= 0; --bitIndex)
    {
        // this prints the first bit on the left in the 31 index and then counts down the bitField until all 32 bits are displayed
        unsigned int bit = (bitField >> bitIndex) & 1;
        std::cout << bit;

        // this if statement cases the space every four bitIndex values displayed
        if (bitIndex % 4 == 0)
            std::cout << " ";
    }
    // Adds and endline after the bits are printed
    std::cout << std::endl;
}

// Int Console1 function for the main user menu and selections
int Console1()
{
    // int userSeletion1 variable set to zero
    int userSelection1 = 0;
    // print out hte bitField global variable to the console
    std::cout << "bitField: " << bitField << std::endl;
    // print the bits using the printBits function
    std::cout << "Bits: ";
    printBits();
    // print to console menu options
    std::cout << "TurnOn = 1, TurnOff = 2, Toggle = 3, Negate = 4, Left Shift = 5, Right Shift = 6, Exit = 7" << std::endl;
    std::cout << "Choose operation: ";
    // if else validation. Takes in the userSelection1 and runs it through the getValidNumber function if it validates
    // returns the userSelection1 else it gives invalid and asks for the selection again.
    if (getValidNumber(userSelection1)) {
        return userSelection1;
    }
    else
    {
        std::cout << "Invalid Entry please select from the selections available.";
        // the return 0 is outside the range of the valid 1 to 7 options 
        // returns the userSelection1 value to 0 before asking the user for a new selection
        return 0;
    }
}

// Int Console2 function that can be used to select the bitIndex you want to interact with in selection switch options
int Console2()
{
    // Int userSelection2 variable set to -1 because 0 is a valid index
    int userSelection2 = -1;

    // Continue to ask for input until a valid index is provided
    while (true) 
    {
        // Print to console for user to select the bit index
        std::cout << "Choose bit index: ";
        // if else validation. Takes in the userSelection2 and runs it through the getValidNumber function
        if (getValidNumber(userSelection2))
        {
            // Second if statement to make sure the user selects a valid index between 0 and 31.
            if (userSelection2 >= 0 && userSelection2 <= 31) 
            {
                return userSelection2;
            }
            else 
            {
                std::cout << "Invalid Entry, please select an index between 0 and 31.\n";
            }
        }
        else
        {
            // Print error message
            std::cout << "Invalid Entry, please select an index between 0 and 31.\n";
        }
    }
}


// Void TurnOn function to turn on a bit using OR |=
void TurnOn(int bit)
{
    bitField |= (1 << bit);
}
// Void TurnOn function to turn on a bit using AND &= Negate ~

void TurnOff(int bit)
{
    bitField &= ~(1 << bit);
}

// Void TurnOn function to turn on a bit using XOR ^=
void Toggle(int bit)
{
    bitField ^= (1 << bit);
}

// Void TurnOn function to turn on a bit using Negate
void Negate()
{
    bitField = ~bitField;
}

// Void TurnOn function to turn on a bit using shift left 1
void LeftShift()
{
    bitField = bitField << 1;
}

// Void TurnOn function to turn on a bit using shift right 1
void RightShift()
{
    bitField = bitField >> 1;
}