/*
File:			DList.h\
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		A doubly-linked list (similar to std::list)
Notes:			Property of Full Sail University 2310
*/

// Header protection
#pragma once
#include <iostream>
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
#define LAB_3	1

// Individual unit test toggles			
#define LAB3_CTOR						1
#define LAB3_NODE_CTOR_DEFAULT			1
#define LAB3_NODE_CTOR					1
#define LAB3_ADDHEAD_EMPTY				1
#define LAB3_ADDHEAD					1
#define LAB3_ADDTAIL_EMPTY				1
#define LAB3_ADDTAIL					1
#define LAB3_CLEAR						1
#define LAB3_DTOR						1
#define LAB3_ITER_BEGIN					1
#define LAB3_ITER_END					1
#define LAB3_ITER_INCREMENT_PRE			1
#define LAB3_ITER_INCREMENT_POST		1
#define LAB3_ITER_DECREMENT_PRE			1
#define LAB3_ITER_DECREMENT_POST		1
#define LAB3_ITER_DEREFERENCE			1
#define LAB3_INSERT_EMPTY				1
#define LAB3_INSERT_HEAD				1
#define LAB3_INSERT_MIDDLE				1
#define LAB3_ERASE_EMPTY				1
#define LAB3_ERASE_HEAD					1
#define LAB3_ERASE_TAIL					1
#define LAB3_ERASE_MIDDLE				1
#define LAB3_ASSIGNMENT_OP				1
#define LAB3_COPY_CTOR					1

template<typename Type>
class DList 
{

	friend class UnitTests_Lab3;	// Giving access to test code

	struct Node 
	{
		// NOTE: Values set to -1 for unit test purposes
		Type data;
		Node* next = reinterpret_cast<Node*>(-1);
		Node* prev = reinterpret_cast<Node*>(-1);

	
		Node(const Type& _data, Node* _next = nullptr, Node* _prev = nullptr) 
		{
			//	Set the data members to the values of the parameters passed in.
			data = _data;
			next = _next;
			prev = _prev;
		}
	};

public:

	class Iterator 
	{
	public:

		Node* mCurr = reinterpret_cast<Node*>(-1);

		Iterator& operator++() 
		{
			//	Moves the Iterator to the next node in the list and returns it.
			//  Setting Current equal to the next node.
			mCurr = mCurr->next;
			//	Return reference to the current iterator.
			return *this;
		}

		Iterator operator++(int) 
		{
			//	Post-fix operators take in an int to allow the compiler to differentiate.
			//	Moves the Iterator to the next node in the list and return an Iterator to the original position.
			//	This will require a temporary variable.
			//	Made a temp position iterator set to original iterator.
			Iterator tempPosition = *this;
			//	Setting current equal to the next node.
			mCurr = mCurr->next;
			//	Return temp position which is storing the original position.
			return tempPosition;
		}

		Iterator& operator--() 
		{
			//	Moves the Iterator to the previous node in the list and returns it.
			//  Setting Current equal to the previous node.
			mCurr = mCurr->prev;
			//	Return reference to the current iterator.
			return *this;
		}

		Iterator operator--(int) 
		{
			//	Post-fix operators take in an int to allow the compiler to differentiate.
			//	Moves the Iterator to the previous node in the list and return an Iterator to the original position.
			//	This will require a temporary variable.
			//	Made a temp position iterator set to original iterator.
			Iterator tempPosition = *this;
			//	Setting current equal to the previous node.
			mCurr = mCurr->prev;
			//	Return temp position which is storing the original position.
			return tempPosition;
		}

		Type& operator*() 
		{
			//	Return the data of the node the Iterator is pointing to.
			return mCurr->data;
		}

	
		bool operator != (const Iterator& _iter) const 
		{
			return mCurr != _iter.mCurr;
		}
	};

	// Data members
	// NOTE: All values set to -1 for unit test purposes
	Node* mHead = reinterpret_cast<Node*>(-1);
	Node* mTail = reinterpret_cast<Node*>(-1);
	size_t mSize = -1;

public:

	DList() 
	{
		//	Set all data members to reflect that no nodes are currently allocated.
		mHead = nullptr;
		mTail = nullptr;
		mSize = 0;
	}

	~DList() 
	{
		//	Free up the memory for all dynamically allocated nodes (There’s a method that does this).
		Clear();
	}

	DList(const DList& _copy)  
	{
		mHead = nullptr;
		mTail = nullptr;
		mSize = 0;
		//	Creates a copy of the object passed in
		//	Deep copy the entire list
		//		This requires some type of loop to move through the passed - in list
		//		Look at your other methods, as there are some that can make this very easy
		Node* copyNodes = _copy.mHead;

		//	This requires some type of loop to move through the passed - in list.
		for (int i = 0; i < _copy.mSize; ++i)
		{
			//	Look at your other methods, as there are some that can make this very easy.
			AddTail(copyNodes->data);
			copyNodes = copyNodes->next;
		}
		//	If the size has not already been updated, shallow copy it
		//	Remember that data members are not automatically initialized in C++
	}

