#pragma once
#include "MyMath.h"

// Function pointer for pixel shader.
void (*PixelShader)(VERTEX&) = nullptr;

// Transform a Matrix by vertex matrix multiplication.
void TransformVertex(float* vertex, const Matrix4x4& matrix, float* result)
{
    VectorMultiplyMatrix(vertex, matrix, result);
    for (int i = 0; i < 4; ++i)
        vertex[i] = result[i];
}

// Vertex shader to transform from model space to screen space.
void VertexShader(VERTEX& vertex, const Matrix4x4& worldMatrix, const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix)
{
    float result[4];

    // Transforms to get from World Space to Camera Space.
    Matrix4x4 invertedViewMatrix = OrthonormalInverse(viewMatrix);

    // Apply transformations.
    TransformVertex(vertex.xyzw, worldMatrix, result);          // Transform to World Space.
    TransformVertex(vertex.xyzw, invertedViewMatrix, result);   // Transform to View Space.
    TransformVertex(vertex.xyzw, projectionMatrix, result);     // Transform to Projection Space.

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

// Pixel Shaders for colors.
void Black(VERTEX& pixel)
{
    pixel.color = black;
}

void White(VERTEX& pixel)
{
    pixel.color = white;
}

void Red(VERTEX& pixel)
{
    pixel.color = red;
}

void Green(VERTEX& pixel)
{
    pixel.color = green;
}

void Yellow(VERTEX& pixel)
{
    pixel.color = yellow;
}

void Blue(VERTEX& pixel)
{
    pixel.color = blue;
}

void Pink(VERTEX& pixel)
{
    pixel.color = pink;
}

void Cyan(VERTEX& pixel)
{
    pixel.color = cyan;
}

// General PixelShader function that calls the current PixelShader.
unsigned int GeneralPixelShader(VERTEX& inputVertex)
{
    if (PixelShader)
    {
        PixelShader(inputVertex);
    }
    return inputVertex.color;
}

// Blend color function.
unsigned int BlendLineColor(unsigned int color1, unsigned int color2, unsigned int color3, float alpha, float beta, float gamma)
{
    // Extract the RGBA components from color1.
    unsigned int r1 = (color1 & 0x00FF0000) >> 16;
    unsigned int g1 = (color1 & 0x0000FF00) >> 8;
    unsigned int b1 = (color1 & 0x000000FF);
    unsigned int a1 = (color1 & 0xFF000000) >> 24;

    // Extract the RGBA components from color2.
    unsigned int r2 = (color2 & 0x00FF0000) >> 16;
    unsigned int g2 = (color2 & 0x0000FF00) >> 8;
    unsigned int b2 = (color2 & 0x000000FF);
    unsigned int a2 = (color2 & 0xFF000000) >> 24;

    // Extract the RGBA components from color3.
    unsigned int r3 = (color3 & 0x00FF0000) >> 16;
    unsigned int g3 = (color3 & 0x0000FF00) >> 8;
    unsigned int b3 = (color3 & 0x000000FF);
    unsigned int a3 = (color3 & 0xFF000000) >> 24;

    // Interpolate the RGBA values based on the alpha, beta, and gamma parameters.
    unsigned int r = static_cast<unsigned int>(alpha * r1 + beta * r2 + gamma * r3);
    unsigned int g = static_cast<unsigned int>(alpha * g1 + beta * g2 + gamma * g3);
    unsigned int b = static_cast<unsigned int>(alpha * b1 + beta * b2 + gamma * b3);
    unsigned int a = static_cast<unsigned int>(alpha * a1 + beta * a2 + gamma * a3);

    // Recombine the RGBA values into a single color.
    return (a << 24) | (r << 16) | (g << 8) | b;
}

// BGRA To ARGB Converter.
unsigned int BGRAConverterToARGB(unsigned int colorBGRA)
{
    // Bit shifting with a mask.
    unsigned int blue = (colorBGRA & 0xFF000000) >> 24;
    unsigned int green = (colorBGRA & 0x00FF0000) >> 8;
    unsigned int red = (colorBGRA & 0x0000FF00) << 8;
    unsigned int alpha = (colorBGRA & 0x000000FF) << 24;

    // Return the recombined ARGB.
    return (alpha | red | green | blue);
}

// Shader for Texels.
unsigned int TexturePixelShader(float u, float v, const unsigned int* texture, unsigned int textureWidth, unsigned int textureHeight)
{
    // Convert UV coordinates to texture coordinates.
    unsigned int texX = static_cast<unsigned int>(u * (textureWidth - 1));
    unsigned int texY = static_cast<unsigned int>(v * (textureHeight - 1));

    // Convert 2D texture coordinates to 1D.
    unsigned int texIndex = Convert2Dto1D(texX, texY, textureWidth);

    // Convert the color format for the texture.
    return BGRAConverterToARGB(texture[texIndex]);
}

// Set the face colors of the cube.
void FaceColor(int v1, int v2, int v3, int v4, unsigned int faceColor)
{
    // Set the same color for all four vertices of the face
    vertices[v1].color = faceColor;
    vertices[v2].color = faceColor;
    vertices[v3].color = faceColor;
    vertices[v4].color = faceColor;
}