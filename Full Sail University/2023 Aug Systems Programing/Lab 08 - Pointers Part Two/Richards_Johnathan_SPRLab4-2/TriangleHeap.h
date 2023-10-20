#pragma once

// Class represents a triangle stored on the heap.
class TriangleHeap 
{
private:
    float* mBase;    // Dynamic pointer to the base of the triangle
    float* mHeight;  // Dynamic pointer to the height of the triangle

public:
    // Rule of 3
    TriangleHeap();                           // Default constructor
    TriangleHeap(const TriangleHeap& other);  // Copy constructor
    ~TriangleHeap();                          // Destructor

    // Sets the base of the triangle.
    void SetBase(float base);

    // Sets the height of the triangle.
    void SetHeight(float height);

    // Returns the area of the triangle.
    float GetArea() const;

    // Overloads the assignment operator for deep copy.
    TriangleHeap& operator=(const TriangleHeap& other);
};

