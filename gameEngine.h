#pragma once
#include <LedControl.h>

class Engine {
public:
    int dPin = 8, clkPin = 10, csPin = 9, m_displayCount = 4, m_totalWidth = 32;
    LedControl lc = LedControl(dPin, clkPin, csPin, m_displayCount);

    bool buttonDown;
    bool buttonUpThisFrame;
    bool buttonDownThisFrame;
    float buttonDownDuration;

    float Joystick1x, Joystick1y;
    float Joystick2x, Joystick2y;
    const int NEUTRAL_POS = 510;

    float deltaTime;
    unsigned long time;

    Engine();
    void updateLoop(float deltaTime);
    void setPixel(int x, int y, bool state);
    // void drawImage(int *pixels, int xSize, int ySize, int xPos, int yPos);
    void clearAllDisplays();
    void updateDisplays();
    float remap(float, float, float, float, float);

private:
    const int buttonPin = 7; // TODO: Add other button pins
    int buttonState;
    int flipMatrixIndex(int virtualIndex, int maxIndex);
};