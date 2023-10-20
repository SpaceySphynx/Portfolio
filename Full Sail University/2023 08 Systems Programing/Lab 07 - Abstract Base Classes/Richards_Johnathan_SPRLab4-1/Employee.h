#pragma once
#include "Base.h"

// Employee class which publicly inherits from the Base class
class Employee : public Base
{
private:
	// Private member variable to store the salary of an Employee
	int salary = 0;

public:
	// Default constructor for the Employee class
	Employee();

	// Destructor for the Employee class
	~Employee();

	// Getter method to retrieve the salary of an Employee (constant int)
	int getSalary() const;

	// Setter method to set the salary of an Employee
	void setSalary(int _salary);

	// Override the DisplayRecord method from the Base class to display Employee information
	virtual void DisplayRecord() override;
};

