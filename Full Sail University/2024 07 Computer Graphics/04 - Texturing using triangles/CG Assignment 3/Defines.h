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
            // Four component variables of the array.
            float x;
            float y;
            float z;
            float w;
        };
    };
    // Constructor to initialize the components.
    Float4(float xVal = 0.0f, float yVal = 0.0f, float zVal = 0.0f, float wVal = 0.0f)
        : x(xVal), y(yVal), z(zVal), w(wVal)
    {}
};

// 4x4 matrix of 16 floats for matrix math. 
struct Matrix4x4
{
    union
    {
        struct
        {
            float Vect[16]; // Array to hold the 16 variable matrix.
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

    // Constructor to initializes the matrix to the identity matrix. 
    Matrix4x4()
        : AxisX(1.0f, 0.0f, 0.0f, 0.0f),
        AxisY(0.0f, 1.0f, 0.0f, 0.0f),
        AxisZ(0.0f, 0.0f, 1.0f, 0.0f),
        AxisW(0.0f, 0.0f, 0.0f, 1.0f)
    {}
};

// Represents a vertex with position and color.
struct VERTEX
{
    float xyzw[4];
    unsigned int color = 0xFFFFFFFF;
    float uv[2];
};

// Cube vertices
VERTEX vertices[8] = 
{
    {{-0.25f,  0.25f, -0.25f, 1.0f}, 0xFFFFFFFF, {0.0f, 0.0f}}, // back-top-left.
    {{ 0.25f,  0.25f, -0.25f, 1.0f}, 0xFFFFFFFF, {1.0f, 0.0f}}, // back-top-right.
    {{-0.25f, -0.25f, -0.25f, 1.0f}, 0xFFFFFFFF, {0.0f, 1.0f}}, // back-bottom-left.
    {{ 0.25f, -0.25f, -0.25f, 1.0f}, 0xFFFFFFFF, {1.0f, 1.0f}}, // back-bottom-right.
    {{-0.25f,  0.25f,  0.25f, 1.0f}, 0xFFFFFFFF, {0.0f, 0.0f}}, // front-top-left.
    {{ 0.25f,  0.25f,  0.25f, 1.0f}, 0xFFFFFFFF, {1.0f, 0.0f}}, // front-top-right.
    {{-0.25f, -0.25f,  0.25f, 1.0f}, 0xFFFFFFFF, {0.0f, 1.0f}}, // front-bottom-left.
    {{ 0.25f, -0.25f,  0.25f, 1.0f}, 0xFFFFFFFF, {1.0f, 1.0f}}  // front-bottom-right.
};

// Matrices.
Matrix4x4 gridWorldMatrix;        // World transformation matrix for the grid.
Matrix4x4 cubeWorldMatrix;        // World transformation matrix for the cube.
Matrix4x4 viewMatrix;             // View transformation matrix (camera).
Matrix4x4 projectionMatrix;       // Projection matrix for 3D to 2D conversion.

// UV texture coordinates. 
float uvFront[4][2] = { {1.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f} };
float uvBack[4][2] = { {0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f} };
float uvTop[4][2] = { {0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f} };
float uvBottom[4][2] = { {0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f} };
float uvLeft[4][2] = { {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 1.0f} };
float uvRight[4][2] = { {0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 0.0f}, {1.0f, 1.0f} };

// Color definitions in ARGB.
const unsigned int black = 0x00000000;
const unsigned int white = 0xFFFFFFFF;
const unsigned int red = 0xFFFF0000;
const unsigned int green = 0xFF00FF00;
const unsigned int blue = 0xFF0000FF;
const unsigned int yellow = 0xFFFFFF00;
const unsigned int pink = 0xFFFF00FF;
const unsigned int cyan = 0xFF00FFFF;

// Assigning the default color for each face.
const unsigned int frontFaceColor = green;
const unsigned int rightFaceColor = cyan;
const unsigned int backFaceColor = red;
const unsigned int leftFaceColor = pink;
const unsigned int bottomFaceColor = yellow;
const unsigned int topFaceColor = blue; 

// Screen Variables.
const unsigned int width = 900;         // Screen width.
const unsigned int height = 500;        // Screen height.
size_t totalPixels = static_cast<size_t>(width) * static_cast<size_t>(height);  // Total number of pixels.

// Buffers.
unsigned int* backBuffer = nullptr;     // Pointer to the 1D array of pixels for the screen.
unsigned int bufferColor = black;       // Background color set to black.
float* depthBuffer = nullptr;           // Intialize the depthBuffer.

// Math variables.
const float pi = 3.1415927f;            // Pi constant for trigonometric calculations

// Camera, rendering and timing.
const float aspectRatio = static_cast<float>(height) / static_cast<float>(width);
const float zNear = 0.1f;                // Near clipping plane distance.
const float zFar = 10.0f;                // Far clipping plane distance.
const float targetFPS = 60.0f;           // Target frames per second.
float currentRotation = 0.0f;            // To store Rotation angle of the cube in degrees.
float rotationSpeed = 60.0f;             // Speed of cube rotation (degrees per second).
float timer = 0.0f;                      // Timer to store accumulation of framees.