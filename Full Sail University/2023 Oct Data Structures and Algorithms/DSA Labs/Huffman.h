/*
File:			Huffman.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		A class to wrap up Huffman compression algorithm
Notes:			Property of Full Sail University 2310
*/

// Header protection
#pragma once

/************/
/* Includes */
/************/
#include <queue>
#include "BitStream.h"
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
#define LAB_8	1

// Individual unit test toggles
#define HUFFMAN_CTOR					1
#define HUFFMAN_GENERATE_FREQUENCY		1
#define HUFFMAN_GENERATE_LEAFLIST		1
#define HUFFMAN_GENERATE_TREE			1
#define HUFFMAN_CLEAR_TREE				1
#define HUFFMAN_DTOR					1
#define HUFFMAN_GENERATE_ENCODING		1
#define HUFFMAN_COMPRESS				1
#define HUFFMAN_DECOMPRESS				1

// Optional unit tests for debugging with small file containing "HELLO WORLD"
#define HUFFMAN_DEBUG_COMPRESS			0
#define HUFFMAN_DEBUG_DECOMPRESS		0

// Wraps up Huffman compression algorithm
class Huffman {

	friend class UnitTests_Lab8; // Giving access to test code

	// A node for a a Huffman tree
	struct HuffNode {
		short value;		 
		unsigned int freq;	
		HuffNode* left;		
		HuffNode* right;	
		HuffNode* parent;	

		HuffNode(short _value, unsigned int _freq, HuffNode* _left = nullptr, HuffNode* _right = nullptr, HuffNode* _parent = nullptr)
			: value(_value), freq(_freq), left(_left), right(_right), parent(_parent) {
		}

		HuffNode(const HuffNode& _hnode)
			: value(_hnode.value), freq(_hnode.freq), left(_hnode.left), right(_hnode.right), parent(_hnode.parent) {
		}
	};

	struct HuffCompare {
		bool operator() (const HuffNode* _a, const HuffNode* _b) {
			return(_a->freq > _b->freq);
		}
	};


	// Data members
	// NOTE: Values set to 1/-1 for unit test purposes
	std::string mFileName = "-1";						
	unsigned int mFrequencyTable[256] = { 1 };			
	std::vector<HuffNode*> mLeafList;					
	HuffNode* mRoot = reinterpret_cast<HuffNode*>(-1);	
	std::vector<bool> mEncodingTable[256];				


	Huffman(const std::string& _fileName) {
		//	Assign the appropriate data member the value from the parameter.
		//	Zero out the entire frequency table.
		//	Set the root to a value that indicates the tree is currently empty.
		mFileName = _fileName;															//	Setting mFileName variable to the passed in variable.
		for (int i = 0; i < 256; ++i) {													//	For loop to go through 0 to 255 of the mFrequencyTable:
			mFrequencyTable[i] = 0;														//		Set all the values to 0 in the table.
		}
		mRoot = nullptr;																//	Set the root node to nullptr.

	}

	~Huffman() {
		//	Clean up all of the dynamically allocated memory (There’s a method to help with this).
		ClearTree();
	}


	void GenerateFrequencyTable() {
		//	Open the file in binary mode, using a std::ifstream.
		//	Read the file one byte at a time, and increment the corresponding index:
		//		The indices of the frequency table line up with the ASCII values.
		//	Close the file when complete.
		std::ifstream file(mFileName, std::ios::binary);								//	Open the file in binary.
		if (!file.is_open()) {
			std::cerr << "File Failed to Open" << std::endl;							//	Error handling for a file that failed to open.
			return;
		}																				
		char oneByte;																	//	Make a char to store the single byte of info.
		while (file.read(&oneByte, 1)) {												//	While loop to read the file to the end one byte at a time and store the oneByte variable.
			unsigned char convertToUnsignedChar = (unsigned char)(oneByte);				//		Convert char from signed to unsigned since the values are more than 127 posative. 
			++mFrequencyTable[convertToUnsignedChar];									//		Assign the value and increment the frequency table.
		}
		file.close();																	//	Close the file.
	}

	void GenerateLeafList() {
		//	Iterate through the frequency table and dynamically create a leaf node for each non-0 frequency.
		//	Add each node to the mLeafList vector.

		for (int i = 0; i < 256; ++i ) {												//	For loop to iterate throught he frequency table for the 256 spots and:
			if (mFrequencyTable[i] != 0) {												//		For all non-0 frequency values:
				HuffNode* makeANewNode = new HuffNode(i, mFrequencyTable[i]);			//			Make a new node.
				mLeafList.push_back(makeANewNode);										//			Add each of these nodes into the mLeafList vector using push back.
			}
		}
	}

