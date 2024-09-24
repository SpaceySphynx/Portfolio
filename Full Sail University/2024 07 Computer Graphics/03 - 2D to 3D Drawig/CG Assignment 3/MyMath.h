#pragma once
#include <math.h>
#include <iomanip>
#include "Defines.h"

// Converts degrees to radians.
float DegreesToRadians(float degrees)
{
    return degrees * (pi / 180);
}

// Calculates the cotangent of an angle.
float Cot(float degrees)
{
    return cos(DegreesToRadians(degrees)) / sin(DegreesToRadians(degrees));
}

// Linear interpolation between ints a and b using the ratio (between 0 and 1).
unsigned int Lerp(int a, int b, float ratio)
{
    return static_cast<unsigned int>(a + (b - a) * ratio);
}

// Converts 2D x,y coordinates to a 1D array for backbuffer.
unsigned int Convert2Dto1D(unsigned int x, unsigned int y, unsigned int width)
{
    return y * width + x;
}

// Multiplies two 4x4 matrices mat1 and mat2 and stores the result in the result matrix.
void MatrixMultiply(const Matrix4x4& mat1, const Matrix4x4& mat2, Matrix4x4& result)
{
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            result.Vect[row * 4 + col] = 0;  // Initialize the result.
            for (int i = 0; i < 4; ++i)
            {
                result.Vect[row * 4 + col] += mat1.Vect[row * 4 + i] * mat2.Vect[i * 4 + col];  // Matrix multiplication formula.
            }
        }
    }
}

// Resets a 4x4 matrix to the identity matrix.
void IdentityMatrix(Matrix4x4& matrix)
{
    matrix.AxisX = Float4{ 1, 0, 0, 0 };  // X axis.
    matrix.AxisY = Float4{ 0, 1, 0, 0 };  // Y axis.
    matrix.AxisZ = Float4{ 0, 0, 1, 0 };  // Z axis.
    matrix.AxisW = Float4{ 0, 0, 0, 1 };  // W axis.
}

// Creates a rotation matrix around the X-axis.
void RotateX(Matrix4x4& matrix, float degrees)
{
    float radians = DegreesToRadians(degrees);  // Convert degrees to radians.
    IdentityMatrix(matrix);  // Reset to identity.
    matrix.AxisY.y = cos(radians);
    matrix.AxisY.z = -sin(radians);
    matrix.AxisZ.y = sin(radians);
    matrix.AxisZ.z = cos(radians);
}

// Creates a rotation matrix around the Y-axis.
void RotateY(Matrix4x4& matrix, float degrees)
{
    float radians = DegreesToRadians(degrees);  // Convert degrees to radians.
    IdentityMatrix(matrix);  // Reset to identity.
    matrix.AxisX.x = cos(radians);
    matrix.AxisX.z = sin(radians);
    matrix.AxisZ.x = -sin(radians);
    matrix.AxisZ.z = cos(radians);
}

// Creates a rotation matrix around the Z-axis.
void RotateZ(Matrix4x4& matrix, float degrees)
{
    float radians = DegreesToRadians(degrees);  // Convert degrees to radians.
    IdentityMatrix(matrix);  // Reset to identity.
    matrix.AxisX.x = cos(radians);
    matrix.AxisX.y = -sin(radians);
    matrix.AxisY.x = sin(radians);
    matrix.AxisY.y = cos(radians);
}

// Applies a translation to the matrix by modifying the W column.
void Translate(Matrix4x4& matrix, float x, float y, float z)
{
    matrix.wx = x;  // Translate along X-axis.
    matrix.wy = y;  // Translate along Y-axis.
    matrix.wz = z;  // Translate along Z-axis.
}

