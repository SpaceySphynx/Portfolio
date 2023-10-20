/*
File:			DSA_Lab6.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Purpose:		Usage of the std::unordered_map class
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
#define LAB_6	1

// Individual unit test toggles
#define LAB6_POPULATE_LETTER_VALUES	1
#define LAB6_GET_LETTER_VALUE		1
#define LAB6_GET_WORD_VALUE			1
#define LAB6_CREATE_PAIR			1
#define LAB6_LOAD_FILE				1
#define LAB6_FIND_WORD_SCORE		1

/************/
/* Includes */
/************/
#include <string>
#include <fstream>
#include <unordered_map>

class DSA_Lab6 {

	friend class UnitTests_Lab6;	// Giving access to test code

	// Data members
	int mLetterValues[26] = { -1 };
	std::unordered_map<std::string, int> mScrabbleMap;

public:

	void PopulateLetterValues(const int* _letterValues) {
		//	Copy the values of the passed-in array into the mLetterValues data member.
		//		Since the methods are explicitly written for scrabble, you can assume that this is an array of 26 elements.
		for (int i = 0; i < 26; ++i) {						//	Loop through assuming there are 26 elements.
			mLetterValues[i] = _letterValues[i];			//	Assign the index of mLetterValues to the index of the passed in _letterValues.
		}
	}

	int GetLetterValue(char _letter) const {
		//	The parameter received will always be an upper - case letter.
		//		Will need to offset this into the array element range and return that value from the array.
		int valueASCII = _letter - 'A';						//	Created a varaible to store the ASCII value of a upper case value.
		return mLetterValues[valueASCII];					//	Returns the value of a particular letter.
	}

	int GetWordValue(const std::string& _word) const {
		int valueOfWord = 0;								//	Created a variable to hold the value of the word to return.
		for (int i = 0; i < _word.size(); i++) {			//	Loop through the word based on size of the word.
															//	Use a previous method to help calculate this.
			valueOfWord += GetLetterValue(_word[i]);		//	Added to the value of the total word using the Method I made to to get the value of each letter.
		}
		return valueOfWord;									//	Returns the total value for a word.
	}

	std::pair<std::string, int> CreatePair(const std::string& _word) const {
		return std::make_pair(_word, GetWordValue(_word));	//	Creates and returns an std::pair with the word as the key, and the total for that word as the value.
	}

	void LoadWords(const char* _filename) {
		//	The string passed in contains the name of a text file that contains all of the words for Scrabble.
		//		There is one word per line, and each word is already in all upper - case letters.
		std::ifstream importedFile;							//	Create the file variable for interacting with the imported file.
		importedFile.open(_filename);						//	Open the imported file.
		std::string currentLine;							//	String variable for the current file line.
		//	Read each word in the file, and create a pair that stores the word and its score.
		//	Add each pair to the unordered_map data member.
		while (std::getline(importedFile, currentLine)) {	//	While loop that will getline of importedFile as a string.
			auto wordPair = CreatePair(currentLine);		//	Auto variable for the pair I created based on the current line string.
			mScrabbleMap.insert(wordPair);					//	Insert the word pair into the map.
		}
		importedFile.close();								//	Close file.
	}

	int FindValueInMap(const std::string& _word) {
		//	Finds a word in the map and returns the value associated with it.
		//	Use the find method of the unordered_map to ensure O(1) complexity.
		auto scrabbleMapIterator = mScrabbleMap.find(_word);//	Auto variable for map iterator. 
		if (scrabbleMapIterator != mScrabbleMap.end())		//	if map iterator doens't equal the end of the map.
			return(scrabbleMapIterator->second);			//	return the value of where the map iterator is pointing.
		else
			return -1;										//	If the word is not found, return -1.
	}
};
