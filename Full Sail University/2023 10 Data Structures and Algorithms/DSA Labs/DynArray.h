/*
File:			DynArray.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:	

Purpose:		A dynamically-allocated resizeable array (similar to std::vector)
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
#define LAB_1	1

// Individual unit test toggles
#define LAB1_DEFAULT_CONSTRUCTOR_NO_ARGS			1
#define LAB1_DEFAULT_CONSTRUCTOR_WITH_ARGS			1
#define LAB1_BRACKET_OPERATOR						1
#define LAB1_SIZE_ACCESSOR							1
#define LAB1_CAPACITY_ACCESSOR						1
#define LAB1_RESERVE_EMPTY							1
#define LAB1_RESERVE_DOUBLE_CAPACITY				1
#define LAB1_RESERVE_LARGER_CAPACITY				1
#define LAB1_RESERVE_SMALLER_CAPACITY				1
#define LAB1_APPEND_NO_RESIZE						1
#define LAB1_APPEND_RESIZE							1
#define LAB1_CLEAR									1
#define LAB1_DESTRUCTOR								1
#define LAB1_ASSIGNMENT_OPERATOR					1
#define LAB1_COPY_CONSTRUCTOR						1

// Our implementation of a vector (simplified)
template<typename Type>
class DynArray 
{

	// Gives access to test code
	friend class UnitTests_Lab1;

	// Data members
	// NOTE: All values set to -1 for unit test purposes
	Type* mArray = reinterpret_cast<Type*>(-1);
	size_t mSize = -1;
	size_t mCapacity = -1;

public:
#if 1
	DynArray(size_t _startingCap = 0) 
	{
		// If 0 is passed in :
		// Set data members to values representing that no memory is allocated, 
		// and there is no space to store anything.
		if (_startingCap == 0) 
		{
			mArray = nullptr;
			mSize = 0;
			mCapacity = 0;
		}
		// Else:
		// Dynamically allocate an array of the supplied number of elements, 
		// and set your other data members to reflect that there is space to store data.
		else 
		{
			mArray = new Type[_startingCap];
			mSize = 0;
			mCapacity = _startingCap;
		}
	};
#endif

#if 1
	~DynArray() 
	{ 
		Clear(); 
	}
#endif

#if 1
	// This was used in both the copy and assignment constructor so I made a method.
	// The duplicate code was bothering me.
	void mCopy(const DynArray& _pass)
	{
		// Shallow copy
		mSize = _pass.mSize;
		mCapacity = _pass.mCapacity;
		// Deep copies – array
		mArray = new Type[mCapacity];
		for (size_t i = 0; i < mSize; i++)
		{
			mArray[i] = _pass.mArray[i];
		}
	}
#endif

#if 1
	DynArray(const DynArray& _copy) 
	{
		// Creates a copy of the object passed in.
		mCopy(_copy);
	}
#endif

#if 1
	DynArray& operator=(const DynArray& _assign) 
	{
		// Assigns all values to match those of the object passed in.
		// had to add the check which it mentions in the testing errors but not in the instructions.
		// Makers sure that the data passing in isn't the same as the data already here.
		// If it is then just return.
		if (this == &_assign)
		{
			return *this;
		}
		// Clean up existing memory before the deep copy(There’s a method that does this).
		Clear();
		// Shallow and Deep copy.
		mCopy(_assign);
		return *this;
	}
#endif

#if 1
	// Cleans up all dynamically allocated memory and resets varaibles.
	void Clear() 
	{
		// Cleans up all dynamically allocated memory.
		// Resets the object to its default state(what the data members would be after the default constructor. is called)
		delete[] mArray;
		mArray = nullptr;
		mSize = 0;
		mCapacity = 0;
	}
#endif

#if 1
	// Accessor for a single element, and return the data from the array,
	// supplied at the requested index without error checking.
	Type& operator[](size_t _index) { return mArray[_index]; }
#endif

#if 1
	// Accessor for the size data member.
	size_t Size() const { return mSize; }
#endif

#if 1
	// Accessor for the capacity data member.
	size_t Capacity() const { return mCapacity; }
#endif

#if 1
	// Stores a value in the next empty element, and updates the size.
	void Append(const Type& _data) 
	{
		// If there is not room to store any additional data, make room by doubling the capacity.
		// This can be done with a method you’ve already written.
		if (mSize == mCapacity)
		{
			Reserve();
		}
		mArray[mSize] = _data;
		mSize++;
	}
#endif

#if 1
	//	Resizes the array data member, based on the parameter. There are several cases that need to be handled, 
	//	depending on the value passed in, as well as the current state of the class object.
	void Reserve(size_t _newCapacity = 0) 
	{
		// If 0 is passed in:
		if (_newCapacity == 0)
		{
			//	If the capacity is currently 0, set the capacity to 1.
			if (mCapacity == 0)
			{
				mCapacity = 1;
			}
			// If the capacity is not 0, double the capacity.
			else
			{
				mCapacity = mCapacity * 2;
			}
		}
		//	If a non - zero value is passed in:
		//		If the value is larger than the current capacity, 
		//		set the capacity to that value.
		//		Otherwise, do nothing
		else if (_newCapacity > mCapacity) 
		{
			mCapacity = _newCapacity;
		}
			
		// I added a check to only do the following if the Capacity is greater than the mSize
		// The pseudo code didn't meantion this but without it, it fails LAB1_RESERVE_SMALLER_CAPACITY check.
		if (mCapacity > mSize)
		{
			//	• Dynamically allocate a temporary array of the new capacity, 
			//		and copy over any data that may be in the “smaller” array.
			Type* mArrayLarger = new Type[mCapacity];

			for (size_t i = 0; i < mSize; i++)
			{
				mArrayLarger[i] = mArray[i];
			}
			//	• Free up the memory of the data member.
			delete[] mArray;
			//	• Re - assign the data member to point to the “larger” array.
			mArray = mArrayLarger;
		}
	}
#endif
};