	void GenerateTree() {
		//	Create the priority_queue:
		//		This will be storing HuffNode* in a vector, and uses HuffCompare for the comparator.
		//	Populate the priority_queue with the data in the leaf list.
		//	Generate the tree with the following algorithm:
		//		While the queue has more than 1 node:
		//			Store the top two nodes into some temporary pointers and pop them.
		//			Create a new parent node with first node as the left child, and second node as the right child.
		//			Set the parent’s value to - 1, and the frequency to the sum of its two children’s frequencies.
		//			Set the first and second nodes’ parent to the newly created node.
		//			Insert the new node into the queue.
		//	Set the root data member:
		//		There is only one node in the queue.
		std::priority_queue<HuffNode*, std::vector<HuffNode*>, HuffCompare> priority;	//	Use the priority queue function we learned in lecture taking in HuffNode Pointer type, vector of HuffNode pointers and HuffCompare comparator.
		for (HuffNode* eachNode : mLeafList) {											//	For each node of the mLeafList:
			priority.push(eachNode);													//		Push the information into the priorty list.
		}
		while (priority.size() > 1) {													//	While size of prioroty queue nodes are greater than 1:
			HuffNode* firstChild = priority.top(); priority.pop();						//		Created a first child node variable and assigned top of the stack then deleted it.
			HuffNode* secondChild = priority.top(); priority.pop();						//		Created a second chlid node variable and assigned the new new top of the stack then deleted it.
			HuffNode* parentNode = new HuffNode
				(-1, firstChild->freq + secondChild->freq, firstChild, secondChild);	//	Created a parent node variable and intialized it to -1, sum of both frequencies, and first and second child.
			firstChild->parent = parentNode;											//		Assigned pointer for first child node's parent to the parent node. 
			secondChild->parent = parentNode;											//		Assigned pointer for second chlid node's parent to the parent node.
			priority.push(parentNode);													//		Pushed the new node into the queue.
		}
		if (!priority.empty()) {														//	If the queue isn't emtpy:
			mRoot = priority.top();														//		Assign the root to the top of the stack of the priority queue.
		}
	}

	void GenerateEncodingTable() {
		//	Go through all of the leaf nodes and generate the bit codes.
		//	This is done by traversing up the tree from each leaf node with a temporary pointer, and storing the direction in the corresponding vector:
		//		Each index of the encoding table aligns to an ASCII value.
		//	As you move up, push a 0 to the vector if you passed through a left child connection, and a 1 if you passed through a right connection.
		//	Once you hit the root node, reverse the values in the vector.
		for (HuffNode* leafNode : mLeafList) {											//	For each node of the mLeafList:
			std::vector<bool> encoding;													//		Intialized a vector of bool I called encoding.
			HuffNode* currentNode = leafNode;											//		Created a new node and assigned to leafNode.
			while (currentNode->parent != nullptr) {									//		While the currentNode's parent is not equal to null pointer:
				if (currentNode->parent->left == currentNode)							//			If that the current node is the left node of the parent:
					encoding.push_back(0);												//				Push back 0.
				else																	//			Else:
					encoding.push_back(1);												//				Push back 1.
				currentNode = currentNode->parent;										//			Move the current node's parent the current node.
			}
			std::reverse(encoding.begin(), encoding.end());								//		Reverse the encoded list.
			mEncodingTable[static_cast<unsigned char>(leafNode->value)] = encoding;		//		Save the newly created and reversed list into the mEncodingTable.
		}
	}

	void ClearTree() {
		//	Perform a post-order traversal to delete all of the nodes:
		//		Same as Clear from the BST.
		ClearTree(mRoot);																//	Call the Clear method passing in mRoot node.
		mRoot = nullptr;																//	Set mRoot node back to nullptr.
	}

	void ClearTree(HuffNode* _curr) {
		if (_curr == nullptr) {															//	If currrent passed in node is nullptr:
			return;																		//		Then just return;
		}
		ClearTree(_curr->left);															//	Clear transverse to the farthest left node and clear it.
		ClearTree(_curr->right);														//	Clear transverse to the next right node.
		delete _curr;																	//	Delete current node.
	
	}

