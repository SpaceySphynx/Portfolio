#include "TriangleStack.h"

// Default constructor initializes base and height to zero.
TriangleStack::TriangleStack() : mBase(0), mHeight(0) 
{

}

// Sets the base of the triangle.
void TriangleStack::SetBase(float base) 
{
    mBase = base;
}

// Sets the height of the triangle.
void TriangleStack::SetHeight(float height) 
{
    mHeight = height;
}

// Calculates and returns the area of the triangle.
float TriangleStack::GetArea() const 
{
    return mBase * mHeight / 2.0f;
}