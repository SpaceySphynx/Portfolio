#include "Defines.h"

// Extract color components into a ColorComponents struct.
ColorComponents ExtractColorComponents(unsigned int color)
{
    return 
    {
        (color >> 24) & 0xFF,   // Alpha
        (color >> 16) & 0xFF,   // Red
        (color >> 8) & 0xFF,    // Green
        color & 0xFF            // Blue
    };
}

// Helper function to combine color components back.
inline unsigned int CombineColorComponents(const ColorComponents& color)
{
    return (color.a << 24) | (color.r << 16) | (color.g << 8) | color.b;
}

// Converts degrees to radians
inline float DegreesToRadians(float degrees)
{
    return degrees * (PI / 180);
}

// Calculates the cotangent of an angle
inline float Cot(float degrees)
{
    return cos(DegreesToRadians(degrees)) / sin(DegreesToRadians(degrees));
}

// Converts pixel coordinates.
inline int PixelConversion(int x, int y, unsigned int width)
{
    return y * width + x;
}

// Calculates the dot product of two vectors.
inline float DotProduct(Vector4 vertex1, Vector4 vertex2)
{
    return vertex1.x * vertex2.x + vertex1.y * vertex2.y + vertex1.z * vertex2.z;
}

inline float ImplicitLineEquation(Vector2 trigA, Vector2 trigB, Vector2 trigC)
{
    return (trigB.y - trigC.y) * trigA.x + (trigC.x - trigB.x) * trigA.y + trigB.x * trigC.y - trigB.y * trigC.x;
}

// Scaling factors for field of view.
float yScale = Cot(cameraFOV / 2);
float xScale = yScale * ASPECT_RATIO;

// Clamps a value within a range.
float Clamp(float input, float upper, float lower)
{
    if (input > upper)
        input = upper;
    else if (input < lower)
        input = lower;
    return input;
}

// Cycles a value between upper and lower bounds.
float Cycle(float input, float upper, float lower)
{
    if (input > upper)
        input = lower;
    else if (input < lower)
        input = upper;
    return input;
}

// Multiplies a vector by a 4x4 matrix.
void MultiplyVectorByMatrix4x4(Vector4& vertex, Matrix4x4& matrix)
{
    float _x = matrix[0][0] * vertex.x + matrix[0][1] * vertex.y + matrix[0][2] * vertex.z + matrix[0][3] * vertex.w;
    float _y = matrix[1][0] * vertex.x + matrix[1][1] * vertex.y + matrix[1][2] * vertex.z + matrix[1][3] * vertex.w;
    float _z = matrix[2][0] * vertex.x + matrix[2][1] * vertex.y + matrix[2][2] * vertex.z + matrix[2][3] * vertex.w;
    float _w = matrix[3][0] * vertex.x + matrix[3][1] * vertex.y + matrix[3][2] * vertex.z + matrix[3][3] * vertex.w;

    vertex.x = _x;
    vertex.y = _y;
    vertex.z = _z;
    vertex.w = _w;
}

// Multiplies a vector by a 3x3 matrix.
void MultiplyVectorByMatrix3x3(Vector4& vertex, Matrix4x4& matrix)
{
    float _x = matrix[0][0] * vertex.x + matrix[0][1] * vertex.y + matrix[0][2] * vertex.z;
    float _y = matrix[1][0] * vertex.x + matrix[1][1] * vertex.y + matrix[1][2] * vertex.z;
    float _z = matrix[2][0] * vertex.x + matrix[2][1] * vertex.y + matrix[2][2] * vertex.z;

    vertex.x = _x;
    vertex.y = _y;
    vertex.z = _z;
}

// Multiplies two 4x4 matrices.
void MultiplyTwoMatrix4x4(Matrix4x4& matrix1, Matrix4x4& matrix2)
{
    Matrix4x4 tempMatrix;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            tempMatrix[i][j] = matrix1[i][0] * matrix2[0][j] + matrix1[i][1] * matrix2[1][j] + matrix1[i][2] * matrix2[2][j] + matrix1[i][3] * matrix2[3][j];
        }
    }
    matrix1 = tempMatrix;
}

// Transposes a matrix.
void TransposeMatrix(Matrix4x4& matrix, int row, int col)
{
    Matrix4x4 tempMatrix = matrix;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            tempMatrix[j][i] = matrix[i][j];
        }
    }
    matrix = tempMatrix;
}

// Inverts a matrix.
void InverseMatrix(Matrix4x4& matrix)
{
    Vector4 tempVertex(matrix[0][3], matrix[1][3], matrix[2][3]);
    TransposeMatrix(matrix, 3, 3);
    MultiplyVectorByMatrix3x3(tempVertex, matrix);
    tempVertex *= -1;
    matrix[0][3] = tempVertex.x;
    matrix[1][3] = tempVertex.y;
    matrix[2][3] = tempVertex.z;
}

