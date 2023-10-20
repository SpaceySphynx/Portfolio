#include "Inventory.h"

void Inventory::CreateItem()
{
    std::string name = "Item " + std::to_string(m_ItemsMade);
    m_Items.push_back(new Item(name.c_str(), 100 * m_ItemsMade));
    ++m_ItemsMade;
}

Inventory::Inventory()
{
    CreateItem();
    CreateItem();
    CreateItem();
}

// Added destructor
Inventory::~Inventory()
{
    for (auto item : m_Items) {
        delete item;
    }
}

void Inventory::Print() const
{
    size_t* nSize = new size_t(m_Items.size());
    std::cout << "_____INVENTORY_____\n";
    for (unsigned int i = 0; i < *nSize; ++i)
    {
        m_Items[i]->Print();
    }
    // Added delete nSize which was missing
    delete nSize;
}