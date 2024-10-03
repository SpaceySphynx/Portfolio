#include "RasterFunctions.h"

// Handles input for camera movement and rotation based on keypresses.
void GetInputs(float delta)
{
    // Move forward (W key)
    if (GetAsyncKeyState(0x57))
        Translation(worldMatrixView, Vector4(0, 0, cameraMovementSpeed * delta));

    // Move left (A key)
    if (GetAsyncKeyState(0x41))
        Translation(worldMatrixView, Vector4(-cameraMovementSpeed * delta, 0, 0));

    // Move backward (S key)
    if (GetAsyncKeyState(0x53))
        Translation(worldMatrixView, Vector4(0, 0, -cameraMovementSpeed * delta));

    // Move right (D key)
    if (GetAsyncKeyState(0x44))
        Translation(worldMatrixView, Vector4(cameraMovementSpeed * delta, 0, 0));

    // Rotate camera left (left arrow key)
    if (GetAsyncKeyState(0x25))
        AxisRotation(worldMatrixView, Vector4(0, -cameraHorizontalAxisSpeed * delta, 0), viewRotationInfo);

    // Rotate camera right (right arrow key)
    if (GetAsyncKeyState(0x27))
        AxisRotation(worldMatrixView, Vector4(0, cameraHorizontalAxisSpeed * delta, 0), viewRotationInfo);

    // Rotate camera up (up arrow key)
    if (GetAsyncKeyState(0x26))
        AxisRotation(worldMatrixView, Vector4(-cameraVerticalAxisSpeed * delta, 0, 0), viewRotationInfo);

    // Rotate camera down (down arrow key)
    else if (GetAsyncKeyState(0x28))
        AxisRotation(worldMatrixView, Vector4(cameraVerticalAxisSpeed * delta, 0, 0), viewRotationInfo);
}

// Initializes the application, setting up shaders, transformations, and other resources.
void InitializeApp()
{
    // Set the vertex and pixel shaders
    VertexShaderWithClipTriangle = ViewTriangle;
    UVShader = ConvertBGRAtoARGB;

    // Set the initial position of the camera
    Translation(worldMatrixView, Vector4(0, 0.75, -1));

    // Generate the skybox and load the model for rendering
    GenerateSkybox();
    LoadModel();

    // Initialize the rendering surface
    RS_Initialize("Johnathan Richards", SCREEN_WIDTH, SCREEN_HEIGHT);
}

// Updates the light radius, adjusting it over time for dynamic light changes.
void UpdateLightRadius(float delta, float& radiusMutiplier)
{
    pointLightRadius += delta * radiusMutiplier * 2;

    // Invert the radius change when limits are reached
    if (pointLightRadius > 5.0f)
    {
        pointLightRadius = 5.0f;
        radiusMutiplier = -1;
    }
    else if (pointLightRadius <= 0)
    {
        pointLightRadius = 0;
        radiusMutiplier = 1;
    }
}

// Main render loop, clearing buffers, drawing stars, rendering the model, and handling input.
void RenderLoop(XTime& timer, float& radiusMutiplier)
{
    do 
    {
        // Clear screen and depth buffers for each frame.
        ClearScreenBuffer();
        ClearDepthBuffer();

        // Draw the stars using the white shader and Render StoneHenge.
        pixelShader = White;
        DrawStars();
        RenderModel();

        // Update the timer and get input for camera movement and rotation
        timer.Signal();
        GetInputs(timer.Delta());

        // Update the light radius dynamically
        UpdateLightRadius(timer.Delta(), radiusMutiplier);

    } while (RS_Update(backBuffer.data(), TOTAL_SCREEN_PIXELS));  // Continue rendering until the window is closed
}

int main()
{
    srand(time(NULL));

    // Initialize the application.
    InitializeApp();

    XTime timer;
    float radiusMutiplier = 1;

    // Start the render loop.
    RenderLoop(timer, radiusMutiplier);

    // Shutdown the rendering.
    RS_Shutdown();
}