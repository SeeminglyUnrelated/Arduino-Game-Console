#pragma once
#include <LedControl.h>

class Engine
{
    private:
        const int NEUTRAL_POS = 510;

        const int buttonPin1 = 13; // Joystick 1 button Default Mapping set to switch games
        const int buttonPin2 = 35; // Joystick 2 button Default Mapping set to switch brightness // TODO: Add more buttons
        const int dPin = 27, clkPin = 12, csPin = 14;
        const int Joystick1xPin = 26, Joystick1yPin = 25, Joystick2xPin = 33, Joystick2yPin = 32;

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
        int m_displayIntensity = 0;
        LedControl lc = LedControl(dPin, clkPin, csPin, m_displayCount);

        float deltaTime;
        unsigned long time;

        Engine();
        void updateLoop(float deltaTime);
        void setPixel(int x, int y, bool state);
        void drawImage(int *pixels, int xSize, int ySize, int xPos, int yPos);
        void clearAllDisplays();
        void setDisplayBrightness(int brightness);
        void updateDisplays();
        float remap(float, float, float, float, float);
};