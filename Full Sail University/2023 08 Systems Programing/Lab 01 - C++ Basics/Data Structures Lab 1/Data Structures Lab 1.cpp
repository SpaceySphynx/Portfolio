#include <iostream>
#include <climits>
#include <ctime>

// Global Declarations
bool getValidNumber(int& number);
std::string initials();
std::string whatName();
void intergralVariables();
void algebraProblem();
void gameDifficulty();
void randomDivisor();
void whichPopsicle();
void numberArray();
int checkAge();
int isItEven();
int age();


// Main function
int main()
{
    srand(time(NULL));
    // Call initials method and store in userInitials string variable
    std::string userInitials = initials();
    // Call age method and store in the userAge int variable
    int userAge = age();
    // Console out the user's initials
    std::cout << "Your initials are : " << userInitials << std::endl;
    // Console out the user's age
    std::cout << "Your age is: " << userAge << std::endl;
    // Console out about how many days the user has been alive not including leap years
    std::cout << userInitials << ", did you know you're at least " << userAge * 365 << " days old? \n";
    // Call the function for the numberArray
    numberArray();
    // Call the function for the algebraProblem
    algebraProblem();
    // Call the function for the intergralVariables
    intergralVariables();
    // Call the function for the whatName
    whatName();
    // Call the function for the checkAge
    checkAge();
    // Call the function for the isItEven
    isItEven();
    // Call the function for the randomDivisor
    randomDivisor();
    // Call the function for the whichPopsicle
    whichPopsicle();
    // Call the function for the gameDifficulty
    gameDifficulty();
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

// String initials function to get a user's initials
std::string initials()
{
    // Title
    std::cout << " Program 1-1 " << std::endl;
    // Array to store initials 3 to store 2 digits since one is the NULL value
    char initials[3];
    // Ask for user's initials on the console
    std::cout << "Please enter your initials (two characters): ";
    // Take in the initials value to store in the array
    std::cin.getline(initials, 3);
    // If cin fails then clear the input
    if (std::cin.fail())
    {
        std::cin.clear();
    }
    // Return the initials string value
    return std::string(initials);
}

// Int age function to get the user's age
int age()
{
    // Int variable to store the age
    int userAge;
    // While loop the value is true
    while (true)
    {
        // Ask the user with console out for them to enter their age
        std::cout << "Please enter your age: ";
        // If the input is a valid number according to the validation function and greater than zero
        if (getValidNumber(userAge) && userAge > 0)
        {
            // Break out of the loop
            break;
        }
        // If both conditions are not true then display this message and stay in the loop
        std::cout << "Invalid input. Age must be a positive and numeric. \n";
    }
    // Return user's age
    return userAge;
}

// Void numberArray() function
void numberArray()
{
    // Title
    std::cout << "\n Program 1-2" << std::endl;
    // Int numbers array taking in 5 positions
    int numbers[5];
    // For loop to run 5 times
    for (int i = 0; i < 5; i++)
    {
        // While true
        while (true)
        {
            // Ask user for a number and add to the array then break
            std::cout << "Please enter a number: ";
            // If statement that checks if the input is a valid number
            if (getValidNumber(numbers[i]))
            {
                // if valid break out of loop
                break;
            }
            // if false tell user input is invalid and to enter a valid number
            std::cout << "Invalid input. Please enter a valid number. \n";
        }
    }
    // Print the 5 digit array as a single number using a for loop
    std::cout << "You entered: ";
    for (int i = 0; i < 5; i++)
    {
        std::cout << numbers[i];
    }
    std::cout << "\n";
}

void algebraProblem()
{
    // Title
    std::cout << "\n Program 1-3" << std::endl;
    std::cout << "Please enter 3 numbers." << std::endl;
    // Int numbers array taking in 3 positions
    int numbers1[3];
    // Char a set to value a so I can increment through the letters in the loop
    char a = 'a';
    // For loop to run 3 times
    for (int i = 0; i < 3; i++)
    {
        // While true
        while (true)
        {
            // Ask user for a number and add to the array then break
            std::cout << "Enter value for " << a << ": ";
            // If statement that checks if the input is a valid number
            if (getValidNumber(numbers1[i]))
            {
                // if valid break out of loop
                break;
            }
            // if false tell user input is invalid and to enter a valid number
            std::cout << "Invalid input. Please enter a valid number. \n";
        }
        // Increment char a
        a++;
    }
    // assign each element in the array to a variable 
    int variable_a = numbers1[0];
    int variable_b = numbers1[1];
    int variable_c = numbers1[2];
    // Print the two problems
    std::cout << "a+1*b+2-c = " << variable_a+1*variable_b+2-variable_c << std::endl;
    std::cout << "(a+1)*(b+2)-c = " << (variable_a + 1) * (variable_b + 2) - variable_c << std::endl;
}

void intergralVariables() 
{
    // Title
    std::cout << "\n Program 1-4" << std::endl;
    // Made a table using hte max and min 
    std::cout << "Table of integral variable type ranges in C++:" << std::endl;
    std::cout << "type                  range" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "ushort                " << "0 to " << USHRT_MAX << std::endl;
    std::cout << "short                 " << SHRT_MIN << " to " << SHRT_MAX << std::endl;
    std::cout << "int                   " << INT_MIN << " to " << INT_MAX << std::endl;
    std::cout << "uint                  " << "0 to " << UINT_MAX << std::endl;
    std::cout << "longlong              " << LLONG_MIN << " to " << LLONG_MAX << std::endl;
    std::cout << "ulonglong              " << "0 to " << ULLONG_MAX << std::endl;
}

std::string whatName()
{
    // Title
    std::cout << "\n Program 1-5" << std::endl;
    char theArray[32];

    // Ask user for their name
    std::cout << "Please enter your name: ";
    std::cin.getline(theArray, 32);

    // Store the input in a string variable for easy manipulation
    std::string name = theArray;

    // Print out the interesting fact
    std::cout << "Hello there " << name << ", did you know that the core of the sun is believed to be 15 million degrees Celsius (27 million degrees Fahrenheit)." << std::endl;

    // Return the name
    return name;
}

int checkAge()
{
    // Title
    std::cout << "\n Program 1-6" << std::endl;
    int userOldEnough = 0;

    // While true
    while (true)
    {
        // Ask the user with console out for them to enter their age
        std::cout << "How old are you? ";
        // If the input is a valid number according to the validation function
        if (getValidNumber(userOldEnough))
        {
            if (userOldEnough > 17)
            {
                std::cout << "You should hurry up and play, you do not have a lot of time left." << std::endl;
                // Break out of the loop
                break;
            }
            else if (userOldEnough > 0 && userOldEnough < 18)
            {
                std::cout << "I'm sorry, but you're too young for this game. Bye!" << std::endl;
                // Break out of the loop
                break;
            }
            else
            {
                std::cout << "Invalid input. Age must be a positive number. \n";
            }
        }
        else
        {
            // If the condition is not true then display this message and stay in the loop
            std::cout << "Invalid input. Age must be numeric. \n";
        }
    }
    // Return user's age
    return userOldEnough;
}

int isItEven()
{
    // Title
    std::cout << "\n Program 1-7" << std::endl;
    int userNumber2 = 0;

    // While true
    while (true)
    {
        // Ask the user with console out for them to enter their age
        std::cout << "Please enter an even number: ";
        // If the input is a valid number according to the validation function
        if (getValidNumber(userNumber2))
        {
            if (userNumber2%2 == 0)
            {
                std::cout << "Nice!" << std::endl;
                // Break out of the loop
                break;
            }
            else
            {
                std::cout << "Boo!" << std::endl;
            }
        }
        else
        {
            // If the condition is not true then display this message and stay in the loop
            std::cout << "Invalid input. Age must be numeric. \n";
        }
    }
    // Return user's age
    return userNumber2;
}

void randomDivisor()
{
    // Title
    std::cout << "\n Program 1-8" << std::endl;
    std::cout << "Please enter a divisor: ";
    int userNumber3 = 0;
    std::cin >> userNumber3;

    for (int i = 0; i < 3; i++)
    {
        int randomNumber = rand();
        std::cout << randomNumber << " - ";
        if (randomNumber % userNumber3 == 0)
        {
            std::cout << "yes!" << std::endl;
        }
        else 
        {
            std::cout << "no" << std::endl;
        }
    }
}

void whichPopsicle()
{
    // Title
    std::cout << "\n Program 1-9" << std::endl;
    // User interface on console out asking for popsicle type
    std::cout << "Which color popsicle do you want from the freezer? " << std::endl;
    std::cout << "1) Red " << std::endl;
    std::cout << "2) Green " << std::endl;
    std::cout << "3) Blue " << std::endl;
    std::cout << "13) Orange " << std::endl;
    std::cout << "> ";
    // Int variable popsicle set to 0
    int popsicle = 0;
    // take console in new value of popsicle from user
    std::cin >> popsicle;
    // using switch statement for each popsicle type selected taking in the popsicle variable
    switch (popsicle) 
    {
        // case one is going to print to screen for the 1) Red selection
    case 1:
        std::cout << "Red, I think that one is fruit punch, let me know." << std::endl;
        // breaks out of switch
        break;
        // case two for selecting 2) Green
    case 2:
        std::cout << "Green, oh I iddn't think anyone liked the green ones." << std::endl;
        // Breaks out of switch
        break;
        // Case three for selecting 3) Blue
    case 3:
        std::cout << "Blue, will turn your tongue the same color." << std::endl;
        // Breaks out of switch
        break;
        // Case thirteen for selecting 13) Orange
    case 13:
        std::cout << "Orange, the only one that the flavor and color is the same selection." << std::endl;
        // Breaks out of switch
        break;
        // All other selections will return this output
    default:
        std::cout << "Sorry I do not have that type of popsicle" << std::endl;
    }
}

void gameDifficulty()
{
    // Title
    std::cout << "\n Program 1-10" << std::endl;
    // User interface on console.
    std::cout << "Difficulty Levels " << std::endl;
    std::cout << "1) Easy " << std::endl;
    std::cout << "2) Medium " << std::endl;
    std::cout << "3) Hard " << std::endl;
    std::cout << "What is your choice? ";
    // Int variables set to their defaults
    int difficultyLevel = 0;
    // With the randoms I have added numbers to adjust thier ranges.
    int randomNumber1 = rand() % 10+1;
    int randomNumber2 = 10+rand() % 16;
    int randomNumber3 = 25+rand() % 26;
    // Assign the user's selection to the difficultyLevel variable
    std::cin >> difficultyLevel;
    // switch statement taking in the difficultyLevel variable
    switch (difficultyLevel)
    {
        // case 1 for 1) Easy and prints out the following infomation including the random number of enemies
    case 1:
        std::cout << "You've selected Easy and will have to fight " << randomNumber1 << " enemies!" << std::endl;
        // Breaks out of switch
        break;
        // case 2 for 2) Medium selection
    case 2:
        std::cout << "You've selected Medium and will have to fight " << randomNumber2 << " enemies!" << std::endl;
        // Breaks out of switch
        break;
        // case 3 for 3) Hard selection
    case 3:
        std::cout << "You've selected Hard and will have to fight " << randomNumber3 << " enemies!" << std::endl;
        // Breaks out of switch
        break;
        // All other selections will return this output
    default:
        std::cout << "Sorry please select option 1, 2, or 3";
    }
}