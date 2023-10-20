/*
File:			BST.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		A binary search tree
Notes:			Property of Full Sail University 2310
*/

// Header protection
#pragma once

/************/
/* Includes */
/************/
#include <string>

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
#define LAB_7	1

// Individual unit test toggles
#define BST_CTOR								1
#define BST_NODE_CTOR							1
#define BST_PUSH_EMPTY							1
#define BST_PUSH_LEFT							1
#define BST_PUSH_RIGHT							1
#define BST_CLEAR								1
#define BST_DTOR								1
#define BST_CONTAINS_FOUND						1
#define BST_CONTAINS_NOTFOUND					1
#define BST_REMOVE_CASE0_ROOT					1
#define BST_REMOVE_CASE0_LEFT					1
#define BST_REMOVE_CASE0_RIGHT					1
#define BST_REMOVE_CASE1_ROOT_LEFT				1
#define BST_REMOVE_CASE1_ROOT_RIGHT				1
#define BST_REMOVE_CASE1_LEFT_LEFT				1
#define BST_REMOVE_CASE1_LEFT_RIGHT				1
#define BST_REMOVE_CASE1_RIGHT_LEFT				1
#define BST_REMOVE_CASE1_RIGHT_RIGHT			1
#define BST_REMOVE_CASE2_CASE0					1
#define BST_REMOVE_CASE2_CASE1					1
#define BST_REMOVE_CASE0						1
#define BST_REMOVE_CASE1						1
#define BST_REMOVE_CASE2						1
#define BST_REMOVE_NOT_FOUND					1
#define BST_IN_ORDER_TRAVERSAL					1
#define BST_ASSIGNMENT_OP						1
#define BST_COPY_CTOR							1


// Templated binary search tree
template<typename Type>
class BST {

	friend class UnitTests_Lab7;	// Giving access to test code

	struct Node {
		Type data;					
		Node* left, * right;		
		Node* parent;				

			Node(const Type& _data, Node* _parent = nullptr) {
				//	Set the data and parent to the passed-in values.
				//	Nodes always start out as leaf nodes.
				data = _data;												//	Intialized data to passed in value of _data.
				parent = _parent;											//	Intialized parent node to passed in value of _parent.
				left = nullptr;												//	Intialized left node to nullptr;
				right = nullptr;											//	Intialized right node to nullptr;
		}
	};

	// Data members
	// NOTE: All values set to -1 for unit test purposes
	Node* mRoot = reinterpret_cast<Node*>(-1);	

public:

	BST() {
		//	Set all data members to reflect that no nodes are currently allocated.
		mRoot = nullptr;				//	Intialized mRoot Node to nullptr.
	}

	~BST() {
		//	Free up the memory for all dynamically allocated nodes (There’s a method that does this).
		Clear();
	}

	BST(const BST& _copy) {
		//	Assigns all values to match those of the object passed in
		//	Deep copy the entire tree
		//		Use the recursive Copy method to duplicate the tree with a pre - order traversal
		//			Each recursive call to copy should create a single node by Pushing it
		//	Remember that data members are not automatically initialized in C++
		mRoot = nullptr;													//	Set the Root node to nullptr in preperation for copying.
		Copy(_copy.mRoot);													//	Use the recursive copy constructor to make a shallow copy.
	}

	BST& operator=(const BST& _assign) {
		//	Assigns all values to match those of the object passed in
		//	Clean up existing memory before the deep copy(There’s a method that does this)
		//	Deep copy the entire tree
		//		Use the recursive Copy method to duplicate the tree with a pre - order traversal
		//			Each recursive call to copy should create a single node by Pushing it
		if (this == &_assign) {												//	If this tree matches the passed in tree:
			return *this;													//		Return.
		}
		Clear();															//	Clear this tree using the clearn method to prepare for copy.

		Copy(_assign.mRoot);												//	Call the recursive copy helper function.
		return *this;														//	Return the new tree.
	}

private:
	// Recursive helper method for use with Rule of 3
	void Copy(const Node* _curr) {
		if (_curr == nullptr) {												//	If the current passed in node is nullptr:
			return;															//		Return.
		}
		Push(_curr->data);													//	Recursive call to Push method taking in the current node's data.
		Copy(_curr->left);													//	Recursive call to Copy to traverse the left branch.
		Copy(_curr->right);													//	Recursive call to Copy to traverse the right branch.
	}

public:

	void Clear() {
		//	Free up the memory for all dynamically allocated nodes
		//	Use a post - order traversal and delete one node at a time
		//	Set the root back to its default state
		Clear(mRoot);														//	Call the Clear method passing in mRoot node.
		mRoot = nullptr;													//	Set mRoot node back to nullptr.
	}

private:

