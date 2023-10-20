#pragma once
// Base Class
class Base
{
private:
	// Private Char name Pointer assigned to null
	char* name = nullptr;

public:
	// default constructor for Base class
	Base();

	// rule of 3
	Base& operator=(const Base& other); // assignment operator
	Base(const Base& other);			// copy constructor
	~Base();							// destructor

	// Set the name of the record
	void setName(const char* _name);

	// Get the name of the record
	char* getName() const;

	// Declare a pure virtual function for DisplayRecord set to 0
	virtual void DisplayRecord() = 0;
};

