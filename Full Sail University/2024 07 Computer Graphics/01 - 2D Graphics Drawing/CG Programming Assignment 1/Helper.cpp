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
unsigned int Helper::Blend(int backGroundColor, int foreGroundColor)
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
                unsigned int blendedColor = Helper::Blend(dstColor, colorARGB);
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

    // Move to the next frame and cycle back after the total frames are reached.
    currentFrame = (currentFrame + 1) % totalFrames;
}