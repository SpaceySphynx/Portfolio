#include "Base.h"
#include <iostream>
#include <iostream>
// Base constructor
Base::Base()
{
	setName("Unknown");
}

// Base destructor
Base::~Base()
{
	delete[] name;
}

// Assignment operator for Base class
Base& Base::operator=(const Base& other)
{
	if (this != &other)
	{
		// Deep copy the name from 'other' object
		setName(other.name);
	}
	return *this;
}

// Copy constructor for Base class
Base::Base(const Base& other)
{
	*this = other;
}

// Set the name of the record with the given character string (_name)
void Base::setName(const char* _name)
{
	if (name != nullptr)
	{
		// Release previous memory
		delete[] name;
	}
	// Calculate the length of the new name
	size_t length = strlen(_name) + 1; 
	// Allocate memory for the new name
	name = new char[length];
	// Copy the new name into the allocated memory
	strcpy_s(name, length, _name); 
}

// Get the name of the record
char* Base::getName() const
{
	// Return the pointer to the name data
	return (char*)name;
}
