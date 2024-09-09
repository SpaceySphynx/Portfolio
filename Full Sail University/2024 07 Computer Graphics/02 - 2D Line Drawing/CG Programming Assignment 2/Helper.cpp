#include "Helper.h"
#include <random>

// Helper Functions

// Clear the Color Buffer with a solid color.
void Helper::ClearColorBuffer(unsigned int* backBuffer, unsigned int totalPixels, unsigned int color)
{
    for (unsigned int i = 0; i < totalPixels; ++i)
    {
        backBuffer[i] = color;
    }
}

// Convert x,y coordinates to 1D.
unsigned int Helper::Convert2Dto1D(unsigned int x, unsigned int y, unsigned int width)
{
    return y * width + x;
}

// Draw Pixels to the window.
void Helper::DrawPixel(unsigned int* backBuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int color)
{
    unsigned int i = Helper::Convert2Dto1D(x, y, width);
    backBuffer[i] = color;
}

// Lerp formuala helper function.
unsigned int Helper::Lerp(int a, int b, float ratio)
{
    return static_cast<unsigned int>(a + (b - a) * ratio);
}

// Helper Function for blending colors.
unsigned int Helper::BlendByAlpha(int backGroundColor, int foreGroundColor)
{
    // Extracted background RGBA components.
    int backGroundA = (backGroundColor & 0xFF000000) >> 24;
    int backGroundR = (backGroundColor & 0x00FF0000) >> 16;
    int backGroundG = (backGroundColor & 0x0000FF00) >> 8;
    int backGroundB = (backGroundColor & 0x000000FF);

    // Extracted foreground RGBA components.
    int foreGroundA = (foreGroundColor & 0xFF000000) >> 24;
    int foreGroundR = (foreGroundColor & 0x00FF0000) >> 16;
    int foreGroundG = (foreGroundColor & 0x0000FF00) >> 8;
    int foreGroundB = (foreGroundColor & 0x000000FF);

    // Calculated the blending ratio by making it into a percentage.
    float alphaRatio = foreGroundA / 255.0f;

    // Used LERP to blend each color channel.
    int R = Lerp(backGroundR, foreGroundR, alphaRatio);
    int G = Lerp(backGroundG, foreGroundG, alphaRatio);
    int B = Lerp(backGroundB, foreGroundB, alphaRatio);

    // Blended the alpha channel.
    int A = Lerp(backGroundA, foreGroundA, alphaRatio);

    // Recombined the channels.
    return (A << 24) | (R << 16) | (G << 8) | B;
}

unsigned int Helper::BlendLineColor(unsigned int startingColor, unsigned int endingColor, float ratio)
{
    // Extract color components from both the starting and ending colors
    unsigned int startR = (startingColor & 0x00FF0000) >> 16;
    unsigned int startG = (startingColor & 0x0000FF00) >> 8;
    unsigned int startB = (startingColor & 0x000000FF);
    unsigned int startA = (startingColor & 0xFF000000) >> 24;

    unsigned int endR = (endingColor & 0x00FF0000) >> 16;
    unsigned int endG = (endingColor & 0x0000FF00) >> 8;
    unsigned int endB = (endingColor & 0x000000FF);
    unsigned int endA = (endingColor & 0xFF000000) >> 24;

    // Use LERP for each color channel
    unsigned int currR = Lerp(startR, endR, ratio);
    unsigned int currG = Lerp(startG, endG, ratio);
    unsigned int currB = Lerp(startB, endB, ratio);
    unsigned int currA = Lerp(startA, endA, ratio);

    // Recombine the interpolated channels into a single ARGB color value
    return (currA << 24) | (currR << 16) | (currG << 8) | currB;
}

// Draw selection from source image to destination window at specific x,y for top left.
bool Helper::Blit(const unsigned int* src, unsigned int srcWidth, unsigned int srcHeight, unsigned int srcRect[4], unsigned int* dst, unsigned dstWidth, unsigned dstHeight, int dstX, int dstY)
{
    // The corners of the selection square extracted.
    unsigned int left = srcRect[0];
    unsigned int top = srcRect[1];
    unsigned int right = srcRect[2];
    unsigned int bottom = srcRect[3];

    // Calculate width and height of rectangle.
    unsigned int rectWidth = right - left;
    unsigned int rectHeight = bottom - top;

    // The BLIT Loop.
    for (unsigned int y = 0; y < rectHeight; ++y)
    {
        for (unsigned int x = 0; x < rectWidth; ++x)
        {
            // Skip drawing if out of bounds otherwise I get an memory access exception.
            if ((dstX + x) >= dstWidth || (dstY + y) >= dstHeight)
            {
                continue;
            }

            // Converts from x,y to 1D from source then destination.
            unsigned int srcIndex = Helper::Convert2Dto1D(left + x, top + y, srcWidth);

            // Converts the current pixel array index to ARGB.
            unsigned int colorARGB = BGRAConverterToARGB(src[srcIndex]);

            // Check if the pixel is transparent.
            unsigned int alpha = (colorARGB & 0xFF000000) >> 24;

            // Only copy a pixel if it is not transparent.
            if (alpha > 0)
            {
                // Convert alpha to alpha percentage.
                float alphaPercent = alpha / 255.0f;

                // Determines the destination array index, found this to be easier than unconverting.
                unsigned int dstIndex = Helper::Convert2Dto1D(dstX + x, dstY + y, dstWidth);

                // Get destination color from the index.
                unsigned int dstColor = dst[dstIndex];

                // Blend the color then copy back to the destination.
                unsigned int blendedColor = Helper::BlendByAlpha(dstColor, colorARGB);
                dst[dstIndex] = blendedColor;
            }
        }
    }
    return true;
}

