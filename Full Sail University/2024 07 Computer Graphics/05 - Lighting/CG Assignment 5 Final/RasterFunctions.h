#include "Shaders.h"

// Draws a pixel to the screen buffer at a specific position with the given color.
void DrawPixel(unsigned int pixelPosition, unsigned int color)
{
	if (pixelPosition >= TOTAL_SCREEN_PIXELS || pixelPosition < 0)
		return;
	backBuffer[pixelPosition] = color;
}

// Clears the depth buffer by resetting all values to 0.
void ClearDepthBuffer()
{
	for (size_t i = 0; i < TOTAL_SCREEN_PIXELS; i++)
	{
		depthBuffer[i] = 0;
	}
}

// Clears the screen buffer by filling it with a solid black color.
void ClearScreenBuffer()
{
	for (size_t i = 0; i < TOTAL_SCREEN_PIXELS; i++)
	{
		backBuffer[i] = BLACK;
	}
}

// Performs a depth buffer check and updates the screen with the given pixel if the depth is closer.
void ZBufferCheck(unsigned int pixelPos, unsigned int color, float depth)
{
	if (pixelPos >= TOTAL_SCREEN_PIXELS || pixelPos < 0)
		return;

	// If the new depth is less than or equal to the current depth, draw the pixel.
	if (depth <= depthBuffer[pixelPos])
	{
		depthBuffer[pixelPos] = depth;
		DrawPixel(pixelPos, color);
	}
	// If the depth buffer is zero (unused), also draw the pixel.
	else if (depthBuffer[pixelPos] == 0)
	{
		depthBuffer[pixelPos] = depth;
		DrawPixel(pixelPos, color);
	}
}

// Rasterizes a triangle using a brute-force method, including clipping, shading, and z-buffering.
void RasterizeTriangleUsingBetterBrute(Triangle triangle)
{
	if (!VertexShaderWithClipTriangle)
		return;

	bool isClipped = false;

	// Check if the triangle is clipped and apply transformations.
	if (!triangle.isClipped)
	{
		Triangle clippedTriangle = VertexShaderWithClipTriangle(triangle.vertexA, triangle.vertexB, triangle.vertexC, isClipped);
		Vector4 faceDirection = CrossProduct(triangle.vertexA - triangle.vertexB, triangle.vertexC - triangle.vertexB);

		// If the face direction indicates back-facing, skip this triangle.
		if (faceDirection.z < 0)
			return;

		// If the triangle is clipped, recursively rasterize the clipped triangle.
		if (isClipped)
			return;

		if (clippedTriangle.isClipped && !triangle.isClipped)
			RasterizeTriangleUsingBetterBrute(clippedTriangle);
	}

	// Convert NDC (Normalized Device Coordinates) to 2D for triangle vertices.
	Vector2 vertexA = ConvertNDCto2D(triangle.vertexA);
	Vector2 vertexB = ConvertNDCto2D(triangle.vertexB);
	Vector2 vertexC = ConvertNDCto2D(triangle.vertexC);

	float startX, startY, endX, endY;

	// Calculate the bounding box for the triangle.
	CalculateBoundingBox(vertexA, vertexB, vertexC, startX, startY, endX, endY);

	// Loop through the bounding box area and rasterize the triangle.
	for (int j = startY; j < endY; j++)
	{
		bool firstTry = true;
		for (int i = startX; i < endX; i++)
		{
			Vector2 currPosition(i, j);
			Vector4 result = FindBarycentricCoordinate(currPosition, triangle);

			// Check if the current pixel is inside the triangle using barycentric coordinates.
			if (result.x >= 0 && result.x <= 1 && result.y >= 0 && result.y <= 1 && result.z >= 0 && result.z <= 1)
			{
				int pos = PixelConversion(currPosition.x, currPosition.y, SCREEN_WIDTH);

				float u, v, depth;

				// Calculate UV coordinates and depth for this pixel.
				CalculateUVandDepth(triangle, result, u, v, depth);

				// Apply the UV texture shader.
				UVShader(currPosition, u, v, StoneHenge_width, StoneHenge_height, StoneHenge_pixels, StoneHenge_numpixels);

				// Blend the colors from the triangle's vertices using the barycentric weights.
				unsigned int colorA = MultiplyColor(triangle.vertexA.color, result.z);
				unsigned int colorB = MultiplyColor(triangle.vertexB.color, result.x);
				unsigned int colorC = MultiplyColor(triangle.vertexC.color, result.y);
				unsigned int c = AdditiveColor(AdditiveColor(colorA, colorB), colorC);
				unsigned int finalColor = ModulateColors(currPosition.color, c);

				// Perform z-buffering and draw the pixel.
				ZBufferCheck(pos, finalColor, depth);
			}
		}
	}
}