	// Recursive helper method for use with Clear
	void Clear(Node* _curr) {												
		if (_curr == nullptr) {												//	If currrent passed in node is nullptr:
			return;															//		Then just return;
		}
		Clear(_curr->left);													//	Clear transverse to the farthest left node and clear it.
		Clear(_curr->right);												//	Clear transverse to the next right node.
		delete _curr;														//	Delete current node.
	}

public:

	void Push(const Type& _val) {
		//	Adds a value to the tree:
		//	Dynamically allocate a Node and place it in the correct position in the tree:
		//		Added nodes will always be leaf nodes.
		//	If there is already at least one node in the tree, you will need a temporary pointer to traverse 
		//		down the tree to the node you want to insert below.
		Node* currentNode = mRoot;											//	Created temp for current node intialized to mRoot.
		Node* parent = nullptr;												//	Created parent node initialized to nullptr;
		if (mRoot == nullptr) {												//	If no root node identified by root == nullptr:
			mRoot = new Node(_val);											//		Then make a new node storing the passed in value.
			return;															//	Return value.
		}																	//	Else if root node exists:
		while (currentNode != nullptr) {									//		Loop for as long as current does not equal nullptr.
			parent = currentNode;											//		Assigning the value of parent node to current node.
			if (_val < currentNode->data) 									//	If the value is less than the value of current then:
				currentNode = currentNode->left;							//		Current goes left.
			else															//	else:
				currentNode = currentNode->right;							//		Current goes right.
		}
		Node* newChildNode = new Node(_val, parent);						//	Make a new node taking in the passed in value of _val and parent which is the current node we're at.
		if (_val < parent->data)											//	If the value is less than the data in our current parent node:
			parent->left = newChildNode;									//		Create the new child node to the left of parent.
		else 																//	Else if the nost is larger than our parent's current value:
			parent->right = newChildNode;									//		Create the new child node to the right of the parent.
	}

	bool Contains(const Type& _val) {
		//	Checks to see if a value is present in the tree and returns true if found.
		//	Create a temporary pointer to traverse down the tree.
		Node* currentNode = mRoot;											//	Created temp for current node intialized to mRoot.
		while (currentNode != nullptr) {									//	Loop for as long as current does not equal nullptr.
			if (_val == currentNode->data)									//	If passed in value is equal to the current node's data:
				return true;												//		Return the current node;
			else if (_val < currentNode->data)								//	If the value is less than the value of current then:
				currentNode = currentNode->left;							//		Current goes left.
			else 															//	Else:
				currentNode = currentNode->right;							//		Current goes right.
		}
		return false;
	}

private:

	Node* FindNode(const Type& _val) {
		//	Checks to see if a value is present in the tree and returns the address if found.
		//	Create a temporary pointer to traverse down the tree.
		Node* currentNode = mRoot;											//	Created temp for current node intialized to mRoot.
		while (currentNode != nullptr) {									//	Loop for as long as current does not equal nullptr.
			if (_val == currentNode->data)									//	If passed in value is equal to the current node's data:
				return currentNode;											//		Return the current node data;
			else if (_val < currentNode->data)								//	If the value is less than the value of current then:
				currentNode = currentNode->left;							//		Current goes left.
			else 															//	Else:
				currentNode = currentNode->right;							//		Current goes right.
		}
		return nullptr;
	}

	void RemoveCase0(Node* _node) {
		//	Removes a node from the tree that has no children.
		//		Can assume the node passed in is a leaf node
		//	Three sub - cases
		//		Root node
		//		Is a left child
		//		Is a right child
		if (_node == mRoot)													//	If the node is equal to the mRoot node then:
			mRoot = nullptr;												//		Set mRoot back to nullptr.
		else if (_node == _node->parent->left)								//	Else if node is equal to the left child:
			_node->parent->left = nullptr;									//		Set that parent's left child to point to nullptr.
		else																//	Else if node is equal to the right child:
			_node->parent->right = nullptr;									//		Set that parent's right child to point to nullptr.
		delete _node;														//		Delete the node.
	}