	DList& operator=(const DList& _assign) 
	{
		//	Assigns all values to match those of the object passed in.
		//	When I ran the check it reminded me to add a check before startings 
		//	To make sure I'm not just copying values into a list that has those values alreadly.
		if (this == &_assign)
		{
			//	If the list passed in matches this list than just return.
			return *this;
		}
		//	Clean up existing memory before the deep copy(There’s a method that does this)
		Clear();
		//	Deep copy the entire list.
		//	Used existing nodes to make the list.
		Node* mCurr = _assign.mHead;

		//	This requires some type of loop to move through the passed - in list.
		for (int i = 0; i < _assign.mSize; ++i)
		{
			//	Look at your other methods, as there are some that can make this very easy.
			AddTail(mCurr->data);
			mCurr = mCurr->next;
		}
		//	If the size has not already been updated, shallow copy it. It already updates.
		return *this;
	}

	void AddHead(const Type& _data) 
	{
		//	Dynamically add a Node to the front of the list.
		//	Dynamically created a new node taking in the passed in _data.
		Node* newNode = new Node(_data);
		//	Set the previous newNode to nullptr since this new node will be the Head. 
		newNode->prev = nullptr;
		//	Check if there is a head, if one does not exist, create a head and tail both set to this first newly created node.
		if (nullptr == mHead)
		{
			mHead = newNode;
			mTail = newNode;
		}
		//	Else if a head already exists:
		else
		{
			//	Create a temporary node to store the original mHead information.
			Node* oldHead = mHead;
			//	Update the head to point to the newly added node.
			oldHead->prev = newNode;
			newNode->next = oldHead;
			//	Update the new node as the Head.
			mHead = newNode;
		}		
		//	Update the size of the list.
		mSize++;
		//	Don’t forget to link the nodes together before updating the head.
	}

	void AddTail(const Type& _data) 
	{
		//	Dynamically add a Node to the back of the list.
		//	Dynamically created a new node taking in the passed in _data.
		Node* newNode = new Node(_data);
		//	Set the next newNode to nullptr since this new node will be the Tail. 
		newNode->next = nullptr;
		//	Check if there is a tail, if one does not exist, create a head and tail both set to this newly created node.
		if (nullptr == mTail)
		{
			mHead = newNode;
			mTail = newNode;
		}
		//	Else if tail already exists:
		else
		{
			//	Create a temporary node to store the original mTail information.
			Node* oldTail = mTail;
			//	Update the tail to point to the newly added node.
			mTail->next = newNode;
			//	Update the new node as the tail.
			mTail = newNode;
			//	Update the tail to point to the newly added node.
			mTail->prev = oldTail;
		}
		//	Update the size of the list.
		mSize++;
		//	Don’t forget to link the nodes together before updating the tail.
	}

	void Clear() 
	{
		//	Free up the memory for all dynamically allocated nodes.
		//	Set all of the data members back to their default state.
		//	Remember there are more nodes than just the head and tail.
		//		This will require some form of loop.
		//	Creatde a temporary node.
		Node* temp;
		//	Loop while the head doens't equal nullptr.
		while (mHead != nullptr)
		{
			//	Assign the current head to a temp variable.
			temp = mHead;
			//	Move the head iterator or pointer to the next node.
			mHead = mHead->next;
			//	Delete the temp node.
			delete temp;
		}
		//	mTail reset to nullptr.
		mTail = nullptr;
		//	mSize reset to zero.
		mSize = 0;		
	}

