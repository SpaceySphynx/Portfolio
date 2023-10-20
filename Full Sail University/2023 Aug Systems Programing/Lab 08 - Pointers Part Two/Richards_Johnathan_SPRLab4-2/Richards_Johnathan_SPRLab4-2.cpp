// Richards_Johnathan_SPRLab4-2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "TriangleStack.h"
#include "TriangleHeap.h"

// Function Prototypes
int AddNumbersReturnInt(int* a, int* b);
void AddNumbersReturnVoid(int a, int b, int* sum);
void SwapValues(int* a, int* b);

int main() 
{
    // include memory leak detection ( needs to be at top of main )
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetBreakAlloc(-1); // set block of memory to find memory leak
    _CrtDumpMemoryLeaks();

    // Creating two TriangleStack objects and setting their properties.
    TriangleStack triangle1, triangle2;
    triangle1.SetBase(5.0f);
    triangle1.SetHeight(6.0f);

    triangle2.SetBase(7.0f);
    triangle2.SetHeight(8.0f);

    // Storing the TriangleStack objects in a vector.
    std::vector<TriangleStack> triangleStacks;
    triangleStacks.push_back(triangle1);
    triangleStacks.push_back(triangle2);

    // Displaying the areas of the TriangleStack objects.
    for (const auto& triangle : triangleStacks) 
    {
        std::cout << "Area of TriangleStack: " << triangle.GetArea() << std::endl;
    }

    // Creating two TriangleHeap objects and setting default values.
    TriangleHeap triangleHeap1, triangleHeap2;
    triangleHeap1.SetBase(9.0f);
    triangleHeap1.SetHeight(10.0f);

    triangleHeap2.SetBase(11.0f);
    triangleHeap2.SetHeight(12.0f);

    std::vector<TriangleHeap> triangleHeaps;
    triangleHeaps.push_back(triangleHeap1);
    triangleHeaps.push_back(triangleHeap2);

    // Displaying the areas of the TriangleHeap objects to console.
    for (const auto& triangle : triangleHeaps) 
    {
        std::cout << "Area of TriangleHeap: " << triangle.GetArea() << std::endl;
    }

    return 0;
}

// Returns the sum of the integers pointed to by 'a' and 'b'.
int AddNumbersReturnInt(int* a, int* b)
{
    return *a + *b;
}

// Stores the sum of integers 'a' and 'b' into the memory pointed by 'sum'.
void AddNumbersReturnVoid(int a, int b, int* sum)
{
    *sum = a + b;
}

// Swaps the values of the integers pointed to by 'a' and 'b'.
void SwapValues(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}