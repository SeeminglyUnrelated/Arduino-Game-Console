#pragma once
#include <LedControl.h>

class Engine
{
    private:
        const int NEUTRAL_POS = 510;

        const int buttonPin1 = 2; // Joystick 1 button
        const int buttonPin2 = 3; // Joystick 2 button // TODO: Add more buttons
        const int dPin = 8, clkPin = 10, csPin = 9;
        const int Joystick1xPin = A0, Joystick1yPin = A1, Joystick2xPin = A2, Joystick2yPin = A3;

        int flipMatrixIndex(int virtualIndex, int maxIndex);
    public:
        struct {
            int buttonState;
            bool buttonDown;
            bool buttonUpThisFrame;
            bool buttonDownThisFrame;
            float buttonDownDuration;
            float x, y;
        } Joystick1, Joystick2;

        const int m_displayCount = 4, m_totalWidth = 32;
        LedControl lc = LedControl(dPin, clkPin, csPin, m_displayCount);

        float deltaTime;
        unsigned long time;

        Engine();
        void updateLoop(float deltaTime);
        void setPixel(int x, int y, bool state);
        // void drawImage(int *pixels, int xSize, int ySize, int xPos, int yPos);
        void clearAllDisplays();
        void updateDisplays();
        float remap(float, float, float, float, float);
};