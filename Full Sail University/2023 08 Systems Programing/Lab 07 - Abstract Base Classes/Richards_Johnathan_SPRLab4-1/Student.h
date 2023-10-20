#pragma once
#include "Base.h"
// Student class which publicly inherits from the Base class
class Student : public Base
{
private:
	// Private member variable to store the GPA of an Student
	int GPA = 0;

public:
	// Default constructor for the Employee class
	Student();

	// Destructor for the Student class
	~Student();

	// Prompt and get salary
	int getGPA() const;
	void setGPA(int _GPA);
	virtual void DisplayRecord() override;
};

