#pragma once
#include "Shaders.h"

// Clear the Color Buffer with a solid color (background).
void ClearColorBuffer(unsigned int* backBuffer, size_t totalPixels, unsigned int color)
{
    for (size_t i = 0; i < totalPixels; ++i)
    {
        backBuffer[i] = color;
    }
}

// Clears the Depth buffer to -1.0. My camera after rotations seems to be right handed so -1.0 is farther away. 
void ClearDepthBuffer(float* depthBuffer, size_t totalPixels, float clearValue = -1.0f)
{
    for (unsigned int i = 0; i < totalPixels; ++i)
    {
        depthBuffer[i] = clearValue;
    }
}

// Draws a single pixel to the backbuffer.
void DrawPixel(unsigned int* backBuffer, float* depthBuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int color, float depth)
{
    if (x < width && y < height)
    {
        unsigned int index = Convert2Dto1D(x, y, width);    // Convert 2D to 1D array index.
        float invertedDepth = zFar - depth;                 // Invert depth for right-handed system.

        // Check if inverted depth is within the acceptable range.
        if (invertedDepth >= zNear && invertedDepth <= zFar)
        {
            // If the new pixel's depth is less (closer) than the current stored depth, update the color.
            if (invertedDepth < depthBuffer[index])
            {
                backBuffer[index] = color;          // Update the color buffer with the new pixel color.
                depthBuffer[index] = invertedDepth; // Update the Z-buffer with the new depth value.
            }
        }
    }
}

// Draw lines using Parametric Line Algorithm with updated BlendLineColor and depth interpolation.
void ParametricLine(unsigned int* backBuffer, float* depthBuffer, int x1, int y1, int x2, int y2, unsigned int width, unsigned int height, unsigned int startingColor, unsigned int endingColor, float z1, float z2)
{
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;

    // If the absolute value of deltaX is greater than the absolute value of deltaY (More horizontal than vertical).
    if (abs(deltaX) > abs(deltaY))
    {
        // Ensure left-to-right.
        if (x1 > x2)
        {
            std::swap(x1, x2);
            std::swap(y1, y2);
            std::swap(startingColor, endingColor);
            std::swap(z1, z2);
            deltaX = x2 - x1;
            deltaY = y2 - y1;
        }

        for (int x = x1; x <= x2; ++x)
        {
            float ratio = static_cast<float>(x - x1) / deltaX;
            float currYFloat = float_Lerp(y1, y2, ratio);
            int currY = static_cast<int>(floor(currYFloat + 0.5f));

            // Interpolate the Z (depth) value using LERP.
            float currZ = float_Lerp(z1, z2, ratio);
            float alpha = 1.0f - ratio;
            float beta = ratio;
            float gamma = 0.0f;
            unsigned int currentColor = BlendLineColor(startingColor, endingColor, endingColor, alpha, beta, gamma);
            DrawPixel(backBuffer, depthBuffer, x, currY, width, height, currentColor, currZ);
        }
    }
    else
    {
        // Ensure top to bottom more vertical than horizontal.
        if (y1 > y2)
        {
            std::swap(x1, x2);
            std::swap(y1, y2);
            std::swap(startingColor, endingColor);
            std::swap(z1, z2);
            deltaX = x2 - x1;
            deltaY = y2 - y1;
        }

        for (int y = y1; y <= y2; ++y)
        {
            float ratio = static_cast<float>(y - y1) / deltaY;
            float currXFloat = float_Lerp(x1, x2, ratio);
            int currX = static_cast<int>(floor(currXFloat + 0.5f));

            // Interpolate the Z (depth) value using LERP.
            float currZ = float_Lerp(z1, z2, ratio);

            float alpha = 1.0f - ratio;
            float beta = ratio;
            float gamma = 0.0f;
            unsigned int currentColor = BlendLineColor(startingColor, endingColor, endingColor, alpha, beta, gamma);
            DrawPixel(backBuffer, depthBuffer, currX, y, width, height, currentColor, currZ);
        }
    }
}

