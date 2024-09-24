#include <iostream>
#include "Main.h"
#include <iostream>
#include "Main.h"
#include "RasterFunction.h"
#include "RasterSurface.h"
#include "XTime.h"

// Constructor.
Main::Main()
{
    backBuffer = new unsigned int[totalPixels];             // 1D array for pixel data.
    ClearColorBuffer(backBuffer, totalPixels, bufferColor); // Clear the Color Buffer to a solid color.
    RS_Initialize("Johnathan Richards", width, height);     // Initialize the RasterSurface.
    InitializeMatrices();                                   // Initialize the matrices (world, view, projection)
}

// Destructor.
Main::~Main()
{
    delete[] backBuffer;                    // Clean up the array.
    RS_Shutdown();                          // Shutdown and clear the RasterSurface.
}

// Initialize the matrices.
void Main::InitializeMatrices()
{
    // Move cube slightly up by 0.25 units.
    IdentityMatrix(cubeWorldMatrix);
    Translate(cubeWorldMatrix, 0.0f, 0.25f, 0.0f);

    // Rotate the camera by -18 degrees on the X-axis and move backwards by 1.
    IdentityMatrix(viewMatrix);
    RotateX(viewMatrix, -18.0f);
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
        float deltaTime = time.Delta();
        timer += deltaTime;

        // FPS when timer reaches FPS then draw.
        if (timer >= frameTime)
        {
            // Update rotation based on frame rate.
            currentRotation += rotationSpeed * frameTime;

            // Reset and Clear Color Buffer.
            ClearColorBuffer(backBuffer, totalPixels, bufferColor);

            // Reset cube world matrix  to start accumlation over.
            IdentityMatrix(cubeWorldMatrix);

            // Translate the cube upwards by 0.25 has to be done every frame to maintain it's location.
            Translate(cubeWorldMatrix, 0.0f, 0.25f, 0.0f);

            // Rotation of the cube.
            Matrix4x4 rotationMatrix;
            IdentityMatrix(rotationMatrix);
            RotateY(rotationMatrix, currentRotation);

            // Apply the rotation and translation.
            Matrix4x4 resultMatrix;
            MatrixMultiply(cubeWorldMatrix, rotationMatrix, resultMatrix);

            // Inverted View Matrix.
            Matrix4x4 invertedViewMatrix;
            IdentityMatrix(invertedViewMatrix);
            invertedViewMatrix = OrthonormalInverse(viewMatrix);

            // Draw Grid taking in all the translations.
            DrawGrid(invertedViewMatrix, projectionMatrix);

            // Draw Cube taking in all the trasnlations.
            DrawCube(resultMatrix, invertedViewMatrix, projectionMatrix);

            timer = 0; // Reset the timer.
        }

    } while (RS_Update(backBuffer, totalPixels));
}

// The Main.
int main()
{
    Main app;  // Create instance of Main.

    // Matrix Math Tests.
    TestMatrixMultiplication();
    TestAdvancedMatrixMultiplication();

    app.WindowUpdate();  // Run WindowUpdate.

    return 0;
}







