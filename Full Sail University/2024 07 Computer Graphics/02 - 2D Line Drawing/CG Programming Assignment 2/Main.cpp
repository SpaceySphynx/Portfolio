#include "RasterSurface.h"
#include "Main.h"
#include "Helper.h"
#include "XTime.h"

// Constructor.
Main::Main()
{
    backBuffer = new unsigned int[totalPixels];                     // 1D array for pixel data.
    Helper::ClearColorBuffer(backBuffer, totalPixels, bufferColor); // Clear the Color Buffer to a solid color.
    RS_Initialize("Johnathan Richards", width, height);             // Initialize the RasterSurface.
}

// Destructor.
Main::~Main()
{
    delete[] backBuffer;                    // Clean up the array.
    RS_Shutdown();                          // Shutdown and clear the RasterSurface.
}

void Main::WindowUpdate()
{
    XTime time;                             // XTime initiate.
    float timeSinceLastFrame = 0.0f;        // Accumulate time.
    const float frameTime = 1.0f / 30.0f;   // Calculation for 30 fps.

    do
    {
        time.Signal();
        timeSinceLastFrame += time.Delta();

        // Set this to 30 fps for drawing.
        if (timeSinceLastFrame >= frameTime)
        {
            Helper::ClearColorBuffer(backBuffer, totalPixels, bufferColor);                 // Clear the buffer.

            // Draw Octagon.
            Helper::ParametricLine(backBuffer, 150, 50, 350, 50, white, white, width);      // Top edge.
            Helper::ParametricLine(backBuffer, 350, 50, 450, 150, white, yellow, width);    // Top-right edge.
            Helper::ParametricLine(backBuffer, 450, 150, 450, 350, yellow, green, width);   // Right edge.
            Helper::ParametricLine(backBuffer, 450, 350, 350, 450, green, cyan, width);     // Bottom-right edge.
            Helper::ParametricLine(backBuffer, 350, 450, 150, 450, cyan, blue, width);      // Bottom edge.
            Helper::ParametricLine(backBuffer, 150, 450, 50, 350, blue, pink, width);       // Bottom-left edge.
            Helper::ParametricLine(backBuffer, 50, 350, 50, 150, pink, red, width);         // Left edge.
            Helper::ParametricLine(backBuffer, 50, 150, 150, 50, red, white, width);        // Top-left edge.

            // Draw lines that cross through the center.
            Helper::ParametricLine(backBuffer, 150, 50, 350, 450, white, cyan, width);      // Diagonal top-left to bottom-right.
            Helper::ParametricLine(backBuffer, 350, 50, 150, 450, white, blue, width);      // Diagonal top-right to bottom-left.
            Helper::ParametricLine(backBuffer, 450, 150, 50, 350, yellow, pink, width);     // Diagonal right-top to left-bottom.
            Helper::ParametricLine(backBuffer, 450, 350, 50, 150, green, red, width);       // Diagonal right-bottom to left-top.

            timeSinceLastFrame -= frameTime;  // Reset time.
        }
    } while (RS_Update(backBuffer, totalPixels));
}

int main()
{
    Main app;               // Create instance of Main.
    app.WindowUpdate();     // Run WindowUpdate.
    return 0;
}