// Creates a perspective projection matrix.
void ProjectionMatrix(Matrix4x4& matrix, float fov, float aspectRatio, float nearPlane, float farPlane)
{
    float yScale = Cot(fov * 0.5f);                                     // Vertical scaling factor.
    float xScale = yScale / aspectRatio;                                // Horizontal scaling factor.

    matrix.AxisX.x = xScale;                                            // Set horizontal scale into matrix.
    matrix.AxisY.y = -yScale;                                           // Set vertical scale into matrix.
    matrix.AxisZ.z = farPlane / (farPlane - nearPlane);                 // Depth scaling into matrix.
    matrix.AxisZ.w = 1.0f;                  
    matrix.AxisW.z = -farPlane * nearPlane / (farPlane - nearPlane);    // Translation along Z-axis into matrix.
    matrix.AxisW.w = 0.0f;                
}

// Convert coordinates (NDC) [-1,1] to screen space [0, screenWidth]
int ConvertToScreenX(float ndcX, unsigned int screenWidth)
{
    return static_cast<int>((ndcX + 1.0f) * 0.5f * screenWidth);
}

// Convert coordinates (NDC) [-1,1] to screen space [0, screenHeight]
int ConvertToScreenY(float ndcY, unsigned int screenHeight)
{
    return static_cast<int>((1.0f - ndcY) * 0.5f * screenHeight);
}

// Perform matrix-vector multiplication.
void VectorMultiplyMatrix(const float vector[4], const Matrix4x4& matrix, float result[4])
{
    for (int i = 0; i < 4; ++i)
    {
        result[i] = 0;
        for (int j = 0; j < 4; ++j)
        {
            result[i] += vector[j] * matrix.Vect[j * 4 + i];
        }
    }
}

