#pragma once

class Main
{
public:
	Main();
	~Main();

	void WindowUpdate();

private:

	// Window dimensions and other initialization variables.
	unsigned int width = 500;
	unsigned int height = 500;
	unsigned int totalPixels = height * width;
	unsigned int* backBuffer = nullptr;
	unsigned int bufferColor = 0xFFFF00FF;
	unsigned int centerX = width / 2;
	unsigned int centerY = height / 2;
	unsigned int currentFrame = 0;
	int fireAnimationCenterX = (width - 128) / 2;
	int fireAnimationCenterY = (height - 128) / 2;
	std::vector<std::pair<int, int>> treePositions;

};