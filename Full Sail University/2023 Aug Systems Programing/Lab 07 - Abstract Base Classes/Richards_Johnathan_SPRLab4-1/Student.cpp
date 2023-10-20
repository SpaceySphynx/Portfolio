#include "Student.h"
#include <iostream>
// Student constructor
Student::Student()
{

}
// Student destructor
Student::~Student()
{

}
// Getter Method for getting constant 
int Student::getGPA() const
{
	return GPA;
}
// Setter method for setting the GPA for a student
void Student::setGPA(int _GPA)
{
	GPA = _GPA;
}
// DisplayRecord Method with console printout to collect Name and Salary infomartion
void Student::DisplayRecord()
{
	std::cout << "Name: " << getName() << "\tGPA: " << getGPA() << std::endl;
}