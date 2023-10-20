#include "Item.h"
#include <iostream>

Item::Item(const char* _name, int _value)
{
	m_Name = _name;
	m_Value = new int(_value);
	// removed duplicate code m_Value = new int(_value);
}

// Added deconstructor
Item::~Item()
{
	delete m_Value;
}

void Item::Print() const
{
	int* value = new int(GetValue());
	std::cout << m_Name << "\t" << *value << std::endl;
	// Added delete value
	delete value;
}