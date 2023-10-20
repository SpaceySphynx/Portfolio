// Richards_Johnathan_SPRLab2-1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>
#include <string>
#include <climits>

// Enumeration to define the possible car colors
enum EnumColorDefinition
{
    Red,   // 0 represents Red
    Blue,  // 1 represents Blue
    Green  // 2 represents Green
};

// Struct to represent a car
struct Car
{
    char Make[32];              // Char array to store car's make
    char Model[32];             // Char array to store car's model
    int Year;                   // Integer to store car's manufacturing year
    int Mileage;                // Integer to store car's mileage
    EnumColorDefinition Color;  // Enumeration to store car's color
};

// Function prototypes
bool getValidNumber(int& number);
void randomNumberArray();
void randomNumberArrayPointer();
void carInformation(Car cararray[3]);
void printCar(Car c);
void printCarPointer(Car* ptrCar);
void addMileage(Car* ptrCar, int milesToAdd);

// The main where all the functions are being called
int main()
{
    // Seed random number generator with the current time
    srand(time(NULL)); 
    // Call function to print 15 random numbers along with their memory addresses
    randomNumberArray();
    // Call function to print 15 random numbers using pointers
    randomNumberArrayPointer();
    // Define an array of 3 Car structs
    Car cararray[3];
    // Call function to gather information for the 3 cars
    carInformation(cararray);
    // Print information for each car using a for loop and printCar function
    std::cout << "Printing cars...\n";
    for (int i = 0; i < 3; i++) {
        printCar(cararray[i]);
    }
    // Print information for each car using pointers and printCarPointer function
    std::cout << "Printing car pointers...\n";
    for (int i = 0; i < 3; i++) {
        printCarPointer(&cararray[i]);
    }
    // Call the addMileage Function selecting car 1 which is 0 and adds 1000 miles
    addMileage(&cararray[0], 1000);
    // Print information for each car after mileage addition
    std::cout << "Printing cars after adding mileage...\n";
    for (int i = 0; i < 3; i++) 
    {
        printCar(cararray[i]);
    }
    // Return 0 to close out the main
    return 0;
}
// Function to validate user input for an integer
bool getValidNumber(int& number)
{
    // If input is not an integer
    if (!(std::cin >> number))
    {
        // Clear the error flag
        std::cin.clear();
        // Ignore the rest of the line
        std::cin.ignore(INT_MAX, '\n');
        // Return false to signal input was not a valid integer
        return false;
    }
    // Clear the error flag
    std::cin.clear();
    // Ignore the rest of the line
    std::cin.ignore(INT_MAX, '\n');
    // Return true to signal input was a valid integer
    return true;
}
// Function to generate and print 15 random numbers along with their memory addresses
void randomNumberArray()
{
    // Define an array to store 15 integers
    int numbers[15];
    // Loop 15 times
    for (int i = 0; i < 15; i++)
    {
        // Generate random number and store it in the array
        numbers[i] = rand();
        // Print the random number to console and its memory address
        std::cout << "Random Number: " << numbers[i] << "\t Memory Address : " << &numbers[i] << std::endl;
    }
}
// Function similar to randomNumberArray but emphasizes using pointers
void randomNumberArrayPointer()
{
    // Define an array to store 15 integers
    int numbers2[15];
    // Loop 15 times
    for (int i = 0; i < 15; i++)
    {
        // Generate random number and store it in the array
        numbers2[i] = rand();
        // Print the random number to console and its memory address
        std::cout << "Random Value: " << numbers2[i] << "\t Pointer Address: " << &numbers2[i] << std::endl;
    }
}
// Function to collect information for 3 cars from the user
void carInformation(Car cararray[3])
{
    // Prompt user for details about 3 cars
    std::cout << "Please enter information for three cars: " << std::endl;
    // Variable to store user's color selection
    int colorInput;
    // Loop 3 times for 3 cars
    for (int i = 0; i < 3; i++)
    {
        // Prompt for make, model, year, mileage, and color, and store in cararray
        std::cout << "What is the make of the car?" << std::endl;
        std::cin.getline(cararray[i].Make, 32);
        std::cout << "What is the model of the car?" << std::endl;
        std::cin.getline(cararray[i].Model, 32);
        while (true)
        {
            std::cout << "What is the year of the car?" << std::endl;
            if (getValidNumber(cararray[i].Year) && cararray[i].Year >= 1886 && cararray[i].Year <= 2023)
            {
                break;
            }
            std::cout << "Invalid input. Year must be numeric and between 1886 and 2023. \n";
        }
        while (true)
        {
            std::cout << "What is the mileage of the car?" << std::endl;
            if (getValidNumber(cararray[i].Mileage) && cararray[i].Mileage >= 0)
            {
                break;
            }
            std::cout << "Invalid input. Year must be numeric and positive. \n";
        }
        std::cout << "What is the color of the car? 0 for Red, 1 for Blue, 2 for Green: ";
        std::cin >> colorInput;
        std::cin.ignore(); // Clearing the buffer
        cararray[i].Color = (EnumColorDefinition)colorInput;
    }
}
// Function to print details about a car
void printCar(Car c)
{
    std::string color;   // Variable to store color as a string
    // Convert the enum color to its string representation using a switch
    switch (c.Color) 
    {
    case Red: color = "Red"; break;
    case Blue: color = "Blue"; break;
    case Green: color = "Green"; break;
    default: color = "Unknown"; break;
    }
    // Print the car's year, color, make, model, and mileage
    std::cout << c.Year << " - " << color << " " << c.Make << " " << c.Model << " with " << c.Mileage << " miles \n" << std::endl;
}
// Function to print details about a car using a pointer
void printCarPointer(Car* ptrCar) 
{
    // Dereference the pointer and call printCar
    printCar(*ptrCar);
}
// Function to add a specified number of miles to a car's mileage
void addMileage(Car* ptrCar, int milesToAdd) 
{
    // Use the pointer to increment the car's mileage by milesToAdd
    ptrCar->Mileage += milesToAdd;
}