// Applies rotation to a matrix based on rotation vector.
void ApplyRotation(Matrix4x4& matrix, Vector4 rotation)
{
    // Convert rotation angles from degrees to radians.
    float rotationX = DegreesToRadians(rotation.x);
    float rotationY = DegreesToRadians(rotation.y);
    float rotationZ = DegreesToRadians(rotation.z);

    if (rotationX != 0)
    {
        float rotX[4][4] = 
        {
            {1, 0, 0, 0},
            {0, cos(rotationX), -sin(rotationX), 0},
            {0, sin(rotationX), cos(rotationX), 0},
            {0, 0, 0, 1},
        };
        Matrix4x4 x(rotX);
        MultiplyTwoMatrix4x4(matrix, x);
    }

    if (rotationY != 0)
    {
        float rotY[4][4] = 
        {
            {cos(rotationY), 0, sin(rotationY), 0},
            {0, 1, 0, 0},
            {-sin(rotationY), 0, cos(rotationY), 0},
            {0, 0, 0, 1},
        };
        Matrix4x4 y(rotY);
        MultiplyTwoMatrix4x4(matrix, y);
    }

    if (rotationZ != 0)
    {
        float rotZ[4][4] = 
        {
            {cos(rotationZ), -sin(rotationZ), 0, 0},
            {sin(rotationZ), cos(rotationZ), 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1},
        };
        Matrix4x4 z(rotZ);
        MultiplyTwoMatrix4x4(matrix, z);
    }
}

// Rotates a matrix around an axis.
void AxisRotation(Matrix4x4& matrix, Vector4 rotation, Vector4& rotationInfo)
{
    // Accumulate rotations.
    rotationInfo.y = Cycle(rotationInfo.y + rotation.y, 360, 0);
    rotationInfo.x = Cycle(rotationInfo.x + rotation.x, 360, 0);
    rotationInfo.z = Cycle(rotationInfo.z + rotation.z, 360, 0);

    // Rebuild rotation matrix with all rotations.
    Matrix4x4 tempMatrix = matrix.TranslationMatrix();  // Translation preserved.
    ApplyRotation(tempMatrix, rotationInfo);            // Apply all rotations at once.
    matrix = tempMatrix;                                // Update the matrix.
}

// Translates a matrix.
void Translation(Matrix4x4& matrix, Vector4 translation)
{
    float translationMatrix[4][4] = 
    {
        {1, 0, 0, translation.x},
        {0, 1, 0, translation.y},
        {0, 0, 1, translation.z},
        {0, 0, 0, 1},
    };

    Matrix4x4 matrix2(translationMatrix);
    MultiplyTwoMatrix4x4(matrix, matrix2);
}

// Converts NDC (normalized device coordinates) to 2D screen coordinates.
Vector2 ConvertNDCto2D(Vector4 vertex)
{
    Vector2 result;
    result.x = (vertex.x + 1) * SCREEN_WIDTH / 2;
    result.y = (1 - vertex.y) * SCREEN_HEIGHT / 2;
    return result;
}

// Calculates the cross product of two vectors.
Vector4 CrossProduct(Vector4 vertex1, Vector4 vertex2)
{
    return 
    {
        vertex1.y * vertex2.z - vertex1.z * vertex2.y,
        vertex1.z * vertex2.x - vertex1.x * vertex2.z,
        vertex1.x * vertex2.y - vertex1.y * vertex2.x
    };
}

// Interpolates between two vertices for clipping.
void Interpolate(Vector4& vertex1, Vector4& vertex2)
{
    float deltaZNear = -vertex1.z;
    float deltaTotal = vertex2.z - vertex1.z;
    float ratio = deltaZNear / deltaTotal;

    vertex1.x += (vertex2.x - vertex1.x) * ratio;
    vertex1.y += (vertex2.y - vertex1.y) * ratio;
    vertex1.z += (vertex2.z - vertex1.z) * ratio;
    vertex1.u += (vertex2.u - vertex1.u) * ratio;
    vertex1.v += (vertex2.v - vertex1.v) * ratio;
    vertex1.w += (vertex2.w - vertex1.w) * ratio;
}

// Normalizes a vector.
void VectorNormalize(Vector4& vector)
{
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    if (length > 0.0f)
    {
        vector.x /= length;
        vector.y /= length;
        vector.z /= length;
    }
}

// Helper Function.
void DivideByW(Vector4& vertex1, Vector4& vertex2, Vector4& vertex3)
{
    vertex1 /= vertex1.w;
    vertex2 /= vertex2.w;
    vertex3 /= vertex3.w;
}

