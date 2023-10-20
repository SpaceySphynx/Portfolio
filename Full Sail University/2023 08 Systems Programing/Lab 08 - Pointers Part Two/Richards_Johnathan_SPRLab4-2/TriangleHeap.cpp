#include "TriangleHeap.h"

// Default constructor
TriangleHeap::TriangleHeap() : mBase(new float(0)), mHeight(new float(0)) 
{

}

// Copy constructor
TriangleHeap::TriangleHeap(const TriangleHeap& other) 
{
    mBase = new float(*other.mBase);
    mHeight = new float(*other.mHeight);
}

// Destructor
TriangleHeap::~TriangleHeap() 
{
    delete mBase;
    delete mHeight;
}

// Sets the base of the triangle.
void TriangleHeap::SetBase(float base) 
{
    *mBase = base;
}

// Sets the height of the triangle.
void TriangleHeap::SetHeight(float height) 
{
    *mHeight = height;
}

// Calculates and returns the area of the triangle.
float TriangleHeap::GetArea() const 
{
    return (*mBase) * (*mHeight) / 2.0f;
}

// Copy assignment operator
TriangleHeap& TriangleHeap::operator=(const TriangleHeap& other) 
{
    if (this == &other) return *this;  // Check for self-assignment

    // Copy the values from the other triangle
    *mBase = *other.mBase;
    *mHeight = *other.mHeight;

    return *this;
}
