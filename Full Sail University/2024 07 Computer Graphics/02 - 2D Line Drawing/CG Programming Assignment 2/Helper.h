#pragma once
#include <vector>

class Helper
{
public:
	Helper();
	~Helper();

	static void ClearColorBuffer(unsigned int* backBuffer, unsigned int totalPixels, unsigned int color);
	static void DrawPixel(unsigned int* backBuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int color);
	static bool Blit(const unsigned int* src, unsigned int srcWidth, unsigned int srcHeight, unsigned int srcRect[4], unsigned int* dst, unsigned dstWidth, unsigned dstHeight, int dstX, int dstY);
	static void Tiler(const unsigned int* src, unsigned int srcWidth, unsigned int srcHeight, unsigned int srcRect[4], unsigned int* dst, unsigned dstWidth, unsigned dstHeight, unsigned tileWidth, unsigned tileHeight);
	static void FireAnimator(const unsigned int* src, unsigned int srcWidth, unsigned int srcHeight, unsigned int* dst, unsigned int dstWidth, unsigned int dstHeight, unsigned int& currentFrame, int dstX, int dstY, unsigned int srcRect[4], unsigned int frameWidth, unsigned int frameHeight, unsigned int totalFrames);
	static void GenerateTreePositions(unsigned int minTrees, unsigned int maxTrees, unsigned int dstWidth, unsigned int dstHeight, std::vector<std::pair<int, int>>& treePositions);
	static void TreeSpawner(const unsigned int* src, unsigned int srcWidth, unsigned int srcHeight, unsigned int srcRect[4], unsigned int* dst, unsigned int dstWidth, unsigned int dstHeight, const std::vector<std::pair<int, int>>& treePositions);
	static void ParametricLine(unsigned int* backBuffer, int x1, int y1, int x2, int y2, unsigned int startingColor, unsigned int endingColor, unsigned int width);

private:
	static unsigned int Convert2Dto1D(unsigned int x, unsigned int y, unsigned int width);
	static unsigned int BGRAConverterToARGB(unsigned int colorBGRA);
	static unsigned int Lerp(int a, int b, float ratio);
	static unsigned int BlendByAlpha(int backGroundColor, int foreGroundColor);
	static unsigned int BlendLineColor(unsigned int startingColor, unsigned int endingColor, float ratio);
};