#include <LedControl.h>
#include "gameEngine.h"
#include "src/Snake.h"
#include "src/Pong.h"
#include "src/Game.h"

Engine engine = Engine();

unsigned long timeOld;
Game* game = new PongGame();

void setup() {
  Serial.begin(115200);
  for(int index1=0;index1<engine.m_displayCount;index1++) {
      engine.lc.shutdown(index1,false);
  }
  engine.clearAllDisplays();
  // startupSequence();
  timeOld = millis();
}

void loop()
{
  // Calculate delta time
  unsigned long frameStartTime = millis();
  unsigned long deltaTimeMillis = frameStartTime - timeOld;
  float deltaTime = deltaTimeMillis / 1000.0;
  timeOld = frameStartTime;

  // Update
  engine.clearAllDisplays();
  engine.updateLoop(deltaTime);
  game->updateLoop(engine);

  // Wait for target fps
  unsigned long endTime = millis();
  unsigned long frameTime = endTime - frameStartTime;

  const unsigned long targetDelay = 16;
  if (frameTime < targetDelay)
  {
      unsigned long waitForFPSTime = targetDelay - frameTime;
      delay(waitForFPSTime);
  }
}

void startupSequence()
{
  // Frame 1
  for (int y = 0; y < 8; y++)
  {
    for (int x = 0; x < 32; x++)
    {
      if (!(x <= y || x - 16 >= y + 8))
      {
        engine.setPixel(x, y, true);
      }
    }
  }
  delay(320);

  // Frame 2
  for (int y = 0; y < 8; y++)
  {
    for (int x = 0; x < 32; x++)
    {
      if (x <= y)
      {
        engine.setPixel(x, y, true);
      }
    }
  }
  delay(320);

  // Frame 3
  for (int y = 0; y < 8; y++)
  {
    for (int x = 0; x < 32; x++)
    {
      engine.setPixel(x, y, true);
    }
  }
  delay(700);

  // Transition out
  for (int i = 0; i < 32; i++)
  {
    for (int x = 0; x < 32; x++)
    {
      for (int y = 0; y < 8; y++)
      {
        if ((x + (8 - y) <= i || 32 - x + y <= i))
        {
          engine.setPixel(x, y, false);
        }
      }
    }
    delay(35);
  }
  delay(30);
}