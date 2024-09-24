#include <iostream>
#include "Main.h"
#include "RasterFunction.h"
#include "RasterSurface.h"
#include "XTime.h"
#include "treeolife.h"

// Constructor.
Main::Main()
{
    backBuffer = new unsigned int[totalPixels];             // Allocate a 1D array for pixel data color buffer.
    depthBuffer = new float[totalPixels];                   // Allocate a 1D array for depth data depth buffer.
    ClearColorBuffer(backBuffer, totalPixels, bufferColor); // Clear the Color Buffer to a solid color.
    RS_Initialize("Johnathan Richards", width, height);     // Initialize the RasterSurface.
    InitializeMatrices();                                   // Initialize the matrices (world, view, projection)
}

// Destructor.
Main::~Main()
{
    delete[] depthBuffer;                   // Clean up the array.
    delete[] backBuffer;                    // Clean up the array.
    RS_Shutdown();                          // Shutdown and clear the RasterSurface.
}

// Initialize the matrices.
void Main::InitializeMatrices()
{
    // Move cube slightly up by 0.25 units.
    IdentityMatrix(cubeWorldMatrix);
    Translate(cubeWorldMatrix, 0.0f, 0.25f, 0.0f);

    // Rotate the camera by -18 degrees (in this assignment I went to -40 to see the top) on the X-axis and move backwards by 1.
    IdentityMatrix(viewMatrix);
    Rotate(viewMatrix, 'x', -40.0f);
    Translate(viewMatrix, 0.0f, 0.0f, -1.0f);

    // Projection Matrix: Perspective projection
    ProjectionMatrix(projectionMatrix, 90.0f, aspectRatio, zNear, zFar);  // Pass projectionMatrix (Matrix4x4)
}

// Update the window function.
void Main::WindowUpdate()
{
    XTime time;  // XTime initiate.
    float frameTime = 1.0f / targetFPS; // The draw frame rate.
    time.Signal();  // Signal XTime.

    do
    {
        // Measure delta time each frame.
        time.Signal();
        float deltaTime = static_cast<float>(time.Delta());
        timer += deltaTime;

        // FPS when timer reaches FPS then draw.
        while (timer >= frameTime)
        {
            // Update rotation based on frame rate.
            currentRotation += rotationSpeed * frameTime;

            // Reset and Clear Color Buffer.
            ClearColorBuffer(backBuffer, totalPixels, bufferColor);
            ClearDepthBuffer(depthBuffer, totalPixels, FLT_MAX);

            // Reset cube world matrix  to start accumlation over.
            IdentityMatrix(cubeWorldMatrix);

            // Translate the cube upwards by 0.25 has to be done every frame to maintain it's location.
            Translate(cubeWorldMatrix, 0.0f, 0.25f, 0.0f);

            // Rotation of the cube.
            Matrix4x4 rotationMatrix;
            IdentityMatrix(rotationMatrix);
            Rotate(rotationMatrix, 'y', currentRotation);

            // Apply the rotation and translation.
            Matrix4x4 resultMatrix;
            MatrixMultiply(cubeWorldMatrix, rotationMatrix, resultMatrix);

            // Inverted View Matrix.
            Matrix4x4 invertedViewMatrix;
            IdentityMatrix(invertedViewMatrix);
            invertedViewMatrix = OrthonormalInverse(viewMatrix);

            // Draw Grid taking in all the translations.
            PixelShader = Green;
            DrawGrid(invertedViewMatrix, projectionMatrix);

            // Draw Cube taking in all the trasnlations with textures.
            DrawCubeWithTexture(resultMatrix, invertedViewMatrix, projectionMatrix, treeolife_pixels, treeolife_width, treeolife_height);

            // subtract frametime each time we execute.
            timer -= frameTime;
        }
    } while (RS_Update(backBuffer, static_cast<unsigned int>(totalPixels)));
}

// The Main.
int main()
{
    Main app;  // Create instance of Main.

    // Matrix Math Tests.
    //TestMatrixMultiplication();
    //TestAdvancedMatrixMultiplication();

    app.WindowUpdate();  // Run WindowUpdate.

    return 0;
}