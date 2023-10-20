/*
File:			Lab2.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		Usage of the std::vector class
Notes:			Property of Full Sail University 2310
*/

// Header protection
#pragma once

/***********/
/* Defines */
/***********/

/*
How to use:

	When working on a lab, turn that lab's #define from 0 to 1

		Example:	#define LAB_1	1

	When working on an individual unit test, turn that #define from 0 to 1

		Example:	#define DYNARRAY_DEFAULT_CTOR	1

NOTE: If the unit test is not on, that code will not be compiled!
*/

// Main toggle
#define LAB_2	1

// Individual unit test toggles
#define LAB2_PALINDROME_NUMBER		1
#define LAB2_FILL_FILE				1
#define LAB2_FILL_ARRAY				1
#define LAB2_CLEAR					1
#define LAB2_SORT_ASCENDING			1
#define LAB2_SORT_DESCENDING		1
#define LAB2_BRACKETS				1
#define LAB2_CONTAINS_TRUE			1
#define LAB2_CONTAINS_FALSE			1
#define LAB2_MOVE_PALINDROMES		1

/************/
/* Includes */
/************/
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>


inline int IsPalindromeNumber(unsigned int _num) 
{	
	// I have been pasting the PDF instructions in as Pseudo Code. 
	// Checks to see if the value passed in is a palindrome or not
	// This value can be any number of digits(1 - N)
	// A palindrome is any sequence that reads the same forwards and backwards

	// My approach: 
	// Take the value in and then assign the value reversed to a new variable.
	// Compare orginal input to the reverse and if equal true if not equal false.

	// Made a variable to store the original value since I will be changing it.
	unsigned int OriginalInput = _num;
	// Made a variable to store the reversed value.
	unsigned int ReverseOfInput = 0;
	// until the original value reaches 0 (while the number doesn't equal 0).
	while (_num != 0) 
	{
		// Take the last digit by using the modulo by 10 it takes the furtherest right digit.
		// 321 becomes 1 1st iteration, 2 second iteration etc.
		unsigned int theRemainder = _num % 10;
		// Append the digit to the ReverseOfInput Variable.
		// 1 -> 12 -> 123.
		ReverseOfInput = ReverseOfInput * 10 + theRemainder;
		// Remove the last digit.
		// 321 -> 32 -> 3.
		_num /= 10;
		// Repeats the entire loop until 321 becomes 123. 
	}
	// Compare the values using a bool and if statement.
	// return 0 for false and 1 for true probably could of also just put true or false for 0 and 1. 
	if (ReverseOfInput == OriginalInput)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

class DSA_Lab2
{
	friend class UnitTests_Lab2;	// Giving access to test code

private:

	std::vector<int> mValues;		// contains all of the values
	std::vector<int> mPalindromes;	// contains just the numbers that are palindromes (only used in MovePalindromes method)

public:

	void Fill(const char* _inputFilename) 
	{
		// Fill the values vector with the contents of the binary file
		// This file contains a four - byte header section that represents the number of values to be read and stored in the vector
		// Started with base example from the videos and kept making changes for my situation.
		
		// Openning the binary file that is being passed in.
		std::ifstream thisBinaryFile(_inputFilename, std::ios_base::binary);

		// Only error check I really added but it is useful 
		// considering there was no file in the original download and was like what is happening?
		if (!thisBinaryFile.is_open())
		{
			std::cerr << "Failed to open file: " << _inputFilename << std::endl;
			return;
		}
		// Variable to store the number of values from the binary header.
		int numberOfValues = 0;

		// Read the binary file header based on the size of the header. 
		// I know it's 4 bytes which makes me think it's an int. 
		thisBinaryFile.read((char*)&numberOfValues, sizeof(int));

		// Read the rest of the file.
		for (int i = 0; i < numberOfValues; i++)
		{
			int currentValue;
			thisBinaryFile.read((char*)&currentValue, sizeof(int));
			// Push back values of the file to be stored in mValues.
			mValues.push_back(currentValue);
		}
		// Close the file.
		thisBinaryFile.close();
	}

	void Fill(const int* _arr, size_t _size) 
	{
		// Fill the values vector with the contents of the passed - in array.
		// The easier one just loop through the array for it's supplied size 
		// while pushing to the mValue vector each value.
		for (size_t i = 0; i < _size; i++)
		{
			mValues.push_back(_arr[i]);
		}
	}

	void Clear() 
	{
		// Removes all elements from the values vector
		mValues.clear();
		mPalindromes.clear();
		// Decreases the capacity of the vector to 0
		mValues.shrink_to_fit();
		mPalindromes.shrink_to_fit();
		// There are two methods within the vector class to handle this
	}

	void Sort(bool _ascending) 
	{
		// Sorts the values vector, based on the value of the parameter
		// Use the std::sort method to handle the sort
		// based on ascending or not ascending since it's a bool I went if else.
		if (_ascending)
		{
			// if ascending is true sort ascending.
			std::sort(mValues.begin(), mValues.end());
		}
		else
		{
			// else make decending.
			// I had to look up how to make a decending version of sort.
			// had to add a lamda function to the end to make it decending.
			// Normally sort makes sure a < b when sorting as ascending so if set to a > b then decending.
			std::sort(mValues.begin(), mValues.end(), [](int a, int b){return a > b;});
		}

	}

	int operator[](int _index) 
	{
		// Returns an individual element from the values vector.
		// No need for error - checking, as std::vector.
		return mValues[_index];
	}

	bool Contains(int _val) const 
	{
		// Determines if a value is present in the values vector.
		// I immediately thought of a for loop to search the vector.
		// I researched a second way using std::find to do this but with with my first instinct.
		for (size_t i = 0; i < mValues.size(); i++)
		{
			if (mValues[i] == _val)
			{
				return true;
			}
		}
		return false;
	}

	void MovePalindromes() 
	{	
		// The values vector is populated with a number of values.
		// Iterate through this vector and move all of these values into the palindromes vector.
		// This will require adding them to palindromes and erasing them from values
		// Pseudo - code
		// Iterate through the values vector
		// Had to make it so it doesn't increment if it erases. Removed i++ and put it in the else.
		for (size_t i = 0; i < mValues.size();) 
		{
			// If the value is a palindrome(remember you have a method to check this)
			if (IsPalindromeNumber(mValues[i]))
			{
				// Add it to the palindromes vector.
				mPalindromes.push_back(mValues[i]);
				// Remove it from the values vector.
				mValues.erase(mValues.begin() + i);
			}
			else
			{
				// if no erase has happened then increment.
				i++;
			}
		}
	}
};