// Using the Vertex Shader to Draw Lines in 3D space with depth handling.
void Draw3DLine(VERTEX start, VERTEX end, const Matrix4x4& worldMatrix, const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix)
{
    // Apply vertex shaders.
    VertexShader(start, worldMatrix, viewMatrix, projectionMatrix);
    VertexShader(end, worldMatrix, viewMatrix, projectionMatrix);

    // Convert the 3D coordinates to 2D screen coordinates.
    int x1 = ConvertToScreenX(start.xyzw[0], width);
    int y1 = ConvertToScreenY(start.xyzw[1], height);
    int x2 = ConvertToScreenX(end.xyzw[0], width);
    int y2 = ConvertToScreenY(end.xyzw[1], height);

    // Extract the Linear Z values for depth interpolation.
    float z1 = start.xyzw[2];  // Z value from the start vertex.
    float z2 = end.xyzw[2];    // Z value from the end vertex.

    // Apply pixel shader colors to the start and end vertices.
    start.color = GeneralPixelShader(start);
    end.color = GeneralPixelShader(end);
    ParametricLine(backBuffer, depthBuffer, x1, y1, x2, y2, width, height, start.color, end.color, z1, z2);
}

// Draw the Grid.
void DrawGrid(const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix)
{
    unsigned int gridColor = yellow;  // Default Grid Color.

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

// Helper function to draw the face of the cube.
void DrawFace(VERTEX v1, VERTEX v2, VERTEX v3, VERTEX v4, const Matrix4x4& worldMatrix, const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix)
{
    // Draw the four edges of the face.
    Draw3DLine(v1, v2, worldMatrix, viewMatrix, projectionMatrix);
    Draw3DLine(v2, v3, worldMatrix, viewMatrix, projectionMatrix);
    Draw3DLine(v3, v4, worldMatrix, viewMatrix, projectionMatrix);
    Draw3DLine(v4, v1, worldMatrix, viewMatrix, projectionMatrix);
}

// Better Bruite Triangle for solid colors.
void BetterBruteTriangle(unsigned int* backBuffer, float* depthBuffer, int width, int height, VERTEX v1, VERTEX v2, VERTEX v3)
{
    // Convert vertices to screen coordinates.
    int x1 = ConvertToScreenX(v1.xyzw[0], width);
    int y1 = ConvertToScreenY(v1.xyzw[1], height);
    int x2 = ConvertToScreenX(v2.xyzw[0], width);
    int y2 = ConvertToScreenY(v2.xyzw[1], height);
    int x3 = ConvertToScreenX(v3.xyzw[0], width);
    int y3 = ConvertToScreenY(v3.xyzw[1], height);

    // Boundries of the triangle.
    int minX = std::min({ x1, x2, x3 });
    int maxX = std::max({ x1, x2, x3 });
    int minY = std::min({ y1, y2, y3 });
    int maxY = std::max({ y1, y2, y3 });

    // Loop through all pixels in the boundry.
    for (int y = minY; y <= maxY; ++y)
    {
        for (int x = minX; x <= maxX; ++x)
        {
            float alpha, beta, gamma;
            FindBarycentricCoords(x, y, x1, y1, x2, y2, x3, y3, alpha, beta, gamma);

            // If the point lies inside the triangle, calculate the depth and draw the pixel.
            if (alpha >= 0 && beta >= 0 && gamma >= 0)
            {
                // Interpolate Z using barycentric coordinates.
                float interpolatedDepth = alpha * v1.xyzw[2] + beta * v2.xyzw[2] + gamma * v3.xyzw[2];

                // BlendLineColors, get the depth and draw the pixel.
                unsigned int interpolatedColor = BlendLineColor(v1.color, v2.color, v3.color, alpha, beta, gamma);
                float adjustedDepth = zFar - interpolatedDepth;
                DrawPixel(backBuffer, depthBuffer, x, y, width, height, interpolatedColor, interpolatedDepth);
            }
        }
    }
}

// Draw using the cube face triangles using better brute and shaders.
void DrawFaceAsTriangles(VERTEX v1, VERTEX v2, VERTEX v3, VERTEX v4, const Matrix4x4& worldMatrix, const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix)
{
    // Apply vertex transformations.
    VertexShader(v1, worldMatrix, viewMatrix, projectionMatrix);
    VertexShader(v2, worldMatrix, viewMatrix, projectionMatrix);
    VertexShader(v3, worldMatrix, viewMatrix, projectionMatrix);
    VertexShader(v4, worldMatrix, viewMatrix, projectionMatrix);

    // Apply color via pixel shader if the pixelshader exists.
    if (PixelShader != nullptr) 
    {
        PixelShader(v1);
        PixelShader(v2);
        PixelShader(v3);
        PixelShader(v4);
    }

    // Draw the two triangles that form the face.
    BetterBruteTriangle(backBuffer, depthBuffer, width, height, v1, v2, v3);
    BetterBruteTriangle(backBuffer, depthBuffer, width, height, v3, v4, v1);
}

// Draw Cube using the 6 faces triangle-based and with different colors for each face.
void DrawCube(const Matrix4x4& worldMatrix, const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix)
{
    // Disable the pixel shader for the cube drawing.
    void (*savedPixelShader)(VERTEX&) = PixelShader; // Save the current pixel shader.
    PixelShader = nullptr; // Disable the pixel shader.
    
    // Apply colors to each vertex of the face before drawing
    // Back face.
    FaceColor(0, 1, 2, 3, backFaceColor);
    DrawFaceAsTriangles(vertices[0], vertices[1], vertices[3], vertices[2], worldMatrix, viewMatrix, projectionMatrix);

    // Front face.
    FaceColor(4, 5, 6, 7, frontFaceColor);
    DrawFaceAsTriangles(vertices[4], vertices[5], vertices[7], vertices[6], worldMatrix, viewMatrix, projectionMatrix);

    // Top face.
    FaceColor(0, 1, 4, 5, topFaceColor);
    DrawFaceAsTriangles(vertices[0], vertices[1], vertices[5], vertices[4], worldMatrix, viewMatrix, projectionMatrix);

    // Bottom face.
    FaceColor(2, 3, 6, 7, bottomFaceColor);
    DrawFaceAsTriangles(vertices[2], vertices[3], vertices[7], vertices[6], worldMatrix, viewMatrix, projectionMatrix);

    // Left face.
    FaceColor(0, 2, 4, 6, leftFaceColor);
    DrawFaceAsTriangles(vertices[0], vertices[2], vertices[6], vertices[4], worldMatrix, viewMatrix, projectionMatrix);

    // Right face.
    FaceColor(1, 3, 5, 7, rightFaceColor);
    DrawFaceAsTriangles(vertices[1], vertices[3], vertices[7], vertices[5], worldMatrix, viewMatrix, projectionMatrix);

    // Turn back on PixelShader giving it's value back.
    PixelShader = savedPixelShader;
}

// Better Brute Triangle Function modified for Texels.
void BetterBruteTriangleWithTexture(unsigned int* backBuffer, float* depthBuffer, int width, int height, VERTEX v1, VERTEX v2, VERTEX v3, const unsigned int* texture, unsigned int textureWidth, unsigned int textureHeight)
{
    // Convert vertices to screen coordinates.
    int x1 = ConvertToScreenX(v1.xyzw[0], width);
    int y1 = ConvertToScreenY(v1.xyzw[1], height);
    int x2 = ConvertToScreenX(v2.xyzw[0], width);
    int y2 = ConvertToScreenY(v2.xyzw[1], height);
    int x3 = ConvertToScreenX(v3.xyzw[0], width);
    int y3 = ConvertToScreenY(v3.xyzw[1], height);

    // Find the boundries of the triangle.
    int minX = std::min({ x1, x2, x3 });
    int maxX = std::max({ x1, x2, x3 });
    int minY = std::min({ y1, y2, y3 });
    int maxY = std::max({ y1, y2, y3 });

    // Loop through all pixels of the triangle.
    for (int y = minY; y <= maxY; ++y)
    {
        for (int x = minX; x <= maxX; ++x)
        {
            float alpha, beta, gamma;
            FindBarycentricCoords(x, y, x1, y1, x2, y2, x3, y3, alpha, beta, gamma);

            // If the point lies inside the triangle, calculate the interpolated values and draw the pixel.
            if (alpha >= 0 && beta >= 0 && gamma >= 0)
            {
                // Interpolate Linear Z using barycentric coordinates.
                float interpolatedDepth = alpha * v1.xyzw[2] + beta * v2.xyzw[2] + gamma * v3.xyzw[2];

                // Interpolate UV coordinates.
                float u = alpha * v1.uv[0] + beta * v2.uv[0] + gamma * v3.uv[0];
                float v = alpha * v1.uv[1] + beta * v2.uv[1] + gamma * v3.uv[1];

                // Call texture pixel shader to sample the texture.
                unsigned int interpolatedColor = TexturePixelShader(u, v, texture, textureWidth, textureHeight);

                // Draw the pixel with the interpolated color and depth.
                DrawPixel(backBuffer, depthBuffer, x, y, width, height, interpolatedColor, interpolatedDepth);
            }
        }
    }
}

// Draw faces of the cube as triangles with texels.
void DrawFaceAsTrianglesWithTexture(VERTEX v1, VERTEX v2, VERTEX v3, VERTEX v4, const Matrix4x4& worldMatrix, const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix, const unsigned int* texture, unsigned int textureWidth, unsigned int textureHeight)
{
    // Apply vertex transformations.
    VertexShader(v1, worldMatrix, viewMatrix, projectionMatrix);
    VertexShader(v2, worldMatrix, viewMatrix, projectionMatrix);
    VertexShader(v3, worldMatrix, viewMatrix, projectionMatrix);
    VertexShader(v4, worldMatrix, viewMatrix, projectionMatrix);

    // Draw the two triangles that form the face.
    BetterBruteTriangleWithTexture(backBuffer, depthBuffer, width, height, v1, v2, v3, texture, textureWidth, textureHeight);
    BetterBruteTriangleWithTexture(backBuffer, depthBuffer, width, height, v3, v4, v1, texture, textureWidth, textureHeight);
}

// Helper function to assign UVs to the four vertices of the face so I don't have to write as much code.
void FaceUV(int v1, int v2, int v3, int v4, float uv[4][2])
{
    vertices[v1].uv[0] = uv[0][0]; vertices[v1].uv[1] = uv[0][1];
    vertices[v2].uv[0] = uv[1][0]; vertices[v2].uv[1] = uv[1][1];
    vertices[v3].uv[0] = uv[2][0]; vertices[v3].uv[1] = uv[2][1];
    vertices[v4].uv[0] = uv[3][0]; vertices[v4].uv[1] = uv[3][1];
}

// Draw Cube using the 6 faces triangle-based and with textures for each face.
void DrawCubeWithTexture(const Matrix4x4& worldMatrix, const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix, const unsigned int* texture, unsigned int textureWidth, unsigned int textureHeight)
{
    // Disable the pixel shader for the cube drawing
    void (*savedPixelShader)(VERTEX&) = PixelShader; // Save the current pixel shader.
    PixelShader = nullptr; // Disable the pixel shader.

    // Assigned texture UV coordinates to each vertex for the cube.
    // Back face.
    FaceUV(0, 1, 2, 3, uvBack);  // Back face
    DrawFaceAsTrianglesWithTexture(vertices[0], vertices[1], vertices[3], vertices[2], worldMatrix, viewMatrix, projectionMatrix, texture, textureWidth, textureHeight);

    // Front face.
    FaceUV(4, 5, 6, 7, uvFront);
    DrawFaceAsTrianglesWithTexture(vertices[4], vertices[5], vertices[7], vertices[6], worldMatrix, viewMatrix, projectionMatrix, texture, textureWidth, textureHeight);

    // Top face.
    FaceUV(4, 5, 0, 1, uvTop);
    DrawFaceAsTrianglesWithTexture(vertices[0], vertices[1], vertices[5], vertices[4], worldMatrix, viewMatrix, projectionMatrix, texture, textureWidth, textureHeight);

    // Bottom face
    FaceUV(2, 3, 6, 7, uvBottom);
    DrawFaceAsTrianglesWithTexture(vertices[2], vertices[3], vertices[7], vertices[6], worldMatrix, viewMatrix, projectionMatrix, texture, textureWidth, textureHeight);

    // Left face.
    FaceUV(0, 2, 4, 6, uvLeft);
    DrawFaceAsTrianglesWithTexture(vertices[0], vertices[2], vertices[6], vertices[4], worldMatrix, viewMatrix, projectionMatrix, texture, textureWidth, textureHeight);

    // Right face.
    FaceUV(1, 3, 5, 7, uvRight);
    DrawFaceAsTrianglesWithTexture(vertices[1], vertices[3], vertices[7], vertices[5], worldMatrix, viewMatrix, projectionMatrix, texture, textureWidth, textureHeight);

    // Turn back on PixelShader giving it's value back.
    PixelShader = savedPixelShader;
}