	void RemoveCase1(Node* _node) {
		//	Removes a node from the tree that has one child:
		//		Can assume the node passed in has exactly one child.
		//	Six sub - cases:
		//		Root node with left child.
		//		Root node with right child.
		//		Left child that has a left child.
		//		Left child that has a right child.
		//		Right child that has a left child.
		//		Right child that has a right child.
		Node* parent = _node->parent;										//	Made a parent node of passed in node's parent. To simplify code making it more readable.
		Node* child = (_node->left) ? _node->left : _node->right;			//	Made new child node that is assigned to left child of parent but can also mean right child of parent.
																			//		if left doesn't exist. This allows me to write one method for two sub cases at a time.
		if (_node == mRoot) {												//	If the node is equal to the mRoot node then:
			mRoot = child;													//		Make the child mRoot.
			child->parent = nullptr;										//		Set the child parent pointer to nullptr.
		}
		else if (_node == parent->left) {									//	Else if node is equal to the left child:
			parent->left = child;											//		Reassign pointer for parent left to be child.
			child->parent = parent;											//		Reassign pointer for child's parent to be the parent.e.
		}
		else if (_node == parent->right) {									//	Else node is equal to the right child:
			parent->right = child;											//		Reassign pointer for parent right to be child.
			child->parent = parent;											//		Reassign pointer for child's parent to be the parent.
		}
		delete _node;														//		Delete the original node.
	}

	void RemoveCase2(Node* _node) {
		//	Removes a node from the tree that has both children
		//		Can assume the node passed in has both children
		//	This will ultimately lead to a Case0 or Case1 removal
		Node* replacementNode = _node->right;								//	A node variable to be used to replace the original passed in node's values and set to the right child initially.
		while (replacementNode->left != nullptr)							//	While the replacement node's left child isn't a value of nullptr:
			replacementNode = replacementNode->left;						//		Move the replacement node to the node's left child.
		_node->data = replacementNode->data;								//	Now that we're at the location of the lowest value of the left side replace the original data of the passed in node with this replacement node's value.
		if (replacementNode->left != nullptr) {								//	If the replacement node's left chlid exists:
			RemoveCase1(replacementNode);									//		Run the remove case 1 method on the left child.
		}
		else if (replacementNode->right != nullptr) {						//	If the replacement node's right child exists:
			RemoveCase1(replacementNode);									//		Run the remove case 1 method on the right child.
		}
		else {																//	Else if no child nodes exist then:
			RemoveCase0(replacementNode);									//		Run the remove case 0 method on the node.
		}
	}

public:

	bool Remove(const Type& _val) {
		//	Removes a node from the tree by calling the appropriate RemoveCase method
		//	Find the address of the node to be removed(There’s potentially a method for this)
		//	Check to see how many children that node has, and call the appropriate RemoveCase method
		//	Return true, if something was removed
		Node* nodeToBeRemoved = FindNode(_val);								//	Made a temp variable to store the node to be removed.
		bool isRemoved = false;												//	Made a bool variable to store if the node had has been removed successfully or not.
		if (nodeToBeRemoved != nullptr) {									//	If nodeToBeRemoved exists:
			Node* childLeft = nodeToBeRemoved->left;						//		Assign node variable for left child of parent.
			Node* childRight = nodeToBeRemoved->right;						//		Assign node variable for right child of parent.
			if (childLeft && childRight) {									//	If there are two child nodes:
				RemoveCase2(nodeToBeRemoved);								//		Use remove case 2.
				isRemoved = true;											//		Update the is removed variable to true if successful.
			}
			else if (childLeft || childRight) {								//	Else if there is only one child node:
				RemoveCase1(nodeToBeRemoved);								//		Use remove case 1.
				isRemoved = true;											//		Update the is removed variable to true if successful.
			}
			else {															//	Else in all other cases: (no child nodes)
				RemoveCase0(nodeToBeRemoved);								//		Use remove case 0.
				isRemoved = true;											//		Update the is removed variable to true if successful.
			}
		}
		return isRemoved;													//	Return if something was removed or not.
	}

	std::string InOrder() {
		//	Creates a space-delimited string that contains the values of the tree in ascending order
		//	Start with the root and use the recursive InOrder method to build out the string one value at a time
		//	Use std::tostring to convert the int into its string equivalent
		std::string treeOutputInOrder;										//	String to hold the output that I will return.
		InOrder(mRoot, treeOutputInOrder);									//	Call the recusive fuction taking in the beginning of the tree or it's root and the string we'll be storing the values in.
		if (!treeOutputInOrder.empty() && treeOutputInOrder.back() == ' ')	//	If the string is not empty and has a back value of an empty space:
			treeOutputInOrder.pop_back();									//		Then pop (delete) the space on the back.
		return treeOutputInOrder;											//	Return the string.
	}

private:

	// Recursive helper method to help with InOrder
	void InOrder(Node* _curr, std::string& _str) {
		if (_curr == nullptr)												//	If the node does not exist:
			return;															//		Return.
		InOrder(_curr->left, _str);											//	Recursive to traverse the left side of the tree for string values.
		_str += std::to_string(_curr->data) + ' ';							//	Add the current nodes data as string values to the string.
		InOrder(_curr->right, _str);										//	Recursive to traverse the right side of the tree for string values.
	}
};