// BLIT Tiler for the background.
void Helper::Tiler(const unsigned int* src, unsigned int srcWidth, unsigned int srcHeight, unsigned int srcRect[4], unsigned int* dst, unsigned int dstWidth, unsigned int dstHeight, unsigned int tileWidth, unsigned int tileHeight)
{
    // Loop to tile the BLIT.
    for (unsigned int y = 0; y < dstHeight; y += tileHeight)
    {
        for (unsigned int x = 0; x < dstWidth; x += tileWidth)
        {
            Helper::Blit(src, srcWidth, srcHeight, srcRect, dst, dstWidth, dstHeight, x, y);
        }
    }
}

// BGRA To ARGB Converter.
unsigned int Helper::BGRAConverterToARGB(unsigned int colorBGRA)
{
    // Bit shifting with a mask.
    unsigned int blue = (colorBGRA & 0xFF000000) >> 24;
    unsigned int green = (colorBGRA & 0x00FF0000) >> 8;
    unsigned int red = (colorBGRA & 0x0000FF00) << 8;
    unsigned int alpha = (colorBGRA & 0x000000FF) << 24;

    // Return the recombined ARGB.
    return (alpha | red | green | blue);
}

void Helper::GenerateTreePositions(unsigned int minTrees, unsigned int maxTrees, unsigned int dstWidth, unsigned int dstHeight, std::vector<std::pair<int, int>>& treePositions)
{
    // Random Seed latest version.
    std::random_device rd;
    std::mt19937 gen(rd());

    // Generate random number of trees to spawn, keep to a uniform distribution.
    std::uniform_int_distribution<> treeDist(minTrees, maxTrees);

    // Generate random positions within the window for the 0,0 pixel.
    std::uniform_int_distribution<> xPosDist(0, dstWidth - 1);
    std::uniform_int_distribution<> yPosDist(0, dstHeight - 1);

    // The number of trees that got generated.
    unsigned int numObjects = treeDist(gen);

    // Loop to draw the trees.
    for (unsigned int i = 0; i < numObjects; ++i)
    {
        int randX = xPosDist(gen);
        int randY = yPosDist(gen);

        treePositions.push_back({ randX, randY });
    }
}

// Random Tree Spawner.
void Helper::TreeSpawner(const unsigned int* src, unsigned int srcWidth, unsigned int srcHeight, unsigned int srcRect[4], unsigned int* dst, unsigned int dstWidth, unsigned int dstHeight, const std::vector<std::pair<int, int>>& treePositions)
{
    for (const auto& pos : treePositions)
    {
        Helper::Blit(src, srcWidth, srcHeight, srcRect, dst, dstWidth, dstHeight, pos.first, pos.second);
    }
}

// Animator for fire.
void Helper::FireAnimator(const unsigned int* src, unsigned int srcWidth, unsigned int srcHeight, unsigned int* dst, unsigned int dstWidth, unsigned int dstHeight, unsigned int& currentFrame, int dstX, int dstY, unsigned int srcRect[4], unsigned int frameWidth, unsigned int frameHeight, unsigned int totalFrames)
{
    // Initial frame bounds from the provided srcRect.
    unsigned int left = srcRect[0];
    unsigned int top = srcRect[1];

    // Calculates the x and y positions for the current frame. Modulo allows to start back at the beginning for the x.
    unsigned int xPos = (currentFrame % (srcWidth / frameWidth)) * frameWidth + left;
    unsigned int yPos = (currentFrame / (srcWidth / frameWidth)) * frameHeight + top;

    // Set up the source rectangle for the current frame, relative to the initial srcRect.
    unsigned int frameRect[4] = { xPos, yPos, xPos + frameWidth, yPos + frameHeight };

    // Blit the current frame to the destination.
    Helper::Blit(src, srcWidth, srcHeight, frameRect, dst, dstWidth, dstHeight, dstX, dstY);
}

// Draw lines using Parametric Line Algorithm.
void Helper::ParametricLine(unsigned int* backBuffer, int x1, int y1, int x2, int y2, unsigned int startingColor, unsigned int endingColor, unsigned int width)
{
    // Find the deltas of x and y.
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

        // Loop long as x1 is less than or equsl to x2. 
        for (int x = x1; x <= x2; ++x)
        {
            // Calculate interpolation ratio along the X-axis for LERP and Blend.
            float ratio = static_cast<float>(x - x1) / deltaX;

            // Interpolating the Y value using LERP.
            float currYFloat = Lerp(y1, y2, ratio);

            // Apply floor rounding to minimize the errors.
            int currY = static_cast<int>(floor(currYFloat + 0.5f));

            // Blend colors based on the ratio.
            unsigned int currentColor = BlendLineColor(startingColor, endingColor, ratio);

            // Draw the pixel.
            DrawPixel(backBuffer, x, currY, width, currentColor);
        }
    }

    // If the absolute value is deltaX is less than the absolute value of deltaY (More vertial than horizontal).
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

        // Loop long as y1 is less than or equsl to y2. 
        for (int y = y1; y <= y2; ++y)
        {
            // Calculate interpolation ratio along the Y-axis for LERP and Blend.
            float ratio = static_cast<float>(y - y1) / deltaY;

            // Interpolate the X value using LERP.
            float currXFloat = Lerp(x1, x2, ratio);

            // Apply floor rounding to minimize rounding errors.
            int currX = static_cast<int>(floor(currXFloat + 0.5f));

            // Blend colors based on the ratio.
            unsigned int currentColor = BlendLineColor(startingColor, endingColor, ratio);

            // Draw the pixel.
            DrawPixel(backBuffer, currX, y, width, currentColor);
        }
    }
}