// Computes the dot product of two 4D vectors.
float DotProduct(const Float4& v1, const Float4& v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

// Computes the orthonormal inverse of a 4x4 matrix.
Matrix4x4 OrthonormalInverse(const Matrix4x4& mIn)
{
    Matrix4x4 result;  // Initialize the result matrix.

    // Transpose the upper-left 3x3 of the matrix along the vertical.
    result.AxisX.x = mIn.AxisX.x; result.AxisX.y = mIn.AxisY.x; result.AxisX.z = mIn.AxisZ.x;
    result.AxisY.x = mIn.AxisX.y; result.AxisY.y = mIn.AxisY.y; result.AxisY.z = mIn.AxisZ.y;
    result.AxisZ.x = mIn.AxisX.z; result.AxisZ.y = mIn.AxisY.z; result.AxisZ.z = mIn.AxisZ.z;

    // Set translation part to zero
    result.AxisX.w = result.AxisY.w = result.AxisZ.w = 0.0f;
    result.AxisW = { 0.0f, 0.0f, 0.0f, 1.0f };

    // Calculate the new position using dot product.
    result.AxisW.x = -DotProduct(mIn.AxisX, mIn.AxisW);
    result.AxisW.y = -DotProduct(mIn.AxisY, mIn.AxisW);
    result.AxisW.z = -DotProduct(mIn.AxisZ, mIn.AxisW);

    return result;
}

////////////////MATRIX GAUNTLET TEST////////////////

// Debug helper function for vector.
void PrintVector(const float vector[4], const std::string& label)
{
    std::cout << label << ": [";
    for (int i = 0; i < 4; ++i)
    {
        std::cout << vector[i];
        if (i < 3) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
    std::cout << std::endl;
}

// Debug helper function for 4x4 matrix with a label.
void PrintMatrix(const Matrix4x4& matrix, const std::string& label)
{
    std::cout << label << " Matrix:" << std::endl;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            std::cout << matrix.Vect[i * 4 + j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// A test function for the rest of the Matrix Gaunlet.
void TestMatrixMultiplication()
{
    Matrix4x4 matrix1, matrix2, resultMatrix;

    // Initialize matrix1.
    matrix1.AxisX = Float4{ 1, 2, 3, 4 };
    matrix1.AxisY = Float4{ 5, 6, 7, 8 };
    matrix1.AxisZ = Float4{ 9, 10, 11, 12 };
    matrix1.AxisW = Float4{ 13, 14, 15, 16 };

    // Initialize matrix2.
    matrix2.AxisX = Float4{ 17, 18, 19, 20 };
    matrix2.AxisY = Float4{ 21, 22, 23, 24 };
    matrix2.AxisZ = Float4{ 25, 26, 27, 28 };
    matrix2.AxisW = Float4{ 29, 30, 31, 32 };

    // Perform matrix multiplication.
    MatrixMultiply(matrix1, matrix2, resultMatrix);

    // Print matrices and results.
    PrintMatrix(matrix1, "Matrix 1");
    PrintMatrix(matrix2, "Matrix 2");
    PrintMatrix(resultMatrix, "Result of Matrix 1 * Matrix 2");

    // Vector-Matrix multiplication Test.
    float vector[4] = { 1, 2, 3, 4 };
    float vectorResult[4];

    // Perform vector-matrix multiplication
    VectorMultiplyMatrix(vector, matrix1, vectorResult);

    // Print vector multiplication results
    PrintVector(vectorResult, "Result of Vector * Matrix 1");
}

// Debug for rotation and inversion.
void TestAdvancedMatrixMultiplication()
{
    Matrix4x4 matrix3, matrix4, resultMatrix;

    // Initialize matrix3.
    matrix3.AxisX = Float4{ 1, 0, 0, 0 };
    matrix3.AxisY = Float4{ 0, 1, 0, 0 };
    matrix3.AxisZ = Float4{ 0, 0, 1, 0 };
    matrix3.AxisW = Float4{ 7, 8, 5, 1 };

    // Initialize matrix4.
    matrix4.AxisX = Float4{ 1, 0, 0, 0 };
    matrix4.AxisY = Float4{ 0, 0.309, 0.951, 0 };
    matrix4.AxisZ = Float4{ 0, -0.951, 0.309, 0 };
    matrix4.AxisW = Float4{ 0, 0, 0, 1 };

    // Perform matrix multiplication.
    MatrixMultiply(matrix3, matrix4, resultMatrix);

    // Print the results of matrix multiplication.
    PrintMatrix(matrix3, "Matrix 3");
    PrintMatrix(matrix4, "Matrix 4");
    PrintMatrix(resultMatrix, "Result of Matrix 3 * Matrix 4");

    Matrix4x4 xRotationMatrix, yRotationMatrix, zRotationMatrix;

    // X-axis rotation (45 degrees).
    IdentityMatrix(xRotationMatrix);
    RotateX(xRotationMatrix, 45.0f);
    PrintMatrix(xRotationMatrix, "X-axis Rotation (45 degrees)");

    // Y-axis rotation (65 degrees).
    IdentityMatrix(yRotationMatrix);
    RotateY(yRotationMatrix, 65.0f);
    PrintMatrix(yRotationMatrix, "Y-axis Rotation (65 degrees)");

    // Z-axis rotation (105 degrees).
    IdentityMatrix(zRotationMatrix);
    RotateZ(zRotationMatrix, 105.0f);
    PrintMatrix(zRotationMatrix, "Z-axis Rotation (105 degrees)");

    // Test inverting a matrix.
    Matrix4x4 matrix5, inverseMatrix5;

    // Initialize matrix5.
    matrix5.AxisX = Float4{ 1, 0, 0, 0 };
    matrix5.AxisY = Float4{ 0, 0.309, 0.951, 0 };
    matrix5.AxisZ = Float4{ 0, -0.951, 0.309, 0 };
    matrix5.AxisW = Float4{ 7, -2.282, 9.153, 1 };

    // Matrix inversion.
    inverseMatrix5 = OrthonormalInverse(matrix5);

    // Print matrix5 and its inverse.
    PrintMatrix(matrix5, "Matrix 5");
    PrintMatrix(inverseMatrix5, "Inverse of Matrix 5");
}
