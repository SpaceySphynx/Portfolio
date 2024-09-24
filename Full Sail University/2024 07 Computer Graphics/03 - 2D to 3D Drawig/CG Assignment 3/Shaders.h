#pragma once
#include "MyMath.h"

// Transform a Matrix by vertex matrix multiplication.
void TransformVertex(float* vertex, const Matrix4x4& matrix)
{
    float result[4] = { 0 };
    VectorMultiplyMatrix(vertex, matrix, result);
    for (int i = 0; i < 4; ++i)
        vertex[i] = result[i];
}

// Vertex shader to transform from model space to screen space.
void VertexShader(VERTEX& vertex, const Matrix4x4& worldMatrix, const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix)
{
    // Transforms to get from World Space to Camera Space.
    Matrix4x4 invertedViewMatrix = OrthonormalInverse(viewMatrix);
    TransformVertex(vertex.xyzw, worldMatrix);
    TransformVertex(vertex.xyzw, invertedViewMatrix);
    TransformVertex(vertex.xyzw, projectionMatrix);

    // Perspective divide.
    const float epsilon = 1e-6f;            // Small value to avoid division by zero.
    if (fabs(vertex.xyzw[3]) > epsilon)     // Ensure w is not zero or near zero.
    {
        vertex.xyzw[0] /= vertex.xyzw[3];   // Divide x by w.
        vertex.xyzw[1] /= vertex.xyzw[3];   // Divide y by w.
        vertex.xyzw[2] /= vertex.xyzw[3];   // Divide z by w.
        vertex.xyzw[3] = 1.0f;
    }
}

// Placeholder for pixel shader.
unsigned int PixelShader(const VERTEX& inputVertex)
{
    return inputVertex.color;
}

// Blends between two colors based on LERP ratio.
unsigned int BlendLineColor(unsigned int startingColor, unsigned int endingColor, float ratio)
{
    // Extract the RGBA components from the starting color using bit shift and masking.
    unsigned int startR = (startingColor & 0x00FF0000) >> 16;  // Extract red.
    unsigned int startG = (startingColor & 0x0000FF00) >> 8;   // Extract green.
    unsigned int startB = (startingColor & 0x000000FF);        // Extract blue.
    unsigned int startA = (startingColor & 0xFF000000) >> 24;  // Extract alpha.

    // Extract the RGBA components from the ending color using bit shift and masking.
    unsigned int endR = (endingColor & 0x00FF0000) >> 16;  // Extract red.
    unsigned int endG = (endingColor & 0x0000FF00) >> 8;   // Extract green.
    unsigned int endB = (endingColor & 0x000000FF);        // Extract blue.
    unsigned int endA = (endingColor & 0xFF000000) >> 24;  // Extract alpha.

    // Linearly interpolate each color channel.
    unsigned int currR = Lerp(startR, endR, ratio);
    unsigned int currG = Lerp(startG, endG, ratio);
    unsigned int currB = Lerp(startB, endB, ratio);
    unsigned int currA = Lerp(startA, endA, ratio);

    // Recombine the colors.
    return (currA << 24) | (currR << 16) | (currG << 8) | currB;
}
