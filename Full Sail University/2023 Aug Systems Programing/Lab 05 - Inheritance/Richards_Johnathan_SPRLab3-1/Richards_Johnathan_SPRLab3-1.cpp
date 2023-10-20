// Richards_Johnathan_SPRLab3-1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "BaseAccount.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"
#include "CreditAccount.h"

// Function prototypes
bool getValidNumber(int& number);
int ConsoleMenu1();
int ConsoleMenu2();
void WriteBalancesToFile(CheckingAccount& checking, SavingsAccount& savings, CreditAccount& credit);

// The main where all the classes and functions are being called
int main()
{
	// include memory leak detection ( needs to be at top of main )
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(-1); // set block of memory to find memory leak
	_CrtDumpMemoryLeaks();
	// int Variables for menu selections
	int userSelection1 = 0;
	int userSelection2 = 0;
	// bool continueRunning for do while loops
	bool continueRunning = true;
	// float variable for amount to add or subtract from balances
	float amount;
	// Create an object of CheckingAccount, SavingsAccount and CreditAccount
	CheckingAccount checkingAccount;
	SavingsAccount savingsAccount;
	CreditAccount creditAccount;
	// Program title printed out to console
	std::cout << "Welcome to our Banking App" << std::endl;
	// do while loop for console menus
	do 
	{
		// call the ConsoleMenu1 for the top menu of checking, savings, credit or exit and assign the user's selection to userSelection1 variable
		userSelection1 = ConsoleMenu1();
		// switch passing in userSolection1
		switch (userSelection1)
		{
			case 1: //Checking
			{
				// Call to GetBalance and assign to CheckingBalance float variable
				float CheckingBalance = checkingAccount.GetBalance();
				// Print Current Balance
				std::cout << "Your Checking account balance: $" << CheckingBalance << std::endl << std::endl;
				// call the ConsoleMenu2 for the sub menu for Withdrawal, Deposit, Get Balance or return to main menu and take user's selection into userSelection2 variable
				userSelection2 = ConsoleMenu2();
				// switch passing userSelection2
				switch (userSelection2)
				{
					case 1: // Withdrawal
					{
						// Ask for amount to withdraw and take in the user's answer to amount
						std::cout << "Enter amount to withdraw: ";
						std::cin >> amount;
						// Call Withdraw from inside checkingAccount object passing amount
						checkingAccount.Withdraw(amount);
						// Call Getbalance to get updated balance for printing out
						CheckingBalance = checkingAccount.GetBalance();
						std::cout << "Your New Checking account balance: $" << CheckingBalance << std::endl << std::endl; // Print the balance
					}
					break;
					case 2: // Deposit
					{
						// Ask for amount to deposit and take in the user's answer to amount
						std::cout << "Enter amount to deposit: ";
						std::cin >> amount;
						// Call Deposit from inside checkingAccount object passing amount
						checkingAccount.Deposit(amount);
						// Call Getbalance to get updated balance for printing out
						CheckingBalance = checkingAccount.GetBalance();
						std::cout << "Your New Checking account balance: $" << CheckingBalance << std::endl << std::endl;
					}
					break;
					case 3: // GetBalance
					{	
						std::cout << "Current balance: " << checkingAccount.GetBalance() << "\n";
					}
					break;
					case 4: // Return to Main Menu
					{

					}
					break;
					default:
					break;
				}
			}
			break;
			case 2: // Savings
			{	
				// Call to GetBalance and assign to SavingsBalance float variable
				float SavingsBalance = savingsAccount.GetBalance();
				// Print Current Balance
				std::cout << "Your Savings account balance: $" << SavingsBalance << std::endl << std::endl;
				// call the ConsoleMenu2 for the sub menu for Withdrawal, Deposit, Get Balance or return to main menu and take user's selection into userSelection2 variable
				userSelection2 = ConsoleMenu2();
				// switch passing userSelection2
				switch (userSelection2)
				{
				case 1: // Withdrawal
				{
					// Ask for amount to withdraw and take in the user's answer to amount
					std::cout << "Enter amount to withdraw: ";
					std::cin >> amount;
					// Call Withdraw from inside savingsAccount object passing amount
					savingsAccount.Withdraw(amount);
					// Call Getbalance to get updated balance for printing out
					SavingsBalance = savingsAccount.GetBalance();
					std::cout << "Your New Savings account balance: $" << SavingsBalance << std::endl << std::endl;
				}
				break;
				case 2: // Deposit
				{
					// Ask for amount to deposit and take in the user's answer to amount
					std::cout << "Enter amount to deposit: ";
					std::cin >> amount;
					// Call Deposit from inside savingsAccount object passing amount
					savingsAccount.Deposit(amount);
					// Call Getbalance to get updated balance for printing out
					SavingsBalance = savingsAccount.GetBalance();
					std::cout << "Your New Savings account balance: $" << SavingsBalance << std::endl << std::endl;
				}
				break;
				case 3: // GetBalance
				{
					std::cout << "Current balance: " << savingsAccount.GetBalance() << "\n";
				}
				break;
				case 4: // Return to Main Menu
				{

				}
				break;
				default:
				break;
				}
			}	
			break;
			case 3: // Credit
			{
				// Call to GetBalance and assign to CreditBalance float variable
				float CreditBalance = creditAccount.GetBalance();
				// Print Current Balance
				std::cout << "Your Credit account balance: $" << CreditBalance << std::endl << std::endl;
				// call the ConsoleMenu2 for the sub menu for Withdrawal, Deposit, Get Balance or return to main menu and take user's selection into userSelection2 variable
				userSelection2 = ConsoleMenu2();
				// switch passing userSelection2
				switch (userSelection2)
				{
				case 1: // Withdrawal
				{
					// Ask for amount to withdraw and take in the user's answer to amount
					std::cout << "Enter amount to withdraw: ";
					std::cin >> amount;
					// Call Withdraw from inside creditAccount object passing amount
					creditAccount.Withdraw(amount);
					// Call Getbalance to get updated balance for printing out
					CreditBalance = creditAccount.GetBalance();
					std::cout << "Your New Credit account balance: $" << CreditBalance << std::endl << std::endl;
				}
				break;
				case 2: // Deposit
				{
					// Ask for amount to deposit and take in the user's answer to amount
					std::cout << "Enter amount to deposit: ";
					std::cin >> amount;
					// Call Deposit from inside savingsAccount object passing amount
					creditAccount.Deposit(amount);
					// Call Getbalance to get updated balance for printing out
					CreditBalance = creditAccount.GetBalance();
					std::cout << "Your New Credit account balance: $" << CreditBalance << std::endl << std::endl;
				}
				break;
				case 3: // GetBalance
				{
					std::cout << "Current balance: " << creditAccount.GetBalance() << "\n";
				}
				break;
				case 4: // Return to Main Menu
				{

				}
				break;
				default:
				break;
				}
			}
			break;
			case 4:
			{
				// Print exit statement and the do while will be set to false exiting the loop and program
				std::cout << "Exiting the program. Balances saved to balances.txt file. Goodbye!\n";
				WriteBalancesToFile(checkingAccount, savingsAccount, creditAccount);
				continueRunning = false;
			}
			break;
			default:
			break;
		}
	}
	while (continueRunning);
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

// Top Menu Function
int ConsoleMenu1()
{
	// int userSeletion1 variable set to zero
	int userSelection1 = 0;
	// do while loop for console menu
	do 
	{
		// print to console menu options
		std::cout << "Please Select Type of Account\n1 = Checking\n2 = Savings\n3 = Credit\n4 = Exit" << std::endl;
		std::cout << "Your Selection: ";
		// if else validation. Takes in the userSelection1 and runs it through the getValidNumber function if it validates
		// returns the userSelection1 else it gives invalid and asks for the selection again.
		if (getValidNumber(userSelection1)) {
			return userSelection1;
		}
		else
		{
			std::cout << "Invalid Entry please select from the selections available.\n";
			// the return 0 is outside the range of the valid 1 to 7 options 
			// returns the userSelection1 value to 0 before asking the user for a new selection
			return 0;
		}
	} while (true);
}

// Sub Menu Function
int ConsoleMenu2()
{
	// int userSeletion1 variable set to zero
	int userSelection2 = 0;
	// do while loop for console menu
	do 
	{
		// print to console menu options
		std::cout << "Would you like to make a\n1 = Withdrawal\n2 = Deposit\n3 = GetBalance\n4 = Return to Main Menu" << std::endl;
		std::cout << "Your Selection: ";
		// if else validation. Takes in the userSelection1 and runs it through the getValidNumber function if it validates
		// returns the userSelection1 else it gives invalid and asks for the selection again.
		if (getValidNumber(userSelection2)) {
			return userSelection2;
		}
		else
		{
			std::cout << "Invalid Entry please select from the selections available.\n";
			// the return 0 is outside the range of the valid 1 to 7 options 
			// returns the userSelection1 value to 0 before asking the user for a new selection
			return 0;
		}
	} while (true);
}

// Function to create or open file to write balances to
void WriteBalancesToFile(CheckingAccount& checking, SavingsAccount& savings, CreditAccount& credit)
{
	std::ofstream fout;
	// Open or create a file called balances.txt
	fout.open("balances.txt");
	// if file is open write the balances into the file
	if (fout.is_open())
	{
		fout << "Checking account balance: $" << checking.GetBalance() << std::endl;
		fout << "Savings account balance: $" << savings.GetBalance() << std::endl;
		fout << "Credit account balance: $" << credit.GetBalance() << std::endl;
		fout.close();
		std::cout << "Balances saved to balances.txt\n";
	}
	// else if file is not open print error statement
	else
	{
		std::cout << "File could not be opened\n";
	}
}
