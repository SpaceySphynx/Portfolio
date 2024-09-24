#pragma once

// Struct Definitions

// Float vector (x, y, z, w).
struct Float4
{
    union
    {
        struct
        {
            float Vect[4]; // Array of the four floats.
        };
        struct
        {
            float x;
            float y;
            float z;
            float w;
        };
    };
};

// 4x4 matrix of 16 floats for matrix math. 
struct Matrix4x4
{
    union
    {
        struct
        {
            float Vect[16];
        };
        struct
        {
            float xx, xy, xz, xw;  // First row of the matrix.
            float yx, yy, yz, yw;  // Second row of the matrix.
            float zx, zy, zz, zw;  // Third row of the matrix.
            float wx, wy, wz, ww;  // Fourth row of the matrix.
        };
        struct
        {
            Float4 AxisX;  // X axis.
            Float4 AxisY;  // Y axis.
            Float4 AxisZ;  // Z axis.
            Float4 AxisW;  // W axix for translations.
        };
    };

    // Constructor initializes the matrix to the identity matrix. 
    Matrix4x4()
    {
        AxisX = Float4{ 1, 0, 0, 0 };
        AxisY = Float4{ 0, 1, 0, 0 };
        AxisZ = Float4{ 0, 0, 1, 0 };
        AxisW = Float4{ 0, 0, 0, 1 };
    }
};

// Represents a vertex with position and color
struct VERTEX
{
    float xyzw[4];
    unsigned int color;
};

// Cube vertices
VERTEX vertices[8] =
{
    { {-0.25f,  0.25f, -0.25f, 1.0f}, 0xFFFFFFFF }, // back-top-left.
    { { 0.25f,  0.25f, -0.25f, 1.0f}, 0xFFFFFFFF }, // back-top-right.
    { {-0.25f, -0.25f, -0.25f, 1.0f}, 0xFFFFFFFF }, // back-bottom-left.
    { { 0.25f, -0.25f, -0.25f, 1.0f}, 0xFFFFFFFF }, // back-bottom-right.
    { {-0.25f,  0.25f,  0.25f, 1.0f}, 0xFFFFFFFF }, // front-top-left.
    { { 0.25f,  0.25f,  0.25f, 1.0f}, 0xFFFFFFFF }, // front-top-right.
    { {-0.25f, -0.25f,  0.25f, 1.0f}, 0xFFFFFFFF }, // front-bottom-left.
    { { 0.25f, -0.25f,  0.25f, 1.0f}, 0xFFFFFFFF }  // front-bottom-right.
};

// Matrices
Matrix4x4 gridWorldMatrix;        // World transformation matrix for the grid.
Matrix4x4 cubeWorldMatrix;        // World transformation matrix for the cube.
Matrix4x4 viewMatrix;             // View transformation matrix (camera).
Matrix4x4 projectionMatrix;       // Projection matrix for 3D to 2D conversion.

// Screen Variables
unsigned int width = 500;         // Screen width.
unsigned int height = 500;        // Screen height.
unsigned int totalPixels = height * width;  // Total number of pixels.

// Color definitions in ARGB
unsigned int black = 0x00000000;
unsigned int white = 0xFFFFFFFF;
unsigned int red = 0xFFFF0000;
unsigned int green = 0xFF00FF00;
unsigned int blue = 0xFF0000FF;
unsigned int yellow = 0xFFFFFF00;
unsigned int pink = 0xFFFF00FF;
unsigned int cyan = 0xFF00FFFF;

unsigned int* backBuffer = nullptr;  // Pointer to the 1D array of pixels for the screen.
unsigned int bufferColor = black;    // Background color set to black.

// Screen center
unsigned int centerX = width / 2;
unsigned int centerY = height / 2;

// Math and timing variables
float pi = 3.14159265359;               // Pi constant for trigonometric calculations
float timeSinceLastFrame = 0.0f;        // Time accumulator for frame updates
const float frameTime = 1.0f / 30.0f;   // Time per frame (for 30 FPS)

// Camera and rendering
float aspectRatio = float(width) / float(height); // Aspect ratio.
float zNear = 0.1f;                               // Near clipping plane distance.
float zFar = 10.0f;                               // Far clipping plane distance.
const float targetFPS = 60.0f;                    // Target frames per second.
float currentRotation = 0.0f;                     // To store Rotation angle of the cube in degrees.
float rotationSpeed = 60.0f;                      // Speed of cube rotation (degrees per second).
float timer = 0.0f;                               // Tiner to store accumulation of framees.