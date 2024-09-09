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
	unsigned int bufferColor = 0xFF000000;
	unsigned int centerX = width / 2;
	unsigned int centerY = height / 2;
	unsigned int color[8] = { 0x00000000, 0xFFFFFFFF, 0xFFFF0000, 0xFF00FF00, 0xFF0000FF, 0xFFFFFF00, 0xFFFF00FF, 0xFF00FFFF };
	unsigned int black = color[0];
	unsigned int white = color[1];
	unsigned int red = color[2];
	unsigned int green = color[3];
	unsigned int blue = color[4];
	unsigned int yellow = color[5];
	unsigned int pink = color[6];
	unsigned int cyan = color[7];
};