// Rasterizes a line using parametric line drawing, applying depth and z-buffer checks.
void ParametricConversion(Vector2 startPoint, Vector2 endPoint, float z1, float z2)
{
	Vector2 _startPoint;
	Vector2 _endPoint;
	bool swapped = false;

	// Ensure the start point is on the left side for consistency.
	if (startPoint.x > endPoint.x)
	{
		_startPoint = endPoint;
		_endPoint = startPoint;
		swapped = true;
	}
	else
	{
		_startPoint = startPoint;
		_endPoint = endPoint;
	}

	if (pixelShader)
	{
		pixelShader(_startPoint);
		pixelShader(_endPoint);
	}

	int deltaX = _endPoint.x - _startPoint.x;
	int deltaY = (int)_endPoint.y - (int)_startPoint.y;

	// Vertical or steep lines rspecial handling.
	if ((deltaY < 0 ? -deltaY : deltaY) > deltaX)
	{
		float temp = z1;
		z1 = z2;
		z2 = temp;
		if (_startPoint.y > _endPoint.y)
			_startPoint.Swap(_endPoint);

		// Loop through the y-range and draw vertical lines.
		for (int i = _startPoint.y < 0 ? 0 : _startPoint.y; i < _endPoint.y; i++)
		{
			float ratio = deltaY == 0 ? 0 : (i - _startPoint.y) / (float)deltaY;
			float currX = deltaX * ratio + _startPoint.x;
			int finalX = (currX + 0.5f) * 1;
			float depth = (z2 - z1) * ratio + z1;
			ZBufferCheck(PixelConversion(finalX, i, SCREEN_WIDTH), _startPoint.color, depth);
		}
	}
	else
	{
		if (swapped)
		{
			float temp = z1;
			z1 = z2;
			z2 = temp;
		}

		// Loop through the x-range and draw horizontal lines.
		for (int i = _startPoint.x < 0 ? 0 : _startPoint.x; i <= _endPoint.x; i++)
		{
			float ratio = deltaX == 0 ? 0 : (i - _startPoint.x) / (float)deltaX;
			float currY = deltaY * ratio + _startPoint.y;
			int finalY = (currY + 0.5f) * 1;
			float depth = (z2 - z1) * ratio + z1;
			ZBufferCheck(PixelConversion(i, finalY, SCREEN_WIDTH), _startPoint.color, depth);
		}
	}
}

// Transforms the vertex for star rendering by applying view and projection matrices.
void TransformVertexForStars(Vector4& vertex)
{
	Matrix4x4 tempMatrixView = worldMatrixView;
	InverseMatrix(tempMatrixView);

	MultiplyVectorByMatrix4x4(vertex, tempMatrixView);
	MultiplyVectorByMatrix4x4(vertex, worldMatrixProjection);

	vertex /= vertex.w;
}

// Draws a 3D pixels.
void Draw3Dpixel(Vector4 vertex)
{
	TransformVertexForStars(vertex);

	Vector2 currPos = ConvertNDCto2D(vertex);

	// Ensure the pixel is within screen boundaries.
	if (currPos.x < 0 || currPos.x >= SCREEN_WIDTH || currPos.y < 0 || currPos.y >= SCREEN_HEIGHT)
		return;

	if (pixelShader)
		pixelShader(currPos);

	ZBufferCheck(PixelConversion(currPos.x, currPos.y, SCREEN_WIDTH), currPos.color, vertex.z);
}