	void Compress(const char* _outputFile) {
		//	In this method, mFileName is the file to compress, and the parameter is the name of the file to write to.
		//		Create the frequency table, leaf list, tree, and encoding table by calling the existing methods(in this order).
		//		Create a BitOfstream and supply it the Huffman header.
		//		Open the input file in binary mode with a std::ifstream.
		//		Compress the file:
		//			For each byte in the original file, write out the corresponding bit - code from the encoding table.
		//		Close both streams.

		GenerateFrequencyTable();														//	Called method to generate the frequency table.
		GenerateLeafList();																//	Called method to generate the leaf list.
		GenerateTree();																	//	Called method to generate the huffman tree.
		GenerateEncodingTable();														//	Called method to generate the encoding table.

		BitOfstream bitOut(_outputFile, reinterpret_cast<const char*>(mFrequencyTable), 256 * sizeof(unsigned int));	//	BitOfstream to take in the Huffman header of the file. 
		std::ifstream file(mFileName, std::ios::binary);								//	Open the file in binary for reading.
		if (!file.is_open()) {															//	If the file does not open:
			std::cerr << "File Failed to Open" << std::endl;							//		Error handling for a file that failed to open message to visual studio debugger.
			return;																		//		Then return.
		}

		char oneByte;																	//	Make a char to store the single byte of info.
		while (file.read(&oneByte, 1)) {												//	While loop to read the file to the end one byte at a time and store the oneByte variable.
			unsigned char convertToUnsignedChar = (unsigned char)(oneByte);				//		Convert char from signed to unsigned since the values are more than 127 posative. 
			std::vector<bool>& encoding = mEncodingTable[convertToUnsignedChar];		//		Used a vector of bools called encoding to take in the encoding table values.
			bitOut << encoding;															//		Send the bool vector to bitOut.
		}
		
		file.close();																	//	Close the ifStream file.
		bitOut.Close();																	//	Close the bitOut file.
	}

	void Decompress(const char* _outputFile) {
		//	In this method, mFileName is the file to decompress, and the parameter is the name of the file to write to.
		//		Create a BitIfstream and read the frequency table.
		//		Create the leaf list and tree by calling the existing methods(in this order).
		//		Create a std::ofstream for output in binary mode.
		
		//		Create a bool to use for traversing down the tree, and an unsigned char for writing to the file.
		//		Create a HuffNode pointer for use in traversing the tree(start at the top).
		//		Go through the compressed file one bit at a time, moving the temporary pointer down the tree:
		//			When a leaf node is reached, write the value to the uncompressed file, and go back to the root:
		//				This will need to be done a number of times equal to the total frequency of the original file.
		//	Close both streams.
		BitIfstream bitIn(mFileName.c_str(), reinterpret_cast<char*>(mFrequencyTable), 256 * sizeof(unsigned int));	//	BitIfstream to take in the Huffman header of the file. 
		GenerateLeafList();																//	Called method to generate the leaf list.
		GenerateTree();																	//	Called method to generate the huffman tree.
		std::ofstream outputFile(_outputFile, std::ios::binary);							//	Open the file in binary for writing.
		if (!outputFile.is_open()) {														//	If the file does not open:
			std::cerr << "File Failed to Open" << std::endl;							//		Error handling for a file that failed to open message to visual studio debugger.
			return;																		//		Then return.
		}
		bool bitForTreeTravel;															//	Bool for traversing the tree. 
		HuffNode* currentNode = mRoot;													//	Assigned root node to the current node.
		unsigned int totalFileChars = 0;												//	Int variable for tracking hte Char characters from the FrequencyTable.
		for (int i = 0; i < 256; ++i) {													//	For loop to run through the entire Frequency table:
			totalFileChars += mFrequencyTable[i];										//		Store the count in the totalFileCharacter variable.
		}
		for (unsigned int i = 0; i < totalFileChars;) {									//	For loop to travel the tree and decompress and loops for long as the it takes to meet the character for the file.
			bitIn >> bitForTreeTravel;													//		To read the left and right 0 or 1 for traversing the compressed file.
			currentNode = bitForTreeTravel ? currentNode->right : currentNode->left;	//		A bool condition to go right of left based on the current 0 or 1 map. 
			if (currentNode->left == nullptr && currentNode->right == nullptr) {		//		If the left child is empty and the right child is empty then we've made it to a leaf node and:
				outputFile.put(static_cast<char>(currentNode->value));					//			Write the current node's value to the output file.
				currentNode = mRoot;													//			Assign this node the value of mRoot.
				i++;																	//			Increament the index variable.
			}
		}
		outputFile.close();																//	Close the output file.
		bitIn.Close();																	//	Close the bitIn file.
	}
};

