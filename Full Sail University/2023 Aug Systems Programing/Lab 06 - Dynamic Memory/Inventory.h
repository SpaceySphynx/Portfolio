// Both the header and class cpp were in one file. I split it into two files.
#pragma once
#include "Item.h"
#include <vector>
#include <iostream>
#include <string>

class Inventory
{
	std::vector<Item*> m_Items;
	static unsigned int m_ItemsMade;

	void CreateItem();

public:
	Inventory();
	~Inventory();
	void Print() const;
};