#include <iostream>
#include <vector>
#include <random>
#include "RasterSurface.h"
#include "tiles_12.h"
#include "fire_01b.h"
#include "XTime.h"
#include "Main.h"
#include "Helper.h"

// Constructor.
Main::Main() 
{
    backBuffer = new unsigned int[totalPixels];                         // 1D array for pixel data.
    Helper::ClearColorBuffer(backBuffer, totalPixels, bufferColor);     // Clear the Color Buffer to a solid color.
    RS_Initialize("Johnathan Richards", width, height);                 // Intialize the RasterSurface.
    srand(static_cast<unsigned int>(time(0)));                          // Intialize the Seed for extra randomness.
    Helper::GenerateTreePositions(5, 30, width, height, treePositions); // This generates the random positions and number of trees.
}

// Deconstructor.
Main::~Main()
{   
    delete[] backBuffer;    // Clean up of the array.
    RS_Shutdown();          // Shutdown and clear the RasterSurface.
}

void Main::WindowUpdate()
{
    // Selection - Left (x), Top (y), Right (x), Bottom (y).
    unsigned int srcRectForBackground[4] = { 288, 128, 319, 159 };
    unsigned int srcRectForTree[4] = { 316, 13, 388, 100 };
    unsigned int srcRectForFireAnimation[4] = { 0, 0, 127, 127 };

    // Calculate the width and height of the background selection.
    unsigned int tileWidthBackground = srcRectForBackground[2] - srcRectForBackground[0];
    unsigned int tileHeightBackground = srcRectForBackground[3] - srcRectForBackground[1];

    XTime time;                             // XTime intiate.
    float timeSinceLastFrame = 0.0f;        // Accumulate time.
    const float frameTime = 1.0f / 30.0f;   // Caculation for 30 fps.

    // Main while loop that updates pixels in the window for animations and drawing to window.
    do
    {
        // Collecting the time by signaling to Xtime and then adding the deltas of each update.
        time.Signal();
        timeSinceLastFrame += time.Delta();

        // Chech if time since last frame is greater than or equal to the 30 fps if os draw a new frame.
        if (timeSinceLastFrame >= frameTime)
        {
            // Using the Tiler here for Background.
            Helper::Tiler(tiles_12_pixels, tiles_12_width, tiles_12_height, srcRectForBackground, backBuffer, width, height, tileWidthBackground, tileHeightBackground);

            // Using the tree spawner to draw the trees.
            Helper::TreeSpawner(tiles_12_pixels, tiles_12_width, tiles_12_height, srcRectForTree, backBuffer, width, height, treePositions);

            // Using the fire animator to cycle through the fire frames.
            Helper::FireAnimator(fire_01b_pixels, fire_01b_width, fire_01b_height, backBuffer, width, height, currentFrame, fireAnimationCenterX, fireAnimationCenterY, srcRectForFireAnimation, 128, 128, 64);

            currentFrame = (currentFrame + 1) % 64; // Update frame index for the fire animation.
            timeSinceLastFrame -= frameTime;        // Reset time.
        }

        // the functions I called at different steps.
        //Helper::DrawPixel(backBuffer, centerX, centerY, width, 0xFF00FF00);
        //Helper::Blit(tiles_12_pixels, tiles_12_width, tiles_12_height, srcRect, backBuffer, width, height, centerX, centerY);

    } while (RS_Update(backBuffer, totalPixels));
}

int main()
{
    Main app;                   // Create instance of Main.
    app.WindowUpdate();         // Run WindowUpdate.    
    return 0;
}