#include "MyMath.h"

// Perspective projection matrix.
float projectionMatrix[4][4] =
{
    {xScale, 0.0f, 0.0f, 0.0f},
    {0.0f, yScale, 0.0f, 0.0f},
    {0.0f, 0.0f, zFar / (zFar - zNear), -(zFar * zNear) / (zFar - zNear)},
    {0.0f, 0.0f, 1.0f, 0.0f}
};

Matrix4x4 worldMatrixProjection(projectionMatrix);

// Apply lighting to a vertex using directional and point lights.
void ApplyLighting(Vector4& vertex, const Vector4& normal)
{
    Vector4 directionalLightDir = directionalLight;
    MultiplyVectorByMatrix3x3(directionalLightDir, worldMatrixLight);
    directionalLightDir *= -1;

    // Apply directional lighting.
    float directionalLightRatio = Clamp(DotProduct(directionalLightDir, normal), 1, 0);
    unsigned int directionalLightColor = Lerp(directionalLight.color, directionalLightRatio + ambientLightingIntensity);

    // Calculate point light.
    Vector4 pointLightDir = pointLight - vertex;
    VectorNormalize(pointLightDir);
    float pointLightRatio = Clamp(DotProduct(pointLightDir, normal), 1, 0);
    float attenuation = 1.0f - Clamp(pointLight.Distance(vertex) / pointLightRadius, 1, 0);
    unsigned int pointLightColor = Lerp(pointLight.color, pointLightRatio * attenuation);

    // Combine light sources.
    unsigned int finalColor = AdditiveColor(directionalLightColor, pointLightColor);
    vertex.color = finalColor;
}

// Perform clipping for the triangle.
Triangle PerformClipping(Vector4& vertex1, Vector4& vertex2, Vector4& vertex3, unsigned int finalColor, bool& isClipped)
{
    Triangle tempTriangle;
    Vector4 tempVertex;

    // If all vertices are behind the near plane, the triangle is fully clipped.
    if (vertex1.z < 0 && vertex2.z < 0 && vertex3.z < 0) {
        isClipped = true;
        return tempTriangle;
    }

    // Perform clipping and interpolate between vertices.
    if (vertex1.z < 0)
    {
        if (vertex2.z < 0)
        {
            Interpolate(vertex1, vertex3);
            Interpolate(vertex2, vertex3);
        }
        else if (vertex3.z < 0)
        {
            Interpolate(vertex1, vertex2);
            Interpolate(vertex3, vertex2);
        }
        else
        {
            tempVertex = vertex1;
            Interpolate(vertex1, vertex2);
            Interpolate(tempVertex, vertex3);
            DivideByW(vertex1, vertex2, vertex3);
            tempVertex /= tempVertex.w;
            tempTriangle = { tempVertex, vertex1, vertex3 };
            tempTriangle.isClipped = true;
            tempTriangle.vertexA.color = finalColor;
            return tempTriangle;
        }
    }
    else if (vertex2.z < 0)
    {
        if (vertex3.z < 0)
        {
            Interpolate(vertex2, vertex1);
            Interpolate(vertex3, vertex1);
        }
        else
        {
            tempVertex = vertex2;
            Interpolate(vertex2, vertex1);
            Interpolate(tempVertex, vertex3);
            DivideByW(vertex1, vertex2, vertex3);
            tempVertex /= tempVertex.w;
            tempTriangle = { tempVertex, vertex3, vertex2 };
            tempTriangle.isClipped = true;
            tempTriangle.vertexA.color = finalColor;
            return tempTriangle;
        }
    }
    else if (vertex3.z < 0)
    {
        tempVertex = vertex3;
        Interpolate(vertex3, vertex1);
        Interpolate(tempVertex, vertex2);
        DivideByW(vertex1, vertex2, vertex3);
        tempVertex /= tempVertex.w;
        tempTriangle = { tempVertex, vertex2, vertex3 };
        tempTriangle.isClipped = true;
        tempTriangle.vertexA.color = finalColor;
        return tempTriangle;
    }

    DivideByW(vertex1, vertex2, vertex3);
    tempTriangle.vertexA /= tempTriangle.vertexA.w;

    return tempTriangle;
}

// Shader for transforming vertices and applying lighting.
Triangle ViewTriangle(Vector4& vertex1, Vector4& vertex2, Vector4& vertex3, bool& b)
{
    Triangle tempTriangle;
    Matrix4x4 tempMatrixView = worldMatrixView;
    InverseMatrix(tempMatrixView);

    // Lighting calculations for directional and point lights.
    Vector4 normal = { vertex1.normalX, vertex1.normalY, vertex1.normalZ };

    // Apply lighting to the vertices.
    ApplyLighting(vertex1, normal);
    ApplyLighting(vertex2, normal);
    ApplyLighting(vertex3, normal);

    // Apply view and projection transformations.
    MultiplyVectorByMatrix4x4(vertex1, tempMatrixView);
    MultiplyVectorByMatrix4x4(vertex2, tempMatrixView);
    MultiplyVectorByMatrix4x4(vertex3, tempMatrixView);
    MultiplyVectorByMatrix4x4(vertex1, worldMatrixProjection);
    MultiplyVectorByMatrix4x4(vertex2, worldMatrixProjection);
    MultiplyVectorByMatrix4x4(vertex3, worldMatrixProjection);

    // Call the clipping logic.
    return PerformClipping(vertex1, vertex2, vertex3, vertex1.color, b);
}

// Pixel shader for UV texturing, converting BGRA to ARGB format.
void ConvertBGRAtoARGB(Vector2& pixel, float u, float v, int width, int height, const unsigned int arr[], int size) {
    int x = u * width;
    int y = v * height;
    int pos = PixelConversion(x, y, width);

    if (pos >= size)
        return;

    // Extract the color from the array.
    unsigned int color = arr[pos];

    // Manually extract the components.
    ColorComponents colorComponents;
    colorComponents.r = (color & 0x0000ff00) >> 8;
    colorComponents.g = (color & 0x00ff0000) >> 16;
    colorComponents.b = (color & 0xff000000) >> 24;
    colorComponents.a = (color & 0x000000ff);

    // Rebuild the pixel color.
    pixel.color = (colorComponents.a << 24) | (colorComponents.r << 16) | (colorComponents.g << 8) | colorComponents.b;
}

// Solid color shaders.
void Black(Vector2& pixel) { pixel.color = BLACK; }
void Blue(Vector2& pixel) { pixel.color = BLUE; }
void Cyan(Vector2& pixel) { pixel.color = CYAN; }
void Green(Vector2& pixel) { pixel.color = GREEN; }
void Pink(Vector2& pixel) { pixel.color = PINK; }
void Red(Vector2& pixel) { pixel.color = RED; }
void White(Vector2& pixel) { pixel.color = WHITE; }
void Yellow(Vector2& pixel) { pixel.color = YELLOW; }