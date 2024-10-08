#include "gameEngine.h"


Engine ::Engine()
{
    for (int index1 = 0; index1 < m_displayCount; index1++)
    {
        lc.shutdown(index1, false);
    }

    pinMode(buttonPin1, INPUT_PULLUP);
    
    // This doesn't work on ESP32
    //digitalWrite(buttonPin1, HIGH); // Joystick buttons must be set to active low

    pinMode(buttonPin2, INPUT_PULLUP);
    
    // This doesn't work on ESP32
    //digitalWrite(buttonPin2, HIGH);
    // pinMode(buzzerPin, OUTPUT);

    clearAllDisplays();
    time = 0;

    setDisplayBrightness(4);
}


// set display brightness [0,15]
void Engine::setDisplayBrightness(int brightness) {
	lc.setIntensity(0, brightness);
    lc.setIntensity(1, brightness);
    lc.setIntensity(2, brightness);
    lc.setIntensity(3, brightness);
    m_displayIntensity = brightness;
}

// TODO: Make frame buffer
void Engine::updateLoop(float deltaTime) {
    this->deltaTime = deltaTime;
    time += deltaTime;

    // Button input joystick 1:
    int buttonStateOld = Joystick1.buttonState;
    Joystick1.buttonState = !digitalRead(buttonPin1); // Inverted because joystick button is active low
    Joystick1.buttonDown = Joystick1.buttonState == 1;
    Joystick1.buttonDownThisFrame = Joystick1.buttonDown && Joystick1.buttonState != buttonStateOld;
    Joystick1.buttonUpThisFrame = Joystick1.buttonState == 0 && buttonStateOld == 1;

    if (Joystick1.buttonDownThisFrame)
        Joystick1.buttonDownDuration = 0;
    if (Joystick1.buttonDown)
        Joystick1.buttonDownDuration += deltaTime;

    // Button input joystick 2:
    buttonStateOld = Joystick2.buttonState;
    Joystick2.buttonState = !digitalRead(buttonPin2); // Inverted because joystick button is active low
    Joystick2.buttonDown = Joystick2.buttonState == 1;
    Joystick2.buttonDownThisFrame = Joystick2.buttonDown && Joystick2.buttonState != buttonStateOld;
    Joystick2.buttonUpThisFrame = Joystick2.buttonState == 0 && buttonStateOld == 1;

    if (Joystick2.buttonDownThisFrame)
        Joystick2.buttonDownDuration = 0;
    if (Joystick2.buttonDown)
        Joystick2.buttonDownDuration += deltaTime;

    // Get analog stick input:
    const float inputThreshold = 0.6;
    Joystick1.x = remap(analogRead(Joystick1xPin), 0, 4095, -1, 1);
    Joystick1.y = remap(analogRead(Joystick1yPin), 0, 4095, -1, 1);
    Joystick2.x = remap(analogRead(Joystick2xPin), 0, 4095, -1, 1);
    Joystick2.y = remap(analogRead(Joystick2yPin), 0, 4095, -1, 1);

    if (abs(Joystick1.x) < inputThreshold)
        Joystick1.x = 0;
    if (abs(Joystick1.y) < inputThreshold)
        Joystick1.y = 0;

    if (abs(Joystick2.x) < inputThreshold)
        Joystick2.x = 0;
    if (abs(Joystick2.y) < inputThreshold)
        Joystick2.y = 0;
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