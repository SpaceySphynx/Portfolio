#pragma once
#include <vector>
#include <iostream>
#include "StoneHenge.h"
#include "StoneHenge_Texture.h"
#include "RasterSurface.h"
#include "XTime.h"

// Color definitions in ARGB format.
const unsigned int BLACK = 0x00000000;
const unsigned int WHITE = 0xFFFFFFFF;
const unsigned int RED = 0xFFFF0000;
const unsigned int GREEN = 0xFF00FF00;
const unsigned int BLUE = 0xFF0000FF;
const unsigned int YELLOW = 0xFFFFFF00;
const unsigned int PINK = 0xFFFF00FF;
const unsigned int PALE_BLUE = 0xFFC0C0F0;
const unsigned int SKY_BLUE = 0xFF003366;
const unsigned int CYAN = 0xFF00FFFF;

const unsigned int SKYBOX_COLOR = BLACK;

// 4D Vector struct with positions, normals, colors, and texture coordinates.
struct Vector4
{
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 1.0f;

	unsigned int color = WHITE;

	// UV coordinates for texture mapping.
	float u = 0;
	float v = 0;

	// Normals for Lightning.
	float normalX = 0;
	float normalY = 0;
	float normalZ = 0;

	// Set UV coordinates.
	void SetUV(float _u, float _v)
	{
		u = _u;
		v = _v;
	}

	// Set normal vector for lighting calculations.
	void SetNormalVector(float _normalX, float _normalY, float _normalZ)
	{
		normalX = _normalX;
		normalY = _normalY;
		normalZ = _normalZ;
	}

	// Calculate the distance between two points.
	float Distance(Vector4 other)
	{
		return std::sqrt(std::pow(other.x - x, 2) + std::pow(other.y - y, 2) + std::pow(other.z - z, 2));
	}

	// Constructors.
	Vector4(float _x, float _y, float _z, float _w, unsigned int _color)
		: x(_x), y(_y), z(_z), w(_w), color(_color) {}

	Vector4(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z), w(1.0f) {}

	Vector4() = default;

	// Operator overload to scale the vector.
	Vector4& operator*=(float multiplier)
	{
		x *= multiplier;
		y *= multiplier;
		z *= multiplier;
		return *this;
	}

	Vector4& operator/=(float divisor)
	{
		x /= divisor;
		y /= divisor;
		z /= divisor;
		u /= divisor;
		v /= divisor;
		return *this;
	}

	// Operator overload to subtract vectors.
	Vector4 operator-(const Vector4& other) const
	{
		return Vector4(x - other.x, y - other.y, z - other.z);
	}
};

// 2D Vector struct used for screen coordinates and pixel manipulation.
struct Vector2
{
	int x = 0;
	int y = 0;
	unsigned int color = WHITE;

	// Constructors.
	Vector2(int _x, int _y) : x(_x), y(_y) {}
	Vector2() = default;

	// Swap the values of two Vector2 instances.
	void Swap(Vector2& other)
	{
		Vector2 temp = *this;
		*this = other;
		other = temp;
	}
};

// 4x4 Matrix struct used for translation, rotation, and scaling.
struct Matrix4x4
{
	float matrix[4][4] =
	{
		{1.0f, 0.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}
	};

	// Constructor to initialize with a 2D array.
	Matrix4x4(float _matrix[4][4])
	{
		for (int i = 0; i < 4; i++) 
		{
			for (int j = 0; j < 4; j++) 
			{
				matrix[i][j] = _matrix[i][j];
			}
		}
	}

	Matrix4x4() = default;

	Matrix4x4 TranslationMatrix()
	{
		float temp[4][4] = 
		{
			{1.0f, 0.0f, 0.0f, matrix[0][3]},
			{0.0f, 1.0f, 0.0f, matrix[1][3]},
			{0.0f, 0.0f, 1.0f, matrix[2][3]},
			{0.0f, 0.0f, 0.0f, 1.0f}
		};

		return Matrix4x4(temp);
	}

	// Overload operator for matrix access.
	float* operator[](int row)
	{
		return matrix[row];
	}
};

