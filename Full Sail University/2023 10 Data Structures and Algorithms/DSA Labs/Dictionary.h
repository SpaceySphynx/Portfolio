/*
File:			DList.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		A hash-mapped data structure using key/value pairs and separate chaining
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
#define LAB_5	1

// Individual unit test toggles
#define LAB5_PAIR_CTOR				1
#define LAB5_CTOR					1
#define LAB5_DTOR					1
#define LAB5_CLEAR					1
#define LAB5_INSERT_NEW				1
#define LAB5_INSERT_EXISTING		1
#define LAB5_FIND					1
#define LAB5_FIND_NOT_FOUND			1
#define LAB5_REMOVE					1
#define LAB5_REMOVE_NOT_FOUND		1
#define LAB5_ASSIGNMENT_OP			1
#define LAB5_COPY_CTOR				1

/************/
/* Includes */
/************/
#include <list>

template<typename Key, typename Value>
class Dictionary 
{

	friend class UnitTests_Lab5;	// Giving access to test code

	struct Pair 
	{
		Key key;			
		Value value;		

		Pair(const Key& _key, const Value& _value) 
		{
			//	Assign the members to the values passed in.
			key = _key;
			value = _value;
		}

		// For testing
		bool operator==(const Pair& _comp) const 
		{
			return (_comp.key == key &&
				_comp.value == value);
		}
	};

	// Data members
	// NOTE: All values set to -1 for unit test purposes
	std::list<Pair>* mTable = reinterpret_cast<std::list<Pair>*>(-1);							// A dynamic array of lists (these are the buckets)
	size_t mNumBuckets = -1;																	// Number of elements in mTable
	unsigned int(*mHashFunc)(const Key&) = reinterpret_cast<unsigned int(*)(const Key&)>(-1);	// Pointer to the hash function


public:

	Dictionary(size_t _numBuckets, unsigned int (*_hashFunc)(const Key&)) 
	{
		//	Dynamically allocate the table, based on the supplied number of buckets:
		//		Look at the type of pointer the table is if you are having problems.
		mTable = new std::list<Pair>[_numBuckets];		
		//	Assign your other data members to the passed - in values.
		mNumBuckets = _numBuckets;
		mHashFunc = _hashFunc;
	}

	~Dictionary() 
	{
		//	Cleans up all dynamically allocated memory:
		//		You do not need to remove the data from each individual list.
		delete []mTable;
	}

	Dictionary(const Dictionary& _copy) 
	{
		// Creates a copy of the object passed in.
		//	Deep copy the table:
		//		This is an array.Look at previous examples of deep - copying arrays.
		//	Shallow copy the other data members.
		mNumBuckets = _copy.mNumBuckets;	
		mTable = new std::list<Pair>[mNumBuckets];
		for (size_t i = 0; i < mNumBuckets; ++i)
		{
			mTable[i] = _copy.mTable[i];
		}
		mHashFunc = _copy.mHashFunc;
	}

	Dictionary& operator=(const Dictionary& _assign) 
	{
		//	Self-assignment check.
		if (this == &_assign)
		{
			return *this;
		}
		//	Assigns all values to match those of the object passed in.
		//	Cleans up existing memory before the deep copy:
		//		Clear doesn’t work the same as the previous labs
		delete []mTable;
		//	Deep copy the table:
		//		This is an array.Look at previous examples of deep - copying arrays.
		//	Shallow copy the other data members.
		mNumBuckets = _assign.mNumBuckets;
		mTable = new std::list<Pair>[mNumBuckets];
		for (size_t i = 0; i < mNumBuckets; ++i)
		{
			mTable[i] = _assign.mTable[i];
		}
		mHashFunc = _assign.mHashFunc;
		return *this;
	}

	void Clear() 
	{
		//	Empty all of the data from each bucket.
		//	Do not delete the table or reset any of the data members.
		for (int i = 0; i < mNumBuckets; ++i)
		{
			mTable[i].clear();
		}
	}

	void Insert(const Key& _key, const Value& _value) 
	{
		//	Add (or update) a Pair, based on the key value provided.
		//	Call the hash function to find out which bucket to interact with.
		unsigned int bucketIndex = mHashFunc(_key) % mNumBuckets;
		Pair newPair(_key, _value);
		//	Error	C2440	'initializing': cannot convert from 'Dictionary<float,float>::Pair' to 'float'
		//	Remember to look through the entire bucket before adding / updating.
		for (auto insertIterator = mTable[bucketIndex].begin(); insertIterator != mTable[bucketIndex].end(); ++insertIterator)
		{
			//	Existing key:
			//		If the key is already in the bucket, update the associated value.
			if (insertIterator->key == _key)
			{
				insertIterator->value = _value;
				return;
			}
		}
		//	If the key is not in the bucket:
				//		Create a Pair and add it to the bucket.
		mTable[bucketIndex].push_back(newPair);
	}

	const Value* Find(const Key& _key) 
	{
		//	Checks to see if a key is present or not.
		//	Call the hash function to find out which bucket to interact with.
		unsigned int bucketIndex = mHashFunc(_key) % mNumBuckets;
		//	Remember to look through the entire bucket before returning.
		for (auto findIterator = mTable[bucketIndex].begin(); findIterator != mTable[bucketIndex].end(); ++findIterator)
		{
			//	Key found:
			//		Return the address of the pair’s value.
			if (findIterator->key == _key)
			{
				return &(findIterator->value);
			}
		}
		//	Key not found:
		//		Return a null pointer.
		return nullptr;
	}

	bool Remove(const Key& _key) 
	{
		//	Removes a pair from the Dictionary if present.
		//	Call the hash function to find out which bucket to interact with.
		unsigned int bucketIndex = mHashFunc(_key) % mNumBuckets;
		//	Remember to look through the entire bucket before returning.
		for (auto removeIterator = mTable[bucketIndex].begin(); removeIterator != mTable[bucketIndex].end(); ++removeIterator)
		{
			//	Key found:
			//		Erase the pair from the bucket and return true to indicate success.
			if (removeIterator->key == _key)
			{
				mTable[bucketIndex].erase(removeIterator);
				return 1;
			}
		}
		//	Key not found:
		//		Nothing to remove, so only need to return false.
		return 0;
	}
};