// Loads the 3D model into an array of triangles for rendering.
void LoadModel()
{
	for (int i = 0; i < 2532; i += 3)
	{
		Triangle tempTri;
		tempTri.vertexA = { StoneHenge_data[StoneHenge_indicies[i]].pos[0], StoneHenge_data[StoneHenge_indicies[i]].pos[1], StoneHenge_data[StoneHenge_indicies[i]].pos[2] };
		tempTri.vertexB = { StoneHenge_data[StoneHenge_indicies[i + 1]].pos[0], StoneHenge_data[StoneHenge_indicies[i + 1]].pos[1], StoneHenge_data[StoneHenge_indicies[i + 1]].pos[2] };
		tempTri.vertexC = { StoneHenge_data[StoneHenge_indicies[i + 2]].pos[0], StoneHenge_data[StoneHenge_indicies[i + 2]].pos[1], StoneHenge_data[StoneHenge_indicies[i + 2]].pos[2] };
		tempTri.vertexA *= 0.1f;
		tempTri.vertexB *= 0.1f;
		tempTri.vertexC *= 0.1f;
		tempTri.vertexA.SetUV(StoneHenge_data[StoneHenge_indicies[i]].uvw[0], StoneHenge_data[StoneHenge_indicies[i]].uvw[1]);
		tempTri.vertexB.SetUV(StoneHenge_data[StoneHenge_indicies[i + 1]].uvw[0], StoneHenge_data[StoneHenge_indicies[i + 1]].uvw[1]);
		tempTri.vertexC.SetUV(StoneHenge_data[StoneHenge_indicies[i + 2]].uvw[0], StoneHenge_data[StoneHenge_indicies[i + 2]].uvw[1]);
		tempTri.vertexA.SetNormalVector(StoneHenge_data[StoneHenge_indicies[i]].nrm[0], StoneHenge_data[StoneHenge_indicies[i]].nrm[1], StoneHenge_data[StoneHenge_indicies[i]].nrm[2]);
		tempTri.vertexB.SetNormalVector(StoneHenge_data[StoneHenge_indicies[i + 1]].nrm[0], StoneHenge_data[StoneHenge_indicies[i + 1]].nrm[1], StoneHenge_data[StoneHenge_indicies[i + 1]].nrm[2]);
		tempTri.vertexC.SetNormalVector(StoneHenge_data[StoneHenge_indicies[i + 2]].nrm[0], StoneHenge_data[StoneHenge_indicies[i + 2]].nrm[1], StoneHenge_data[StoneHenge_indicies[i + 2]].nrm[2]);
		triangleArray.push_back(tempTri);
	}
}

// Renders the 3D model by rasterizing each triangle.
void RenderModel()
{
	for (int i = 0; i < triangleArray.size(); i++)
	{
		RasterizeTriangleUsingBetterBrute(triangleArray[i]);
	}
}

// Generates a skybox with random star positions.
void GenerateSkybox()
{
	for (int i = 0; i < 3000; i++)
	{
		Vector4 starPos;
		starPos.x = (float)rand() / RAND_MAX * ((float)rand() / RAND_MAX > 0.5 ? 1 : -1) * 50;
		starPos.y = (float)rand() / RAND_MAX * ((float)rand() / RAND_MAX > 0.5 ? 1 : -1) * 50;
		starPos.z = (float)rand() / RAND_MAX * ((float)rand() / RAND_MAX > 0.5 ? 1 : -1) * 50;
		starsArray[i] = starPos;
	}
}

// Draws the skybox with stars.
void DrawStars()
{
	for (int i = 0; i < TOTAL_SCREEN_PIXELS; i++)
	{
		backBuffer[i] = SKYBOX_COLOR;
	}

	for (int i = 0; i < 3000; i++)
	{
		Draw3Dpixel(starsArray[i]);
	}
}