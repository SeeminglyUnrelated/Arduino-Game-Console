#include "gameEngine.h"

Engine ::Engine()
{
    for (int index1 = 0; index1 < m_displayCount; index1++)
    {
        lc.shutdown(index1, false);
    }

    pinMode(buttonPin, INPUT);
    digitalWrite(buttonPin, HIGH);
    // pinMode(buzzerPin, OUTPUT);

    clearAllDisplays();
    time = 0;
}

// TODO: Make frame buffer
void Engine::updateLoop(float deltaTime) {
    this->deltaTime = deltaTime;
    time += deltaTime;

    // Button input:
    int buttonStateOld = buttonState;
    buttonState = !digitalRead(buttonPin);
    buttonDown = buttonState == 1;
    buttonDownThisFrame = buttonDown && buttonState != buttonStateOld;
    buttonUpThisFrame = buttonState == 0 && buttonStateOld == 1;

    Serial.println(!digitalRead(7));

    if (buttonDownThisFrame)
    {
        buttonDownDuration = 0;
    }
    if (buttonDown)
    {
        buttonDownDuration += deltaTime;
    }

    // Get analog stick input:
    const float inputThreshold = 0.1;
    Joystick1x = remap(analogRead(A0), 0, 1023, -1, 1);
    Joystick1y = remap(analogRead(A1), 0, 1023, -1, 1);
    Joystick2x = remap(analogRead(A2), 0, 1023, -1, 1);
    Joystick2y = remap(analogRead(A3), 0, 1023, -1, 1);

    // Serial.print("X: ");
    // Serial.print(Joystick1x);
    // Serial.print(" Y: ");
    // Serial.print(Joystick1y);
    // Serial.print("\n");

    if (abs(Joystick1x) < inputThreshold)
    {
        Joystick1x = 0;
    }
    if (abs(Joystick1y) < inputThreshold)
    {
        Joystick1y = 0;
    }

    if (abs(Joystick2x) < inputThreshold)
    {
        Joystick2x = 0;
    }
    if (abs(Joystick2y) < inputThreshold)
    {
        Joystick2y = 0;
    }
}

int Engine::flipMatrixIndex(int virtualIndex, int maxIndex) {
    if (virtualIndex < 0 || virtualIndex >= maxIndex) {
        return -1; // Invalid input
    }
    
    return maxIndex - 1 - virtualIndex;
}

void Engine::setPixel(int x, int y, bool state) {
    int virtualMatrixIndex = (int)(x / (m_totalWidth / m_displayCount));
    int realMatrixIndex = flipMatrixIndex(virtualMatrixIndex, m_displayCount);

    // Calculate the x-coordinate relative to the matrix
    int xWithinMatrix = x % (m_totalWidth / m_displayCount);

    lc.setLed(realMatrixIndex, y, xWithinMatrix, state);
}

//! Commented out since it is very slow
// void Engine::drawImage(int *pixels, int numRows, int numCols, int xPos, int yPos)
// {
//     for (int y = 0; y < numCols; y++)
//     {
//         for (int x = 0; x < numRows; x++)
//         {
//             // Calculate the index in the 1D array
//             int index = y * numRows + x;
//             if (!pixels[index]) continue; // No pixel = no need for calculations. This optimizes a lot but is dangerous and won't work if we don't clear the screen each frame

//             int pixelX = x + xPos;
//             int pixelY = y + yPos;

//             // Check if the pixel coordinates are within the display boundaries
//             if (pixelX >= 0 && pixelX < m_totalWidth && pixelY >= 0 && pixelY < 8)
//             {

//                 // Set the pixel on the LED matrix using the setPixel method
//                 setPixel(pixelX, pixelY, true); // The pixel cannot be 0 because of the check earlier.
//             }
//         }
//     }
// }

void Engine::clearAllDisplays()
{
    for (int index = 0; index < m_displayCount; index++)
    {
        lc.clearDisplay(index);
    }
}

float Engine::remap(float value, float minOld, float maxOld, float minNew, float maxNew)
{
    return minNew + (value - minOld) / (maxOld - minOld) * (maxNew - minNew);
}