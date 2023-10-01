#pragma once
#include <LedControl.h>

class Engine {
public:
    int dPin = 8, clkPin = 10, csPin = 9, m_displayCount = 4, m_totalWidth = 32;
    float Joystick1x, Joystick1y;
    float Joystick2x, Joystick2y;
    LedControl lc = LedControl(dPin, clkPin, csPin, m_displayCount);
    float deltaTime;
    unsigned long time;

    const int NEUTRAL_POS = 510;

    // Function to get the pixel data for a specific letter
    const int *getLetterData(char letter);

    void updateLoop(float deltaTime);
    void setPixel(int x, int y, bool state);
    void drawImage(int *pixels, int xSize, int ySize, int xPos, int yPos);
    void clearAllDisplays();
    void updateDisplays();
    float remap(float, float, float, float, float);

private:
    int flipMatrixIndex(int virtualIndex, int maxIndex);
};