// Modulates (multiplies) two colors
unsigned int ModulateColors(unsigned int color1, unsigned int color2)
{
    ColorComponents c1 = ExtractColorComponents(color1);
    ColorComponents c2 = ExtractColorComponents(color2);

    c1.a = Clamp(c1.a * (c2.a / 255.0f), 255, 0);
    c1.r = Clamp(c1.r * (c2.r / 255.0f), 255, 0);
    c1.g = Clamp(c1.g * (c2.g / 255.0f), 255, 0);
    c1.b = Clamp(c1.b * (c2.b / 255.0f), 255, 0);

    return CombineColorComponents(c1);
}

// Multiplies a color by a float multiplier.
unsigned int MultiplyColor(unsigned int color, float multiplier)
{
    ColorComponents c = ExtractColorComponents(color);

    c.a = Clamp(c.a * multiplier, 255, 0);
    c.r = Clamp(c.r * multiplier, 255, 0);
    c.g = Clamp(c.g * multiplier, 255, 0);
    c.b = Clamp(c.b * multiplier, 255, 0);

    return CombineColorComponents(c);
}

// Adds two colors together.
unsigned int AdditiveColor(unsigned int color1, unsigned int color2)
{
    ColorComponents c1 = ExtractColorComponents(color1);
    ColorComponents c2 = ExtractColorComponents(color2);

    c1.a = Clamp(c1.a + c2.a, 255, 0);
    c1.r = Clamp(c1.r + c2.r, 255, 0);
    c1.g = Clamp(c1.g + c2.g, 255, 0);
    c1.b = Clamp(c1.b + c2.b, 255, 0);

    return CombineColorComponents(c1);
}

// Performs linear interpolation between colors.
unsigned int Lerp(unsigned int color1, float ratio)
{
    ratio = Clamp(ratio, 1.0f, 0.0f);

    ColorComponents c = ExtractColorComponents(color1);
    c.a = c.a * ratio;
    c.r = c.r * ratio;
    c.g = c.g * ratio;
    c.b = c.b * ratio;

    return CombineColorComponents(c);
}

Vector4 FindBarycentricCoordinate(Vector2 vertex, Triangle triangle)
{
    Vector2 _vertexA = ConvertNDCto2D(triangle.vertexA);
    Vector2 _vertexB = ConvertNDCto2D(triangle.vertexB);
    Vector2 _vertexC = ConvertNDCto2D(triangle.vertexC);

    float beta = ImplicitLineEquation(_vertexB, _vertexA, _vertexC);
    float gamma = ImplicitLineEquation(_vertexC, _vertexB, _vertexA);
    float alpha = ImplicitLineEquation(_vertexA, _vertexC, _vertexB);

    float b = ImplicitLineEquation(vertex, _vertexA, _vertexC);
    float y = ImplicitLineEquation(vertex, _vertexB, _vertexA);
    float a = ImplicitLineEquation(vertex, _vertexC, _vertexB);

    return Vector4(b / beta, y / gamma, a / alpha);
}

void CalculateBoundingBox(const Vector2& vertexA, const Vector2& vertexB, const Vector2& vertexC, float& startX, float& startY, float& endX, float& endY)
{
    startX = fminf(fminf(vertexA.x, vertexB.x), vertexC.x);
    startY = fminf(fminf(vertexA.y, vertexB.y), vertexC.y);
    endX = fmaxf(fmaxf(vertexA.x, vertexB.x), vertexC.x);
    endY = fmaxf(fmaxf(vertexA.y, vertexB.y), vertexC.y);

    startX = Clamp(startX, SCREEN_WIDTH - 1, 0);
    endX = Clamp(endX, SCREEN_WIDTH - 1, 0);
    startY = Clamp(startY, SCREEN_HEIGHT - 1, 0);
    endY = Clamp(endY, SCREEN_HEIGHT - 1, 0);
}

void CalculateUVandDepth(const Triangle& triangle, const Vector4& result, float& u, float& v, float& depth)
{
    float reciprocalA = 1 / triangle.vertexA.w;
    float reciprocalB = 1 / triangle.vertexB.w;
    float reciprocalC = 1 / triangle.vertexC.w;

    float w = reciprocalA * result.z + reciprocalB * result.x + reciprocalC * result.y;
    u = triangle.vertexA.u * result.z + triangle.vertexB.u * result.x + triangle.vertexC.u * result.y;
    v = triangle.vertexA.v * result.z + triangle.vertexB.v * result.x + triangle.vertexC.v * result.y;
    u /= w;
    v /= w;

    depth = triangle.vertexA.z * result.z + triangle.vertexB.z * result.x + triangle.vertexC.z * result.y;
}