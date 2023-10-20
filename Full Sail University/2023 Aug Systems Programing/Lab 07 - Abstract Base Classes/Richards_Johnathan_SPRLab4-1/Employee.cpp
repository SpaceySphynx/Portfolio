#include "Employee.h"
#include <iostream>
// Employee constructor
Employee::Employee()
{

}
// Employee destuctor
Employee::~Employee()
{

}
// Getter Method for getting constant int salary
int Employee::getSalary() const
{
	return salary;
}
// Setter method for setting the salary of an Employee
void Employee::setSalary(int _salary)
{
	salary = _salary;
}
// DisplayRecord Method with console printout to collect Name and Salary infomartion
void Employee::DisplayRecord()
{
	std::cout << "Name: " << getName() << "\tSalary: " << getSalary() << std::endl;
}