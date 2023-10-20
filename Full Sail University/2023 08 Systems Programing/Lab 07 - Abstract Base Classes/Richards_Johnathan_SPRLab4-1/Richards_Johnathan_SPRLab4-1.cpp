// Richards_Johnathan_SPRLab4-1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>

#include "Base.h"
#include "Employee.h"
#include "Student.h"

// Functions Prototypes
void addRecord(std::vector<Base*>& records, int type);
void displayAllRecords(const std::vector<Base*>& records);
void duplicateRecord(std::vector<Base*>& records);
int ConsoleMenu1();
int ConsoleMenu2();
bool getValidNumber(int& number);


int main()	// Main Method
{
	// include memory leak detection ( needs to be at top of main )
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(-1); // set block of memory to find memory leak
	_CrtDumpMemoryLeaks();

	// Declared a vector of Base pointers
	std::vector<Base*> records;
	// int Variables for menu selections
	int userSelection1 = 0;
	int userSelection2 = 0;
	// bool continueRunning for while loop
	bool continueRunning = true;

	// Program title printed out to console
	std::cout << "Abstract Base Classes" << std::endl;
	// while loop set to while true continueRunning Variable
	while (continueRunning) 
	{
		// Call ConsoleMenu1 Function and assign to int variable userSelection1
		userSelection1 = ConsoleMenu1();

		// switch passing in userSelection1
		switch (userSelection1) 
		{
			// Last program I did menus that repeated code with minor adjustments 
			// which made my code long and to me seemed like duplicate code so I looked into
			// a way to do it this time with less code
		case 1: // Employee
		case 2: // Student
			// if userSelection1 is 1 print out Employee Selected else Student Selected
			// because I left case 1 blank this if statement is considered case 1 and case 2
			// this allowed me to put only one switch statement nested
			if (userSelection1 == 1) 
			{
				std::cout << "\nEmployee Selected\n";
			}
			else {
				std::cout << "\nStudent Selected\n";
			}

			// Call ConsoleMenu2 Function and assign to int variable userSelection2
			userSelection2 = ConsoleMenu2();
			// Here is my nested switch menu passing in userSelection2 variable
			switch (userSelection2) 
			{
				// Selection 1 calls addRecord function passing in records vector
				// and userSelection1 to know if the record is employee or student
				case 1:
					addRecord(records, userSelection1);
					break;
				// Selection 2 calls displayAllRecords function passing in records vector
				case 2:
					displayAllRecords(records);
					break;
				// Selection 3 calls duplicateRecord function passing in records vector 
				case 3:
					duplicateRecord(records);
					break;
				// Exit Menu by exiting the while true loop by making the bool false
				case 4:
					continueRunning = false;
					break;
				// default wrong selection is entered so not valid is printed out and then menu loops back around to top menu
				default:
					std::cout << "Not a valid selection\n" << std::endl;
					break;
			}
			break;
		// Exit Menu by exiting the while true loop by making the bool false
		case 3:
			continueRunning = false;
			break;
		// default wrong selection is entered so not valid is printed out and then menu loops back around
		default:
			std::cout << "Not a valid selection\n" << std::endl;
			break;
		}
	}
	
	// for loop to delete all record pointers on program exit
	for (Base* record : records) 
	{
		delete record;
	}
	
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
		std::cout << "Please Select Type of Record: \n1 = Employee\n2 = Student\n3 = Exit" << std::endl;
		std::cout << "Your Selection: ";
		// if else validation. Takes in the userSelection1 and runs it through the getValidNumber function if it validates
		// returns the userSelection1 else it gives invalid and asks for the selection again.
		if (getValidNumber(userSelection1)) 
		{
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

int ConsoleMenu2()
{
	// int userSeletion1 variable set to zero
	int userSelection2 = 0;
	// do while loop for console menu
	do
	{
		// print to console menu options
		std::cout << "Please Select Record Action: \n1 = Add a Record\n2 = Display All Records\n3 = Duplicate a Record\n4 = Exit" << std::endl;
		std::cout << "Your Selection: ";
		// if else validation. Takes in the userSelection1 and runs it through the getValidNumber function if it validates
		// returns the userSelection1 else it gives invalid and asks for the selection again.
		if (getValidNumber(userSelection2)) 
		{
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

// addRecord function 
void addRecord(std::vector<Base*>& records, int type)
{
	// takes in 100 characters which is probably excessive 
	char name[100];

	// if type of record is equal to 1 for employee
	if (type == 1)
	{
		// Create a new Employee object
		Employee* newEmployee = new Employee();

		//  Prompt and get name
		std::cout << "Enter employee name: ";
		std::cin.getline(name, 100);

		// Prompt and get salary
		int salary;
		std::cout << "Enter employee salary: ";
		std::cin >> salary;

		// Set the provided name and salary to the new employee object
		newEmployee->setName(name);
		newEmployee->setSalary(salary);

		// Add the new Employee object to the records vector
		records.push_back(newEmployee);
	}
	// Else, if the provided type is 2 then it is a Student
	else if (type == 2)
	{
		// Create a new Student object
		Student* newStudent = new Student();

		// Prompt user for student's name
		std::cout << "Enter student name: ";
		std::cin.getline(name, 100);

		// Prompt user for student's GPA
		int GPA;
		std::cout << "Enter student GPA: ";
		std::cin >> GPA;

		// Set the provided name and GPA to the new student object
		newStudent->setName(name);
		newStudent->setGPA(GPA);

		// Add the new Student object to the records vector
		records.push_back(newStudent);
	}
	
	size_t i = records.size() - 1;  // Index of the last (newly added) record
	std::cout << "\nRecord added at index " << i << ":\n";
	records[i]->DisplayRecord();
	std::cout << std::endl;
	// Clear any leftover input
	std::cin.ignore(INT_MAX, '\n');
}

// displayAllRecords function
void displayAllRecords(const std::vector<Base*>& records)
{
	// loop through the vector and print to console
	for (size_t i = 0; i < records.size(); ++i)
	{
		std::cout << "\nRecord at index " << i << ":\n";
		records[i]->DisplayRecord();
		std::cout << std::endl;
	}
}

// duplicateRecord function
void duplicateRecord(std::vector<Base*>& records)
{
	// Prompt user for index of record and assign to int variable for the index
	int index;
	std::cout << "Enter the index of the record you want to duplicate: ";
	std::cin >> index;

	// Validate if valid index is entered
	if (index >= 0 && index < records.size())
	{
		// Obtain the record at the specified index
		Base* originalRecord = records[index];

		// Attempt to dynamically cast the record to an Employee pointer
		Employee* employeeRecord = dynamic_cast<Employee*>(originalRecord);
		// If the dynamic cast was successful, it means the record is of type Employee
		if (employeeRecord)
		{
			// Create a newEmployee using the copy constructor with the original Employee record
			Employee* newEmployee = new Employee(*employeeRecord);
			// Add the newly created Employee record to the end of the records vector
			records.push_back(newEmployee);
			// Calculate the index of the last (newly added) record
			size_t i = records.size() - 1;
			// Print to console the record that was duplicated
			std::cout << "\nRecord added at index " << i << ":\n";
			records[i]->DisplayRecord();
			std::cout << std::endl;  // For an extra line between records for clarity.
			return;
		}

		// Check if the record is a Student
		Student* studentRecord = dynamic_cast<Student*>(originalRecord);
		// if studentRecord is varified take record into if statement
		if (studentRecord)
		{
			// Create a newStudent using the copy constructor with the original Student record
			Student* newStudent = new Student(*studentRecord);
			// Add the newly created Student record to the end of the records vector
			records.push_back(newStudent);
			// Calculate the index of the last (newly added) record
			size_t i = records.size() - 1;
			// Print to console the record that was duplicated
			std::cout << "\nRecord added at index " << i << ":\n";
			records[i]->DisplayRecord();
			std::cout << std::endl;
			return;
		}
	}
	else
	{
		std::cout << "Invalid index provided." << std::endl;
	}
}