// Triangle structure, consisting of three Vector4 vertices.
struct Triangle
{
	Vector4 vertexA;
	Vector4 vertexB;
	Vector4 vertexC;
	bool isClipped = false;

	// Constructors.
	Triangle(const Vector4& _vertexA, const Vector4& _vertexB, const Vector4& _vertexC)
		: vertexA(_vertexA), vertexB(_vertexB), vertexC(_vertexC) {}

	Triangle() = default;

	// Sort triangle vertices by their Y-coordinates.
	Vector4* SortByY()
	{
		static Vector4 arr[3] = { vertexA, vertexB, vertexC };
		if (vertexA.y >= vertexB.y)
		{
			if (vertexB.y >= vertexC.y)
			{
				arr[0] = vertexA; arr[1] = vertexB; arr[2] = vertexC;
			}
			else
			{
				arr[0] = (vertexC.y >= vertexA.y) ? vertexC : vertexA;
				arr[1] = (vertexC.y >= vertexA.y) ? vertexA : vertexC;
				arr[2] = vertexB;
			}
		}
		else
		{
			arr[0] = (vertexB.y >= vertexC.y) ? vertexB : vertexC;
			arr[1] = (vertexC.y >= vertexA.y) ? vertexC : vertexA;
			arr[2] = (vertexC.y >= vertexA.y) ? vertexA : vertexC;
		}
		return arr;
	}
};


struct ColorComponents
{
	unsigned int a;
	unsigned int r;
	unsigned int g;
	unsigned int b;
};

// Identity matrix for initializing world matrices.
float identityMatrix[4][4] =
{
	{1.0f, 0.0f, 0.0f, 0.0f},
	{0.0f, 1.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 1.0f, 0.0f},
	{0.0f, 0.0f, 0.0f, 1.0f}
};

// Global matrices for transformations
Matrix4x4 worldMatrixLight(identityMatrix);
Matrix4x4 worldMatrixView(identityMatrix);

// Lighting information.
Vector4 directionalLight = { -0.6f, -0.6f, 0.6f, 1.0f, PALE_BLUE };
Vector4 pointLight = { -1.0f, 0.5f, 1.0f, 1.0f, YELLOW };
Vector4	viewRotationInfo = { 0.0f, 0.0f, 0.0f };
Vector4	lightRotationInfo = { 0.0f, 0.0f, 0.0f };

// Screen resolution and aspect ratio.
const unsigned int SCREEN_WIDTH = 900;		// Screen width.
const unsigned int SCREEN_HEIGHT = 500;	// Screen height.
const size_t TOTAL_SCREEN_PIXELS = static_cast<size_t>(SCREEN_WIDTH) * static_cast<size_t>(SCREEN_HEIGHT);  // Total number of pixels.
const float ASPECT_RATIO = static_cast<float>(SCREEN_HEIGHT) / static_cast<float>(SCREEN_WIDTH);

// Math variables.
const float PI = 3.1415927f;

// Lighting parameters.
float pointLightRadius = 5.0f;
float cameraHorizontalAxisSpeed = 100.0f;
float cameraVerticalAxisSpeed = 100.0f;
float cameraMovementSpeed = 1.0f;
float cameraFOV = 90.0f;
float zNear = 0.1f;
float zFar = 10.0f;
float ambientLightingIntensity = 0.2f;

std::vector<Vector4> starsArray(3500);
std::vector<Triangle> triangleArray;
std::vector<unsigned int> backBuffer(SCREEN_WIDTH * SCREEN_HEIGHT);
std::vector<float> depthBuffer(SCREEN_WIDTH * SCREEN_HEIGHT);

// Function pointers for shaders.
Triangle(*VertexShaderWithClipTriangle)(Vector4&, Vector4&, Vector4&, bool&) = nullptr;
void (*VertexShader)(Vector4&) = nullptr;
void (*VertexShaderWithClip)(Vector4&, Vector4&, bool&) = nullptr;
void (*pixelShader)(Vector2&) = nullptr;
void (*UVShader)(Vector2& pixel, float u, float v, int width, int height, const unsigned int arr[], int size) = nullptr;