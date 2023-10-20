#pragma once

// Class representing a triangle on the stack
class TriangleStack 
{
private:
    float mBase;    // Base of the triangle
    float mHeight;  // Height of the triangle

public:
    TriangleStack();  // Default constructor

    // Sets the base of the triangle.
    void SetBase(float base);

    // Sets the height of the triangle.
    void SetHeight(float height);

    // Returns the area of the triangle.
    float GetArea() const;
};
