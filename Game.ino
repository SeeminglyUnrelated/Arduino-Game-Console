#include "gameEngine.h"
#include "src/Snake.h"
#include "src/Pong.h"
#include "src/Game.h"
#include "src/SpaceGame.h"
#include "src/Tetris.h"

const bool showStartupSequence = true;
const int numGames = 4;

int activeGameIndex = 3;
unsigned long timeOld;

Engine engine = Engine();
Game *game = new TetrisGame();

void setup()
{
  Serial.begin(115200);

  if (showStartupSequence)
  {
    startupSequence();
  }

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
  handleGames(deltaTime);
  // Check for button 2 input (brightness button)
  if (engine.Joystick2.buttonUpThisFrame && engine.Joystick2.buttonDownDuration > 0.25)
  {
    int newIntensity = engine.m_displayIntensity + 4;
    if (newIntensity > 15) newIntensity = 1;
    engine.setDisplayBrightness(newIntensity);
    Serial.print("New intensity: ");
    Serial.println(newIntensity);
  }

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

void handleGames(float deltaTime)
{
  game->updateLoop(engine);

  const float switchGameButtonHoldTime = 0.75;
  if (engine.Joystick1.buttonUpThisFrame && engine.Joystick1.buttonDownDuration > switchGameButtonHoldTime)
  {
    switchGame();
  }
}

void switchGame()
{
  Serial.println("Switching game");
  activeGameIndex += 1;
  activeGameIndex %= numGames;
  delete game;

  if (activeGameIndex == 0)
  {
    game = new SnakeGame;
  }
  else if (activeGameIndex == 1)
  {
    game = new PongGame;
  }
  else if (activeGameIndex == 2)
  {
    game = new SpaceGame;
  }
  else if (activeGameIndex == 3)
  {
    game = new TetrisGame;
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