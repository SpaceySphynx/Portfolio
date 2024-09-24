#pragma once
#include "Shaders.h"

// Clear the Color Buffer with a solid color (background).
void ClearColorBuffer(unsigned int* backBuffer, unsigned int totalPixels, unsigned int color)
{
    for (unsigned int i = 0; i < totalPixels; ++i)
    {
        backBuffer[i] = color;
    }
}

// Draw a Pixel to the window.
void DrawPixel(unsigned int* backBuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int color)
{
    if (x < width && y < height) 
    {
        unsigned int i = Convert2Dto1D(x, y, width);
        backBuffer[i] = color;
    }
}

// Draw lines using Parametric Line Algorithm.
void ParametricLine(unsigned int* backBuffer, int x1, int y1, int x2, int y2, unsigned int width, unsigned int height, unsigned int startingColor, unsigned int endingColor)
{
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;

    // If the absolute value is deltaX is greater than the absolute value of deltaY (More horizontal than vertical).
    if (abs(deltaX) > abs(deltaY))
    {
        // If x1 is greater than x2, then swap points to always iterate from left to right.
        if (x1 > x2)
        {
            std::swap(x1, x2);
            std::swap(y1, y2);
            std::swap(startingColor, endingColor);
            deltaX = x2 - x1;
            deltaY = y2 - y1;
        }

        for (int x = x1; x <= x2; ++x)
        {
            // Calculate ratio.
            float ratio = static_cast<float>(x - x1) / deltaX;

            // Interpolating the Y value using LERP.
            float currYFloat = Lerp(y1, y2, ratio);

            // Apply floor rounding to minimize the errors.
            int currY = static_cast<int>(floor(currYFloat + 0.5f));

            // Blend colors based on the ratio.
            unsigned int currentColor = BlendLineColor(startingColor, endingColor, ratio);

            // Draw the pixel.
            DrawPixel(backBuffer, x, currY, width, height, currentColor);
        }
    }
    else
    {
        // Swap points to always iterate from top to bottom if y1 is larger than y2.
        if (y1 > y2)
        {
            std::swap(x1, x2);
            std::swap(y1, y2);
            std::swap(startingColor, endingColor);
            deltaX = x2 - x1;
            deltaY = y2 - y1;
        }

        for (int y = y1; y <= y2; ++y)
        {
            // Calculate ratio.
            float ratio = static_cast<float>(y - y1) / deltaY;

            // Interpolate the X value using LERP.
            float currXFloat = Lerp(x1, x2, ratio);

            // Apply floor rounding to minimize rounding errors.
            int currX = static_cast<int>(floor(currXFloat + 0.5f));

            // Blend colors based on the ratio.
            unsigned int currentColor = BlendLineColor(startingColor, endingColor, ratio);

            // Draw the pixel.
            DrawPixel(backBuffer, currX, y, width, height, currentColor);
        }
    }
}

// Using the Vertex Shader to Draw Lines in 3D space.
void Draw3DLine(VERTEX start, VERTEX end, const Matrix4x4& worldMatrix, const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix)
{
    // Apply vertex shaders.
    VertexShader(start, worldMatrix, viewMatrix, projectionMatrix);
    VertexShader(end, worldMatrix, viewMatrix, projectionMatrix);

    // Convert to screen coordinates.
    int x1 = ConvertToScreenX(start.xyzw[0], width);
    int y1 = ConvertToScreenY(start.xyzw[1], height);
    int x2 = ConvertToScreenX(end.xyzw[0], width);
    int y2 = ConvertToScreenY(end.xyzw[1], height);

    // Draw the line on the screen.
    ParametricLine(backBuffer, x1, y1, x2, y2, width, height, start.color, end.color);
}

// Draw the Grid.
void DrawGrid(const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix)
{
    unsigned int gridColor = green;  // Default Grid Color.

    // Draw horizontal lines.
    for (int i = 0; i <= 10; ++i)
    {
        float z = -0.5f + i * 0.1f; // Line spacing.

        VERTEX start = { {-0.5f, 0.0f, z, 1.0f}, gridColor };
        VERTEX end = { {0.5f, 0.0f, z, 1.0f}, gridColor };

        Draw3DLine(start, end, gridWorldMatrix, viewMatrix, projectionMatrix);
    }

    // Draw vertical lines.
    for (int i = 0; i <= 10; ++i)
    {
        float x = -0.5f + i * 0.1f; // Line spacing.

        VERTEX start = { {x, 0.0f, -0.5f, 1.0f}, gridColor };
        VERTEX end = { {x, 0.0f, 0.5f, 1.0f}, gridColor };

        Draw3DLine(start, end, gridWorldMatrix, viewMatrix, projectionMatrix);
    }
}

// Helper function to draw the face of the cube using the Draw3d function.
void DrawFace(VERTEX v1, VERTEX v2, VERTEX v3, VERTEX v4, const Matrix4x4& worldMatrix, const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix)
{
    // Draw the four edges of the face
    Draw3DLine(v1, v2, worldMatrix, viewMatrix, projectionMatrix);
    Draw3DLine(v2, v3, worldMatrix, viewMatrix, projectionMatrix);
    Draw3DLine(v3, v4, worldMatrix, viewMatrix, projectionMatrix);
    Draw3DLine(v4, v1, worldMatrix, viewMatrix, projectionMatrix);
}

// Draw Cube using the 6 faces.
void DrawCube(const Matrix4x4& worldMatrix, const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix)
{
    // Back face.
    DrawFace(vertices[0], vertices[1], vertices[3], vertices[2], worldMatrix, viewMatrix, projectionMatrix);

    // Front face.
    DrawFace(vertices[4], vertices[5], vertices[7], vertices[6], worldMatrix, viewMatrix, projectionMatrix);

    // Top face.
    DrawFace(vertices[0], vertices[1], vertices[5], vertices[4], worldMatrix, viewMatrix, projectionMatrix);

    // Bottom face.
    DrawFace(vertices[2], vertices[3], vertices[7], vertices[6], worldMatrix, viewMatrix, projectionMatrix);

    // Left face.
    DrawFace(vertices[0], vertices[2], vertices[6], vertices[4], worldMatrix, viewMatrix, projectionMatrix);

    // Right face.
    DrawFace(vertices[1], vertices[3], vertices[7], vertices[5], worldMatrix, viewMatrix, projectionMatrix);
}