	Iterator Insert(Iterator& _iter, const Type& _data) 
	{	
		/*
		Debugging code as I was having a lot of issues figuring out what I did wrong here.
		if (mHead != nullptr && _iter.mCurr != nullptr)
		{
			std::cout << "List up to iterator's position: ";
			Node* currentNode = mHead;
			while (currentNode != nullptr && currentNode != _iter.mCurr)
			{
				std::cout << currentNode->data << " -> ";
				currentNode = currentNode->next;
			}
			std::cout << "||| (iterator's position)" << std::endl;
		}
		*/

		//	Do not be afraid to diagram this!
		//	Dynamically allocate a Node and insert it in front of the position of the passed - in Iterator.
		//	There are three special cases for this method, depending on what the Iterator is storing.
		//		Empty List
		//			Iterator will be storing a null pointer, so the list needs to be started.
		//			There’s a method to help with this.
		//		Head
		//			Iterator will be storing a pointer to the head of the list
		//			There’s a method to help with this

		//	If it's a Empty List or at the Head call the AddHead and Begin Methods.
		if (nullptr == _iter.mCurr || mHead == _iter.mCurr)
		{
			AddHead(_data);
			return Begin();
		}

		//		Anywhere else
		//			Iterator is storing a pointer to another node(even the tail)
		//			Link the nodes before and after the inserted nodes
		else
		{
			//std::cout << "Inserting before node with data: " << _iter.mCurr->data << std::endl;
			
			//	created the new node.
			Node* newNode = new Node(_data);
			/*
			if (_iter.mCurr->prev) {
				std::cout << "Iterator's previous node data: " << _iter.mCurr->prev->data << std::endl;
			}
			else {
				std::cout << "Iterator's previous node is nullptr." << std::endl;
			}
			if (_iter.mCurr->next) {
				std::cout << "Iterator's next node data: " << _iter.mCurr->next->data << std::endl;
			}
			else {
				std::cout << "Iterator's next node is nullptr." << std::endl;
			}
			*/

			//	This will require setting a total of four next / prev pointers.
			//	newNode is located between previous and current node that the iterator is pointing to.
			//	newNode's next will be linked to current iter position.
			newNode->next = _iter.mCurr;
			//	newNode's previous will be linked to the previous iter position.
			newNode->prev = _iter.mCurr->prev;
			//	Forming the links back to the newNode.
			_iter.mCurr->prev->next = newNode;
			_iter.mCurr->prev = newNode;
			//	Update the iterator to the new node.
			_iter.mCurr = newNode;

			/*
			std::cout << "Head to Tail: " << std::endl;
			Node* currentNode = mHead;
			while (currentNode)
			{
				std::cout << currentNode->data;
				if (currentNode->next)
				{
					std::cout << " -> ";
				}
				currentNode = currentNode->next;
			}
			std::cout << '\n' << "Tail to Head: " << std::endl;

			Node* currentNodeRev = mTail;
			while (currentNodeRev)
			{
				std::cout << currentNodeRev->data;
				if (currentNodeRev->prev)
				{
					std::cout << " -> ";
				}
				currentNodeRev = currentNodeRev->prev;
			}
			std::cout << '\n' << std::endl;
			*/
			//	Update the size variable.
			mSize++;
			//	Return the updated iterator.
			return _iter;
		}
		//	In all cases, the passed - in Iterator should be updated to store the newly inserted node
	}

	Iterator Erase(Iterator& _iter) 
	{
		//	Do not be afraid to diagram this!
		//	Delete the node stored in the passed - in Iterator
		//	This will require some pointers to be adjusted before the deletion
		//	In most of these cases, a temporary pointer will be required
		//	There are four special cases for this method, depending on what the Iterator is storing
		//		Empty List
		//			Iterator will be storing a null pointer
		//			Since there is nothing to remove, the method can be exited
		//	If it's a Empty List or at the Head call the AddHead and Begin Methods.
		
		//	created the new node.
		Node* tempNodeErase;

		if (nullptr == _iter.mCurr)
		{

			return _iter;
		}

		//		Head
		//			Iterator will be storing a pointer to the head of the list
		//			Will need to update the head pointer
		else if (mHead == _iter.mCurr)
		{
			tempNodeErase = mHead;
			mHead = mHead->next;
			mHead->prev = nullptr;
			_iter.mCurr = mHead;
			delete tempNodeErase;			
			//	Update the size variable.
			mSize--;
			//	Return the updated iterator.
			return _iter;
		}

		//		Tail
		//			Iterator will be storing a pointer to the tail of the list
		//			Will need to update the tail pointer
		else if (mTail == _iter.mCurr)
		{
			tempNodeErase = mTail;
			mTail = mTail->prev;
			mTail->next = nullptr;
			_iter.mCurr = nullptr;
			delete tempNodeErase;			
			//	Update the size variable.
			mSize--;
			//	Return the updated iterator.
			return _iter;
		}

		//		Anywhere else
		//			Iterator is storing a pointer to another node
		//			This will require linking the nodes before and after the node to erase together
		//	In all cases, the passed - in Iterator should be updated to store the node after the erased node
		else 
		{
			tempNodeErase = _iter.mCurr;
			_iter.mCurr = _iter.mCurr->next;
			if (nullptr != _iter.mCurr->prev->prev)
			{
				_iter.mCurr->prev = _iter.mCurr->prev->prev;
			}
			_iter.mCurr->prev->next = _iter.mCurr;
			delete tempNodeErase;

			//	Update the size variable.
			mSize--;
			//	Return the updated iterator.
			return _iter;
		}
	}

	Iterator Begin() const 
	{
		//	Creates and returns an Iterator that points to the head node.
		Iterator beginIterator;
		beginIterator.mCurr = mHead;
		return beginIterator;
	}

	Iterator End() const 
	{
		// Creates and returns an Iterator that points to the Node after the last valid node in the list.
		Iterator endIterator;
		endIterator.mCurr = mTail->next;
		return endIterator;
	}
};
