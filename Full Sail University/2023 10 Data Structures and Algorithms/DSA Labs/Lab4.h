/*
File:			DSA_Lab4.h	
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		Usage of the std::list class
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
#define LAB_4	1

// Individual unit test toggles
#define LAB4_QUEUE_ADD			1
#define LAB4_STACK_ADD			1
#define LAB4_QUEUE_REMOVE		1
#define LAB4_STACK_REMOVE		1
#define LAB4_INSERT_ITER		1
#define LAB4_INSERT_INDEX		1
#define LAB4_REMOVE_DECIMAL		1

/************/
/* Includes */
/************/
#include <list>

class DSA_Lab4 {

	friend class UnitTests_Lab4;	// Giving access to test code

	// Data members
	std::list<float> mList;

public:

	void QueueOrderingAdd(const float* _arr, size_t _size) 
	{
		//	Adds all of the values from the parameter into the list using queue ordering.
		//	Looped through the array based on size.
		for (size_t i = 0; i < _size; ++i)
		{
			//	Used push_back to add passed in values to the array front to back queue style.
			mList.push_back(_arr[i]);
		}
	}

	void StackOrderingAdd(const float* _arr, size_t _size) 
	{
		//	Adds all of the values from the parameter into the list using stack ordering.
		//	Looped through the array based on size.
		for (size_t i = 0; i < _size; ++i)
		{
			//	Used push_front to add passed in values to the array back to front stack style.
			mList.push_front(_arr[i]);
		}
	}

	float QueueOrderingRemove() 
	{
		//	Remove and return the next value in the list using queue ordering.
		//	Intialized a temp variable to hold the value of the front of the line.
		float tempFrontOfTheLine = 0;
		//	Assigned the front of the list value to the temp variable.
		tempFrontOfTheLine = mList.front();
		//	Deleted the front value using pop_front.
		mList.pop_front();
		//	Returned the stored front value.
		return tempFrontOfTheLine;
	}

	float StackOrderingRemove() 
	{
		//	Remove and return the next value in the list using stack ordering.
		//	Was the same as QueueOrderingRemove so jsut called existing function.
		return QueueOrderingRemove();
	}

	void Insert(int _index, float _val) 
	{
		//	Insert the supplied value N nodes away from the front node, based on the index passed in.
		//	Requires creating an iterator and “moving it” to the correct position.
		//	Initalized a variable to hold currentIndex.
		int currentIndex = 0;
		//	Made an iterator to move from the back to the front of the list and increment currentIndex when 
		//		the iter moved to the next value.
		for (std::list<float>::iterator iter = mList.begin(); iter != mList.end(); ++iter, ++currentIndex)
		{
			// if statment to check if the current index is equal to the passed in _index value of the desired insert element.
			if (currentIndex == _index)
			{
				//	Insert the values at the current location of the iterator.
				mList.insert(iter, _val);
				return;
			}
		}

	}

	void Insert(std::list<float>::iterator _iter, float _val) 
	{
		//	Insert the supplied value at the spot specified by the iterator passed in.
		//	This is as simple as calling the class’ insert method.
		mList.insert(_iter, _val);
	}

	int RemoveDecimalGreater(float _decimal) 
	{
		//	Removes all values from the list that have a decimal value greater than the passed - 
		//		in value(which will always be < 1), and returns the number of values removed.
		//			Does not care about the whole number portion, so only compare the decimal value.
		//			Example list with value passed in as 0.42.
		//				498.28 not removed, because 0.28 is not greater than 0.42.
		//				39812.181 not removed, because 0.181 is not greater than 0.42.
		//				3981.89 removed, because 0.89 is greater than 0.42.
		//				487.2 not removed, because 0.2 is not greater than 0.42.
		//	Find a way to isolate only the decimal portion of the values in the list.
		//	Intialized a variable to hold the number of values that were removed.
		int numberOfValuesRemoved = 0;
		//	Iteratorate through the list from beginning to end.
		for (std::list<float>::iterator iter = mList.begin(); iter != mList.end(); )
		{
			//	Intialized a variable to that takes the iter value - the iter casted to an int.
			//	Since Int doesn't contain decimals this is basically like dropping the decimal
			//	then subtracting that whole value from the float and being left with only the decimal.
			float onlyTheDecimal = *iter - (int)*iter;
			//	Compare if the decimal value is greater than the passed in decimal value.
			if (onlyTheDecimal > _decimal)
			{
				// if it is erase that iter and increament that numberOfValuesRemoved.
				iter = mList.erase(iter);
				numberOfValuesRemoved++;
			}
			//	If it isn't greater than the _decimal.
			else
			{
				// Increment the iterator.
				++iter;
			}
		}
		return numberOfValuesRemoved;
	}
};